#pragma once

#include "Entities.h"

#include <vector>
#include <string>
#include <map>
#include <any>
#include <functional>

class IView;
class IViewModelListener;

using MenuItemText = std::string;
using MenuItemAction = std::function<void( void )>;
using MenuItem = std::pair < MenuItemText, MenuItemAction >;
using MenuItems = std::vector<MenuItem>;

class IViewModel
{
public:
    virtual void Init( const std::map<std::string, std::any>& params ) = 0;

    virtual void OnScroll( int delta, Xy xy ) = 0;
    virtual void OnTouch( ETouchEvent event, LargeInteger fingerId, Xy xy ) = 0;
    virtual void OnKey( EKey key, EKeyAction action ) = 0;

    virtual void OnResize( int width, int height, float pixelRatio ) = 0;

    virtual bool IsConnected() const = 0;
    virtual void UpdateMaps() = 0;

    virtual const MenuItems& GetMenuItems() const = 0;

    virtual ~IViewModel() = default;
};
