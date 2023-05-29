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
#include <string>
#include <functional>

class ITextureRepository;
class IResourceRepository;

using IMapServicePtr = std::shared_ptr<class IMapService>;

using ComputeRoutesCallback = std::function<void( int, gem::String, gem::RouteList )>;
using DestinationReachedCallback = std::function<void( void )>;

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

    virtual IMapViewPtr GetMapView( RectF area = RectF( 0.0f, 0.0f, 1.0f, 1.0f ) ) = 0;

    virtual void Resize( Size size, float pixelRatio ) = 0;

    // Repositories
    virtual ITextureRepository* GetTextureRepository() = 0;
    virtual IResourceRepository* GetResourceRepository() = 0;

    virtual void UpdateMaps() = 0;

    // Render fps
    virtual bool IsRenderFps() const = 0;
    virtual void SetRenderFps( bool renderFps ) = 0;

    // Tick
    virtual void Tick() = 0;

    // operations
    virtual int ComputeRoutes( gem::LandmarkList waypoints, ComputeRoutesCallback callback, ETransportMode mode = ETransportMode::Car ) = 0;
    virtual void CancelComputeRoutes() = 0;

    virtual int StartNavigation( gem::Route route, DestinationReachedCallback callback ) = 0;
    virtual void StopNavigation() = 0;

    virtual gem::NavigationInstruction GetNavigationInstruction() = 0;

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
    virtual long int GetID() const = 0;
    virtual long int GetTotalSize() const = 0;
    virtual bool IsImagePreviewAvailable() const = 0;
    ///virtual gem::Image GetImagePreview() const = 0;
    virtual std::string FormatStringDownload(const char16_t* format) = 0;
    virtual std::string FormatStringDownload(const char16_t* format, const char* text) = 0;
    virtual void FallbackToLegacyUnicode() = 0;
    
    //virtual int GetDownloadProgress() const = 0;
    virtual std::string GetName() const = 0;
    //virtual gem::String getname2() = 0;
    virtual EItemState GetState() const = 0;
    virtual unsigned int GetTexture(int width, int height, bool sync = true) const = 0;
    virtual unsigned int GetTexture(const float iconSizeX, const float iconSizeY) const = 0;
    virtual void StartDownload() = 0;
    virtual void StopDownload() = 0;
    //virtual gem::StringListRef GetCountryCodes() = 0;
    virtual ~IMapElement() = default;
};

using IMapElementPtr = std::shared_ptr<IMapElement>;

class IMapsCollection
{
public:
    virtual int GetSize() const = 0;
    virtual IMapElementPtr GetItem(int index) const = 0;
    virtual bool isEmpty() const = 0;
    virtual ~IMapsCollection() = default;
    static std::shared_ptr<IMapsCollection> Produce(gem::ContentStoreItemList items, IResourceRepository* resourceRepository, ITextureRepository* textureRepository);
};

using IMapsCollectionPtr = std::shared_ptr<IMapsCollection>;


