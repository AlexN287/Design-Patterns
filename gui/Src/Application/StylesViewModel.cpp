#include "StylesViewModel.h"

#include "MainView.h"

StylesViewModel::StylesViewModel(IMapService* mapService, INavigationService* navigationService, IViewModelListener* listener)
    : BaseViewModel(mapService, navigationService, listener)
{
    UpdateMenuItems();
}

void StylesViewModel::Init(const std::map<std::string, std::any>& params)
{
    auto it = params.find("mapView");
    if (it != params.end())
        m_mapView = std::any_cast<IMapViewPtr>(it->second);
    else
        m_mapView = GetMapService()->ProduceMapView();
}

void StylesViewModel::UpdateMenuItems()
{
    auto func1 = [&]()
    {
        std::map<std::string, std::any> params;
        params["mapView"] = m_mapView;

        m_navigationService->GoToView(EView::Main, params);
    };

    SetMenuItems({
        { "Main", func1 },
        });
}

IResourceRepository* StylesViewModel::GetResourceRepository()
{
    return GetMapService()->GetResourceRepository();
}

ITextureRepository* StylesViewModel::GetTextureRepository()
{
    return GetMapService()->GetTextureRepository();
}
