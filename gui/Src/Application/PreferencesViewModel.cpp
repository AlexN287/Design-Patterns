#include "PreferencesViewModel.h"

#include "PreferencesView.h"

PreferencesViewModel::PreferencesViewModel( IMapService* mapService, INavigationService* navigationService, IViewModelListener* listener )
    : BaseViewModel( mapService, navigationService, listener )
{
    auto func1 = [&]()
    {
        std::map<std::string, std::any> params;
        params["mapView"] = m_mapView;

        m_navigationService->GoToView( EView::Main, params );
    };

    SetMenuItems( { { "Main menu", func1 } } );
}

void PreferencesViewModel::Init( const std::map<std::string, std::any>& params )
{
    auto it = params.find( "mapView" );
    if (it != params.end())
        m_mapView = std::any_cast<IMapViewPtr>(it->second);
}

bool PreferencesViewModel::IsRenderFps() const
{
    return m_mapService->IsRenderFps();
}

void PreferencesViewModel::SetRenderFps( bool renderFps )
{
    m_mapService->SetRenderFps( renderFps );
    if (m_mapView)
        m_mapView->SetRenderFps( renderFps );
}
