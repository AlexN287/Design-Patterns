#pragma once

#include "BaseViewModel.h"

class StylesViewModel : public BaseViewModel
{
public:
    StylesViewModel(IMapService* mapService, INavigationService* navigationService, IViewModelListener* listener);

    void Init(const std::map<std::string, std::any>& params) override;

    void UpdateMenuItems();

    IResourceRepository* GetResourceRepository();
    ITextureRepository* GetTextureRepository();
};

