// Copyright (C) 2019-2023, Magic Lane B.V.
// All rights reserved.
//
// This software is confidential and proprietary information of Magic Lane
// ("Confidential Information"). You shall not disclose such Confidential
// Information and shall use it only in accordance with the terms of the
// license agreement you entered into with Magic Lane.

#pragma once

#include "IMapView.h"

#include "API/GEM_MapView.h"

class MapView : public IMapView, private gem::IMapViewListener
{
public:
    MapView( gem::StrongPointer<gem::Screen> screen, RectF area, float dpi );

    // coordinates & distances
    Coordinates GetCursorWgsPosition() const override;
    Coordinates GetXyWgsPosition( Xy xy ) const override;

    bool CenterOnCoordinates( Coordinates coordinates, int zoomLevel = -1 ) override;
    bool CenterOnDefaultCoordinates() override;

    // other stuff
    bool IsFpsRender() const override;
    void SetRenderFps( bool renderFps ) override;

    void SetMapStyleById( LargeInteger styleId, bool smoothTransition = false ) override;

    void HandleTouch( ETouchEvent touchEvent, LargeInteger touchId, Xy xy ) override;
    bool HandleKey( EKey key, EKeyAction action ) override;
    void HandleScroll( int delta, Xy xy ) override;

private:
    // IMapViewListener impl
    void onLongDown( const gem::Xy& xy );

private:
    // Map objects
    gem::StrongPointer<gem::MapView> m_pView;
    gem::StrongPointer<gem::Screen> m_pScreen;

    bool m_bRenderFps;

    float m_dpi;

    Coordinates m_defaultCoordinates;
    int m_defaultZoom;
};
