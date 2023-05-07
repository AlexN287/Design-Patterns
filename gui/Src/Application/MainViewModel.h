#pragma once

#include "BaseViewModel.h"

class MainViewModel : public BaseViewModel
{
public:
    MainViewModel( IMapService* mapService, INavigationService* navigationService, IViewModelListener* listener );

    void Init( const std::map<std::string, std::any>& params ) override;

    void OnMapServiceEvent( EMapServiceEvent event );

    void UpdateMenuItems();
};
