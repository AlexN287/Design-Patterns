#include "MapsView.h"

#include "IMainWindow.h"
#include "MapsViewModel.h"

#include "IResourceRepository.h"
#include "ITextureRepository.h"

#include <API/GEM_ContentStoreItem.h>

MapsView::MapsView( IMainWindow* parent )
    : BaseView( parent )
    , m_viewModel( nullptr )
    , m_mapFilterIndex( 0 )
{

}

IViewModel* MapsView::GetViewModel()
{
    return m_viewModel;
}

void MapsView::SetViewModel( IViewModel* viewModel )
{
    m_viewModel = static_cast<MapsViewModel*>(viewModel);
}

static gem::String FormatFileSize( gem::LargeInteger sz )
{
    if (sz < 1024 * 1024)
        return gem::String::formatString( u"%.2lf KB", sz / 1024. );

    if (sz < 1024 * 1024 * 1024)
        return gem::String::formatString( u"%.2lf MB", sz / (1024. * 1024.) );

    return gem::String::formatString( u"%.2lf GB", sz / (1024. * 1024. * 1024.) );
}

void MapsView::Render()
{
    auto resourceRepository = m_viewModel->GetResourceRepository();
    auto textureRepository = m_viewModel->GetTextureRepository();

    m_parentWindow->BeginView( "Maps_View" );

    if (!resourceRepository->IsResourceAvailable(EResourceType::Map))
    {
        m_parentWindow->LoadingWindow( "Loading maps", ImGuiColor_Green, ImGuiColor_Black );
    }
    else
    {
        //gem::ContentStoreItemList contentStoreItems = resourceRepository->GetMaps();
        IMapsCollectionPtr contentStoreItems = IMapsCollection::Produce(resourceRepository->GetMaps(), resourceRepository, textureRepository);

        ImGui::SetNextWindowBgAlpha( 0.8f );

        const float SCROLL_BAR_SIZE = DPI( 30 );
        ImGui::PushStyleVar( ImGuiStyleVar_ScrollbarSize, SCROLL_BAR_SIZE );

        static const char* contentStoreFilter[5] = { "All", "Downloaded", "Not downloaded", "In progress", "Paused" };
        m_parentWindow->Combo( "##filtermapscombo", contentStoreFilter, IM_ARRAYSIZE( contentStoreFilter ), m_mapFilterIndex, []() {} );

        if (ImGui::BeginTable( "##table_maps", 3, ImGuiTableFlags_ScrollY ))
        {
            static float COLUMN2_SIZE = 0;
            if (COLUMN2_SIZE < 0.1)
                COLUMN2_SIZE = ImGui::CalcTextSize( "888.88 MB" ).x;

            const float COLUMN0_SIZE = DPI( 30 );
            const float COLUMN1_SIZE = ImGui::GetWindowWidth() - COLUMN0_SIZE - COLUMN2_SIZE - SCROLL_BAR_SIZE - DPI( 20 );

            ImGui::TableSetupScrollFreeze( 0, 1 ); // Make top row always visible
            ImGui::TableSetupColumn( "##Code", ImGuiTableColumnFlags_WidthFixed, COLUMN0_SIZE );
            ImGui::TableSetupColumn( "Country", ImGuiTableColumnFlags_WidthFixed, COLUMN1_SIZE );
            ImGui::TableSetupColumn( "Size", ImGuiTableColumnFlags_WidthFixed, COLUMN2_SIZE );

            ImGui::TableHeadersRow();

            //for (auto item : contentStoreItems)
            for (int i = 0; i < contentStoreItems->GetSize(); i++)
            {
                //auto itemState = resourceRepository->GetItemState( item );
                IMapElementPtr item = contentStoreItems->GetItem(i);
                auto itemState = item->GetState();

                if (m_mapFilterIndex != 0 && m_mapFilterIndex != (int)itemState)
                    continue;

               // gem::String itemName = item.getName();
               //itemName.fallbackToLegacyUnicode(); // needed to fix some Romanian legacy unicodes
                item->FallbackToLegacyUnicode();
                std::string itemName = item->GetName();

                //std::string itemName = item->GetName();

                if (itemState == EItemState::Paused)
                    itemName = item->FormatStringDownload(u"[PAUSED %d%%] %s");

                if (itemState == EItemState::InProgress)
                    itemName = item->FormatStringDownload(u"[%02d%%] %s");

                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex( 0 );

                const ImVec2 COUNTRY_ICON_SIZE( DPI( 20 ), DPI( 20 ) );
                //gem::String countryCode = item.getCountryCodes()[0];
                //unsigned int textureId = textureRepository->GetTexture( resourceRepository->GetFlagImage( countryCode ), COUNTRY_ICON_SIZE.x, COUNTRY_ICON_SIZE.y );
                unsigned int textureId = item->GetTexture(COUNTRY_ICON_SIZE.x, COUNTRY_ICON_SIZE.y);
                ImGui::Image( (void*)textureId, COUNTRY_ICON_SIZE );

                ImGui::TableSetColumnIndex( 1 );

                switch (itemState)
                {
                case EItemState::Unavailable:
                case EItemState::Paused:
                {
                    ImGui::PushStyleColor( ImGuiCol_Button, ImGuiColor_Black );
                    ImGui::BeginDisabled( !m_viewModel->IsConnected() && itemState == EItemState::Paused );

                    if (ImGui::Button( itemName.c_str() ))
                        //resourceRepository->DownloadAsync( item );
                        item->StartDownload();

                    ImGui::EndDisabled();
                    ImGui::PopStyleColor();
                    break;
                }
                case EItemState::Completed:
                {
                    ImGui::PushStyleColor( ImGuiCol_Button, ImGuiColor_Black );
                    ImGui::PushStyleColor( ImGuiCol_Text, ImGuiColor_Green );
                    ImGui::BeginDisabled( true );

                    ImGui::Button( itemName.c_str() );

                    ImGui::EndDisabled();
                    ImGui::PopStyleColor();
                    ImGui::PopStyleColor();
                    break;
                }
                case EItemState::InProgress:
                {
                    ImGui::PushStyleColor( ImGuiCol_Button, ImGuiColor_Black );

                    if (ImGui::Button(itemName.c_str()))
                        item->StopDownload();

                    ImGui::PopStyleColor();
                    break;
                }
                }

                ImGui::TableSetColumnIndex( 2 );

                ImGui::TextUnformatted( FormatFileSize( item->GetTotalSize() ).toStdString().c_str() );
            }

            ImGui::EndTable();
        }

        ImGui::PopStyleVar( 1 );
    }

    m_parentWindow->EndView();
}

void MapsView::OnEvent( EVmEvent event )
{
    switch (event)
    {
    case EVmEvent::Generic_ChangedConnection:
        break;
    default:
        BaseView::OnEvent( event );
        break;
    }
}

