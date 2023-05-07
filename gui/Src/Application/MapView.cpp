// Copyright (C) 2019-2023, Magic Lane B.V.
// All rights reserved.
//
// This software is confidential and proprietary information of Magic Lane
// ("Confidential Information"). You shall not disclose such Confidential
// Information and shall use it only in accordance with the terms of the
// license agreement you entered into with Magic Lane.

#include "MapView.h"

// for bike could be something like the following:
// (std::int64_t(gem::CT_ViewStyleHighRes) << 32) | 2538
const LargeInteger DEFAULT_MAP_STYLE_ID = 0;

MapView::MapView( gem::StrongPointer<gem::Screen> screen, RectF area, float dpi )
    : m_bRenderFps( false )
    , m_dpi( 1 )
    , m_defaultCoordinates( 45.65119, 25.60480 )
    , m_defaultZoom( 70 )
{
    gem::RectF gemArea( area.x, area.y, area.width, area.height );

    m_pView = gem::MapView::produce( screen, gemArea, this );
    m_pView->preferences().enableCursorRender( false );

    m_pScreen = screen;

    m_dpi = dpi;

    SetRenderFps( m_bRenderFps );

    CenterOnDefaultCoordinates();

    SetMapStyleById( DEFAULT_MAP_STYLE_ID );
}

Coordinates MapView::GetCursorWgsPosition() const
{
    auto coords = m_pView->getCursorWgsPosition();

    return Coordinates( coords.getLatitude(), coords.getLongitude() );
}

Coordinates MapView::GetXyWgsPosition( Xy xy ) const
{
    auto coords = m_pView->transformScreenToWgs( gem::Xy( xy.x, xy.y ) );
    return Coordinates( coords.getLatitude(), coords.getLongitude() );
}

bool MapView::CenterOnCoordinates( Coordinates coordinates, int zoomLevel /*= -1 */ )
{
    gem::Coordinates coords( coordinates.latitude, coordinates.longitude );

    if (!coords.isDefault())
    {
        m_pView->centerOnCoordinates( coords, zoomLevel, gem::Xy(), gem::Animation(), 0.0, 0.0 );

        return true;
    }

    return false;
}

bool MapView::CenterOnDefaultCoordinates()
{
    return CenterOnCoordinates( m_defaultCoordinates, m_defaultZoom );
}

bool MapView::IsFpsRender() const
{
    return m_bRenderFps;
}

void MapView::SetRenderFps( bool renderFps )
{
    m_bRenderFps = renderFps;

    if (m_pScreen && m_pView)
    {
        if (renderFps)
        {
            int height = m_pScreen->getViewport().height;
            m_pView->preferences().setDrawFPS( true, gem::Xy( 0, height / 2 ) );
        }
        else
            m_pView->preferences().setDrawFPS( false, gem::Xy() );
    }
}

void MapView::SetMapStyleById(LargeInteger styleId, bool smoothTransition /*= false*/)
{
    m_pView->preferences().setMapStyleById(styleId, smoothTransition);
}

#include "API/GEM_Debug.h"

void MapView::HandleTouch( ETouchEvent touchEvent, LargeInteger touchId, Xy xy )
{
    switch (touchEvent)
    {
    case ETouchEvent::TE_Down:
        gem::Debug().log( gem::LogInfo, "ResourceRepository", __FUNCTION__, __FILE__, __LINE__, "MapView::TOUCH_DOWN" );
        break;
    case ETouchEvent::TE_Move:
        gem::Debug().log( gem::LogInfo, "ResourceRepository", __FUNCTION__, __FILE__, __LINE__, "MapView::TOUCH_MOVE" );
        break;
    case ETouchEvent::TE_Up:
        gem::Debug().log( gem::LogInfo, "ResourceRepository", __FUNCTION__, __FILE__, __LINE__, "MapView::TOUCH_UP" );
        break;
    }

    m_pScreen->handleTouchEvent( gem::ETouchEvent(touchEvent), touchId, gem::Xy( xy.x, xy.y ) );
}

bool MapView::HandleKey( EKey key, EKeyAction action )
{
    return m_pView->handleKeyboardEvent( gem::EKey( key ), gem::EKeyAction( action ) );
}

void MapView::HandleScroll( int delta, Xy xy )
{
    m_pScreen->scrollEvent( delta, gem::Xy( xy.x, xy.y ) );
}

void MapView::onLongDown( const gem::Xy& xy )
{
    
}
