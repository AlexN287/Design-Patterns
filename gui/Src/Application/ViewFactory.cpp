#include "ViewFactory.h"

#include "IMainWindow.h"

#include "MainView.h"
#include "MapsView.h"
#include "PreferencesView.h"
#include "StylesView.h"

ViewFactory::ViewFactory( IMainWindow& mainWindow ) 
    : m_mainWindow( mainWindow )
{

}

IView* ViewFactory::BuildView( EView viewType )
{
    switch (viewType)
    {
    case EView::Main:
        return new MainView( &m_mainWindow );
    case EView::Maps:
        return new MapsView( &m_mainWindow );
    case EView::Preferences:
        return new PreferencesView( &m_mainWindow );
    case EView::Styles:
        return new StylesView(&m_mainWindow);
    }

    return nullptr;
}
