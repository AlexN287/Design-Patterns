// Copyright (C) 2019-2023, Magic Lane B.V.
// All rights reserved.
//
// This software is confidential and proprietary information of Magic Lane
// ("Confidential Information"). You shall not disclose such Confidential
// Information and shall use it only in accordance with the terms of the
// license agreement you entered into with Magic Lane.

#pragma once

#include "Entities.h"

class IMapView
{
public:
    // coordinates & distances
    virtual Coordinates GetCursorWgsPosition() const = 0;
    virtual Coordinates GetXyWgsPosition( Xy xy ) const = 0;

    virtual bool CenterOnCoordinates( Coordinates coordinates, int zoomLevel = -1 ) = 0;
    virtual bool CenterOnDefaultCoordinates() = 0;

    // other stuff
    virtual bool IsFpsRender() const = 0;
    virtual void SetRenderFps( bool renderFps ) = 0;

    virtual void SetMapStyleById( LargeInteger styleId, bool smoothTransition = false ) = 0;

    // handle events
    virtual void HandleTouch( ETouchEvent touchEvent, LargeInteger touchId, Xy xy ) = 0;
    virtual bool HandleKey( EKey key, EKeyAction action ) = 0;
    virtual void HandleScroll( int delta, Xy xy ) = 0;

    virtual ~IMapView() = default;
};
