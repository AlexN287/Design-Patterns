#include "ViewModelFactory.h"

#include "IMapService.h"
#include "INavigationService.h"
#include "IViewModelListener.h"

#include "MainViewModel.h"
#include "MapsViewModel.h"
#include "PreferencesViewModel.h"
#include "StylesViewModel.h"

ViewModelFactory::ViewModelFactory( IMapService* mapService, INavigationService* navigationService )
    : m_mapService( mapService )
    , m_navigationService( navigationService )
{

}

IViewModel* ViewModelFactory::BuildViewModel( EView viewType, IViewModelListener* listener )
{
    switch (viewType)
    {
    case EView::Main:
        return new MainViewModel( m_mapService, m_navigationService, listener );
    case EView::Maps:
        return new MapsViewModel( m_mapService, m_navigationService, listener );
    case EView::Preferences:
        return new PreferencesViewModel( m_mapService, m_navigationService, listener );
    case EView::Styles:
        return new StylesViewModel(m_mapService, m_navigationService, listener);
    }

    return nullptr;
}
