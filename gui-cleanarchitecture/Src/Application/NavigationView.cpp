#include "NavigationView.h"

#include "IMainWindow.h"
#include "NavigationViewModel.h"

#include "IResourceRepository.h"
#include "ITextureRepository.h"
#include "NavigationInstructionItem.h"
#include "StringItem.h"
#include "RgbaItem.h"
#include "AbstractGeometryImageRenderSettingsItem.h"

#include <API/GEM_ContentStoreItem.h>

NavigationView::NavigationView( IMainWindow* parent )
    : BaseView( parent )
    , m_viewModel( nullptr )
    , m_mapFilterIndex( 0 )
{

}

IViewModel* NavigationView::GetViewModel()
{
    return m_viewModel;
}

void NavigationView::SetViewModel( IViewModel* viewModel )
{
    m_viewModel = static_cast<NavigationViewModel*>(viewModel);
}

static gem::String FormatFileSize( gem::LargeInteger sz )
{
    if (sz < 1024 * 1024)
        return gem::String::formatString( u"%.2lf KB", sz / 1024. );

    if (sz < 1024 * 1024 * 1024)
        return gem::String::formatString( u"%.2lf MB", sz / (1024. * 1024.) );

    return gem::String::formatString( u"%.2lf GB", sz / (1024. * 1024. * 1024.) );
}

void NavigationView::Render()
{
    int fullWindowWidth = m_parentWindow->GetWindowWidth();
    int fullWindowHeight = m_parentWindow->GetWindowHeight();

    static const ImVec2 DEFAULT_WINDOW_PADDING = ImGui::GetStyle().WindowPadding;
    static const ImVec2 DEFAULT_ITEM_SPACING = ImGui::GetStyle().ItemSpacing;

    //auto textureRepository = m_viewModel->GetTextureRepository();
    //gem::NavigationInstruction instruction = m_viewModel->GetNavigationInstruction();
    NavigationInstructionItem instruction(m_viewModel->GetNavigationInstruction());
    //INavigationInstructionPtr instruction = INavigationInstruction::Produce(m_viewModel->GetNavigationInstruction(), textureRepository);

    m_parentWindow->PushFontSize( EFontSize::Big );

    // Instruction window
    {
        // window and columns size
        const ImVec2 INSTRUCTION_ICON_SIZE( DPI( 70 ), DPI( 70 ) );

        ImVec2 windowSize( std::min( DPI( 800 ), m_parentWindow->GetDefaultViewSize().x - DPI( 30 ) ), INSTRUCTION_ICON_SIZE.x + DPI( 10 ) );
        ImVec2 windowPos( m_parentWindow->GetDefaultViewPos().x, DPI( 5 ) );

        int firstColumnSize = INSTRUCTION_ICON_SIZE.x;
        int secondColumnSize = DPI( 70 );
        int lastColumnSize = windowSize.x - firstColumnSize - secondColumnSize - DPI( 20 );

        // prepare data
        auto distMetersToNextTurn = instruction.GetTimeDistanceToNextTurn().getTotalDistance();

        StringItem instructionDist;

        if ( distMetersToNextTurn < 1000 )
            //instructionDist = gem::String::formatString( u"(%d m)", distMetersToNextTurn);
            instructionDist.SetString(instructionDist.FormatString(u"(%d m)", distMetersToNextTurn));
        else
            //instructionDist = gem::String::formatString( u"(%.2f km)", distMetersToNextTurn / 1000. );
            instructionDist.SetString(instructionDist.FormatString(u"(%.2f km)", distMetersToNextTurn / 1000.));

        StringItem instructionText;
        instructionText.SetString(instruction.GetNextTurnInstruction());
        instructionText.FallBackToLegacyUnicode();

        static int lastWindowSizeX = 0;
        static StringItem lastInstructionText;
        static StringItem lastTransformedInstructionText;
        lastInstructionText.SetString("");
        lastTransformedInstructionText.SetString("");

        if ( instructionText.GetString() == lastInstructionText.GetString() && windowSize.x == lastWindowSizeX)
            instructionText.SetString(lastTransformedInstructionText.GetString());
        else
        {
            lastInstructionText.SetString(instructionText.GetString());

            std::vector<StringItem> lines;
            while ( !instructionText.Empty() )
            {
                auto instructionTextSize = ImGui::CalcTextSize( instructionText.ToStdString().c_str() );
                if ( instructionTextSize.x > lastColumnSize )
                {
                    if ( instructionText.Find( ' ' ) == -1 )
                    {
                        lines.push_back( instructionText );
                        instructionText.Clear();
                        break;
                    }

                    for ( int i = instructionText.Size() - 2; i >= 0; i-- )
                    {
                        if ( instructionText.GetElementOnPosition(i) == ' ')
                        {
                            StringItem str; 
                            str.SetString(instructionText.Left(i));
                            if ( ImGui::CalcTextSize( str.ToStdString().c_str() ).x < lastColumnSize )
                            {
                                lines.push_back( str );
                                instructionText.SetString(instructionText.Right(instructionText.Size() - i - 1));
                                break;
                            }
                        }
                    }
                }
                else
                {
                    lines.push_back( instructionText );
                    instructionText.Clear();
                    break;
                }
            }

            instructionText.Clear();
            if ( !lines.empty() )
            {
                for ( int i = 0; i + 1 < lines.size(); i++ )
                    instructionText.Append( lines[i].GetString()).append("\n");
                instructionText.Append( lines.back().GetString() );
            }

            lastTransformedInstructionText.SetString(instructionText.GetString());
        }

        lastWindowSizeX = windowSize.x;

        unsigned int imageId = instruction.GetNextTurnDetails().getAbstractGeometryImage().getUid();

        // actual UI

        ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0, 0 ) );

        m_parentWindow->BeginWindow( "Window_NextInstruction", windowSize, windowPos );

        if ( ImGui::BeginTable( "##table_instructions", 3 ) )
        {
            ImGui::TableSetupColumn( "", ImGuiTableColumnFlags_WidthFixed, firstColumnSize );
            ImGui::TableSetupColumn( "", ImGuiTableColumnFlags_WidthFixed, secondColumnSize );
            ImGui::TableSetupColumn( "", ImGuiTableColumnFlags_WidthFixed, lastColumnSize );

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex( 0 );

            if ( !instruction.IsNavigationInstructionNull() && !instruction.IsDefault())
            {
                auto textureRepository = m_viewModel->GetTextureRepository();

                RgbaItem color( 100, 100, 100, 255 );
                RgbaItem white(255, 255, 255, 255);
                RgbaItem black(0,0,0,255);
                AbstractGeometryImageRenderSettingsItem settings(white.GetColor(), black.GetColor(), color.GetColor());

                auto textureId = textureRepository->GetTexture( instruction.GetNextTurnDetails().getAbstractGeometryImage(), settings.GetSettings(), INSTRUCTION_ICON_SIZE.x, INSTRUCTION_ICON_SIZE.x);

                ImGui::Image( (void*)textureId, INSTRUCTION_ICON_SIZE );
            }

            ImGui::TableSetColumnIndex( 1 );

            ImGui::SetCursorPosY( ImGui::GetCursorPosY() + ( windowSize.y - ImGui::GetFontSize() ) / 4 );
            if ( !instruction.IsNavigationInstructionNull() && !instruction.IsDefault())
                ImGui::TextUnformatted( instructionDist.ToStdString().c_str() );

            ImGui::TableSetColumnIndex( 2 );

            ImGui::SetCursorPosY( ImGui::GetCursorPosY() + ( windowSize.y - ImGui::GetFontSize() ) / 4 );
            if (!instruction.IsNavigationInstructionNull() && !instruction.IsDefault() )
                ImGui::TextUnformatted( instructionText.ToStdString().c_str() );

            ImGui::EndTable();
        }

        m_parentWindow->EndWindow();

        ImGui::PopStyleVar();
    }

    // Remaining distance window
    {
        // prepare data
        int distMeters = instruction.GetRemainingTravelTimeDistance().getTotalDistance();

        char distStr[20];
        if ( distMeters < 1000 )
            sprintf( distStr, "%d m", distMeters - distMeters % 50 );
        else
            sprintf( distStr, "%.2f km", ( distMeters - distMeters % 50 ) / 1000.f );

        int timeSec = instruction.GetRemainingTravelTimeDistance().getTotalTime();
        char timeStr[20];
        if ( timeSec < 60 )
            sprintf( timeStr, "%d sec", timeSec + 5 - timeSec % 5 );
        else
            if ( timeSec < 3600 )
                sprintf( timeStr, "%d min", timeSec / 60 );
            else
                sprintf( timeStr, "%d:%02d hr", timeSec / 3600, ( timeSec % 3600 ) / 60 );

        // actual UI
        ImVec2 windowSize(
            std::max( ImGui::CalcTextSize( distStr ).x, ImGui::CalcTextSize( timeStr ).x ) + 2 * DEFAULT_WINDOW_PADDING.x + DPI( 5 ),
            2 * ImGui::GetTextLineHeight() + DEFAULT_ITEM_SPACING.y + 2 * DEFAULT_WINDOW_PADDING.y );
        ImVec2 windowPos( 0, fullWindowHeight - windowSize.y + 1 );

        m_parentWindow->BeginWindow( "Window_RemainingTimeDistance", windowSize, windowPos );

        ImGui::TextUnformatted( distStr );
        ImGui::TextUnformatted( timeStr );

        m_parentWindow->EndWindow();
    }

    // Speed window
    {
        // prepare data
        auto position = instruction.GetCurrentPosition();
        double speedKMH = position ? position->getSpeed() * 3.6 : 0;

        char speedStr[20];
        if ( speedKMH < 1 )
            sprintf( speedStr, "%.2f km/h", speedKMH );
        else
            sprintf( speedStr, "%d km/h", (int)speedKMH );

        //actual UI
        ImVec2 windowSize( ImGui::CalcTextSize( speedStr ).x + 2 * DEFAULT_WINDOW_PADDING.x + DPI( 5 ), ImGui::GetTextLineHeight() + 2 * DEFAULT_WINDOW_PADDING.y );
        ImVec2 windowPos( fullWindowWidth - windowSize.x + 1, fullWindowHeight - windowSize.y + 1 );

        m_parentWindow->BeginWindow( "Window_Speed", windowSize, windowPos );

        ImGui::TextUnformatted( speedStr );

        m_parentWindow->EndWindow();
    }

    m_parentWindow->PopFontSize();
}

void NavigationView::OnEvent( EVmEvent event )
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

