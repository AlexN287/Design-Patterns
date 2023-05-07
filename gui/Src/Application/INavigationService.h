#pragma once

#include "EView.h"

#include "IViewFactory.h"
#include "IViewModelFactory.h"

#include <map>
#include <string>
#include <any>
#include <functional>
#include <memory>

using Params = std::map<std::string, std::any>;

using ViewChangeCallback = std::function<void( IView* )>;

class INavigationService
{
public:
    virtual bool GoToView( EView view, const Params& params = Params() ) = 0;

    virtual void SetViewFactory( IViewFactory* factory ) = 0;
    virtual void SetViewModelFactory( IViewModelFactory* factory ) = 0;

    virtual void SetViewChangeCallback( ViewChangeCallback callback ) = 0;

    virtual ~INavigationService() = default;
};

using INavigationServicePtr = std::unique_ptr<INavigationService>;
