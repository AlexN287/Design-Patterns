#pragma once

#include "IMapService.h"

#include "IViewModel.h"
#include "IViewModelListener.h"

#include "Entities.h"

#include "INavigationService.h"

class IView;

class BaseViewModel : public IViewModel, public IMapServiceListener
{
public:
    BaseViewModel( IMapService* mapService, INavigationService* navigationService, IViewModelListener* listener );
    virtual ~BaseViewModel();

    // IViewModel methods (notified via MainWindow)
    void OnScroll( int delta, Xy xy ) override;
    void OnTouch( ETouchEvent event, LargeInteger fingerId, Xy xy ) override;
    void OnKey( EKey key, EKeyAction action ) override;

    void OnResize( int width, int height, float pixelRatio ) override;

    const MenuItems& GetMenuItems() const override;

    bool IsConnected() const override;

    void UpdateMaps() override;
    
    // TODO to remove !!!
    IMapViewPtr GetMapView();

    // IMapServiceListener methods
    void OnMapServiceEvent( EMapServiceEvent event ) override;

protected:
    void SetMenuItems( const MenuItems& items );

    virtual IMapService* GetMapService();

protected:
    IMapService* m_mapService;
    INavigationService* m_navigationService;

    IViewModelListener* m_listener;

    IMapViewPtr m_mapView;

    MenuItems m_menuItems;
};
