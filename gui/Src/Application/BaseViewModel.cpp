#include "BaseViewModel.h"

#include "IView.h"
#include "IResourceRepository.h"

BaseViewModel::BaseViewModel( IMapService* mapService, INavigationService* navigationService, IViewModelListener* listener )
    : m_mapService( mapService )
    , m_navigationService( navigationService )
    , m_listener( listener )
{
    m_mapService->AddListener( this );
}

BaseViewModel::~BaseViewModel()
{
    m_mapService->RemoveListener( this );
}

void BaseViewModel::OnScroll( int delta, Xy xy )
{
    if (m_mapView)
        m_mapView->HandleScroll( delta, xy );
}

void BaseViewModel::OnTouch( ETouchEvent event, LargeInteger fingerId, Xy xy )
{
    if (m_mapView)
        m_mapView->HandleTouch( event, fingerId, xy );
}

void BaseViewModel::OnKey( EKey key, EKeyAction keyAction )
{
    if (m_mapView)
        m_mapView->HandleKey( key, keyAction );
}

void BaseViewModel::OnResize( int width, int height, float pixelRatio )
{
    if (m_mapService)
        m_mapService->Resize( Size( width, height ), pixelRatio );
}

const MenuItems& BaseViewModel::GetMenuItems() const
{
    return m_menuItems;
}

bool BaseViewModel::IsConnected() const
{
    return m_mapService->IsConnected();
}

void BaseViewModel::UpdateMaps()
{
    m_mapService->GetResourceRepository()->UpdateMaps();
}

void BaseViewModel::OnMapServiceEvent( EMapServiceEvent event )
{
    switch ( event )
    {
    case EMapServiceEvent::Connected:
        break;
    case EMapServiceEvent::Disconnected:
        break;
    case EMapServiceEvent::ExpiredMaps:
    {
        m_listener->OnEvent( EVmEvent::Generic_MapsExpired );
        break;
    }
    case EMapServiceEvent::NewMaps:
    {
        m_listener->OnEvent( EVmEvent::Generic_NewMaps );
        break;
    }
    case EMapServiceEvent::NewStyles:
        break;
    }
}

void BaseViewModel::SetMenuItems( const MenuItems& items )
{
    m_menuItems = items;
}

IMapService* BaseViewModel::GetMapService()
{
    return m_mapService;
}

IMapViewPtr BaseViewModel::GetMapView()
{
	return m_mapView;
}
