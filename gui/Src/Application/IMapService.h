// Copyright (C) 2019-2023, Magic Lane B.V.
// All rights reserved.
//
// This software is confidential and proprietary information of Magic Lane
// ("Confidential Information"). You shall not disclose such Confidential
// Information and shall use it only in accordance with the terms of the
// license agreement you entered into with Magic Lane.

#pragma once

#include "Entities.h"

#include "WindowInfo.h"
#include "IMapServiceListener.h"
#include "IMapView.h"

#include <memory>

class ITextureRepository;
class IResourceRepository;

using IMapServicePtr = std::shared_ptr<class IMapService>;
using IMapViewPtr = std::shared_ptr<IMapView>;

class IMapService
{
public:
    static IMapServicePtr Produce( const std::string& logFile );

    virtual void AddListener( IMapServiceListener* listener ) = 0;
    virtual void RemoveListener( IMapServiceListener* listener ) = 0;

    virtual bool HasToken() const = 0;

    virtual bool IsConnected() const = 0;
    virtual void SetAllowConnection( bool allowConnection ) = 0;

    // MapView
    virtual void InitGLContext( const WindowInfo& windowInfo ) = 0;

    virtual IMapViewPtr ProduceMapView( RectF area = RectF( 0.0f, 0.0f, 1.0f, 1.0f ) ) = 0;

    virtual void Resize( Size size, float pixelRatio ) = 0;

    // Repositories
    virtual ITextureRepository* GetTextureRepository() = 0;
    virtual IResourceRepository* GetResourceRepository() = 0;

    // Render fps
    virtual bool IsRenderFps() const = 0;
    virtual void SetRenderFps( bool renderFps ) = 0;

    // Tick
    virtual void Tick() = 0;

    virtual ~IMapService() = default;
};

enum class EItemState
{
    Completed = 1,
    Unavailable,
    InProgress,
    Paused,
    Other
};

class IMapElement
{
public:
    long int GetID() const;
    std::string GetName() const;
    EItemState GetState() const;
    unsigned int GetTexture() const;
    void StartDownload();
    void StopDownload();
};

using IMapElementPtr = std::shared_ptr<IMapElement>;

class IMapsCollection
{
public:
    int GetSize() const;
    IMapElementPtr GetItem(int index) const;
};
