#pragma once

#include "BaseViewModel.h"

#include "IView.h"

class PreferencesViewModel : public BaseViewModel
{
public:
    PreferencesViewModel( IMapService* mapService, INavigationService* navigationService, IViewModelListener* listener );

    void Init( const std::map<std::string, std::any>& params ) override;

    // specific methods
    bool IsRenderFps() const;
    void SetRenderFps( bool renderFps );
};
