#include "MainViewModel.h"

#include "MainView.h"

MainViewModel::MainViewModel( IMapService* mapService, INavigationService* navigationService, IViewModelListener* listener )
    : BaseViewModel( mapService, navigationService, listener )
{
    UpdateMenuItems();
}

void MainViewModel::Init( const std::map<std::string, std::any>& params )
{
    auto it = params.find( "mapView" );
    if (it != params.end())
        m_mapView = std::any_cast<IMapViewPtr>(it->second);
    else
        m_mapView = GetMapService()->ProduceMapView();
}

void MainViewModel::OnMapServiceEvent( EMapServiceEvent event )
{
    BaseViewModel::OnMapServiceEvent( event );

    if ( event == EMapServiceEvent::Connected || event == EMapServiceEvent::Disconnected )
        UpdateMenuItems();
}

void MainViewModel::UpdateMenuItems()
{
    auto func1 = [&]()
    {
        std::map<std::string, std::any> params;
        params["mapView"] = m_mapView;

        m_navigationService->GoToView( EView::Maps, params );
    };

    auto func2 = [&]()
    {
        std::map<std::string, std::any> params;
        params["mapView"] = m_mapView;

        m_navigationService->GoToView(EView::Styles, params);
    };

    auto func3 = [&]()
    {
        std::map<std::string, std::any> params;
        params["mapView"] = m_mapView;

        m_navigationService->GoToView( EView::Preferences, params );
    };

    auto func4 = [&]() 
    {
        m_mapService->SetAllowConnection( !GetMapService()->IsConnected() );
    };

    auto func5 = [&]()
    {
        m_listener->OnEvent( EVmEvent::Generic_AppClose );
    };

    const char* connectStr = GetMapService()->IsConnected() ? "Disconnect" : "Connect";
    SetMenuItems( {
        { "Maps", func1 },
        { "Styles", func2 },
        { "Preferences", func3 },
        { connectStr, func4 },
        { "Exit", func5 }
        } );
}
