// Copyright (C) 2019-2023, Magic Lane B.V.
// All rights reserved.
//
// This software is confidential and proprietary information of Magic Lane
// ("Confidential Information"). You shall not disclose such Confidential
// Information and shall use it only in accordance with the terms of the
// license agreement you entered into with Magic Lane.

#include "MagicLaneMapService.h"

#include "OpenGLContextImpl.h"
#include "TextureRepository.h"
#include "ResourceRepository.h"

#include "MapView.h"

#include "SDKUtils.h"

IMapServicePtr IMapService::Produce( const std::string& logFile )
{
    SDKUtils* sdkUtils = new SDKUtils();

    if ( sdkUtils->InitSDK( logFile ) != gem::KNoError )
    {
        delete sdkUtils;
        return nullptr;
    }

    return std::make_shared<MagicLaneMapService>( sdkUtils );
}

MagicLaneMapService::MagicLaneMapService( SDKUtils* sdkUtils )
    : m_sdkUtils( sdkUtils )
    , m_bConnected( false )
    , m_bHasToken( false )
    , m_bRenderFps( false )
{
    m_textureRepository = new TextureRepository();
    m_resourceRepository = new ResourceRepository();

    const char* token = std::getenv( "GEM_TOKEN" );
    if (token)
    {
        m_settings.setAppAuthorization( token );
        m_bHasToken = true;
    }

    SetAllowConnection( true );
}

MagicLaneMapService::~MagicLaneMapService()
{
    m_textureRepository->UnloadAllTextures();

    if ( m_textureRepository )
        delete m_textureRepository;

    if ( m_resourceRepository )
        delete m_resourceRepository;

    delete m_sdkUtils;
}

void MagicLaneMapService::AddListener( IMapServiceListener* listener )
{
    m_listeners.push_back( listener );
}

void MagicLaneMapService::RemoveListener( IMapServiceListener* listener )
{
    for ( auto it = m_listeners.begin(); it != m_listeners.end();)
    {
        if ( *it == listener )
            it = m_listeners.erase( it );
        else
            it++;
    }
}

bool MagicLaneMapService::HasToken() const
{
    return m_bHasToken;
}

bool MagicLaneMapService::IsConnected() const
{
    return m_bConnected;
}

void MagicLaneMapService::SetAllowConnection( bool allowConnection )
{
    m_settings.setAllowConnection( allowConnection, this );
}

void MagicLaneMapService::InitGLContext( const WindowInfo& windowInfo )
{
    m_openGLContext = std::make_unique<OpenGLContextImpl>(
        windowInfo.openGLContext,
        windowInfo.width,
        windowInfo.height,
        windowInfo.ddpi,
        windowInfo.pixelRatio,
        windowInfo.updateOpenGLRenderContextFunc
        );

    m_screen = gem::Screen::produce( m_openGLContext.get(), gem::RR_OnDemand );
}

IMapViewPtr MagicLaneMapService::ProduceMapView( RectF area )
{
    auto mapView = std::make_shared<MapView>( m_screen, area, m_openGLContext->getDpi() );
    mapView->SetRenderFps( m_bRenderFps );
    return mapView;
}

void MagicLaneMapService::Resize( Size size, float pixelRatio )
{
    if (m_screen)
        m_screen->resize( gem::Size( size.width, size.height ) );

    if(m_openGLContext)
        m_openGLContext->SetPixelRatio( pixelRatio );
}

ITextureRepository* MagicLaneMapService::GetTextureRepository()
{
    return m_textureRepository;
}

IResourceRepository* MagicLaneMapService::GetResourceRepository()
{
    return m_resourceRepository;
}

bool MagicLaneMapService::IsRenderFps() const
{
    return m_bRenderFps;
}

void MagicLaneMapService::SetRenderFps( bool renderFps )
{
    m_bRenderFps = renderFps;
}

void MagicLaneMapService::Tick ()
{
    m_sdkUtils->Tick ();

    m_screen->render();
}

void MagicLaneMapService::onConnectionStatusUpdated( bool connected )
{
    m_bConnected = connected;

    if ( m_resourceRepository )
        m_resourceRepository->SetConnected( connected );

    for ( auto it : m_listeners )
        it->OnMapServiceEvent( connected ? EMapServiceEvent::Connected : EMapServiceEvent::Disconnected );
}

void MagicLaneMapService::onWorldwideRoadMapSupportStatus( EStatus state )
{
    if(state == EStatus::ExpiredData)
        for ( auto it : m_listeners )
            it->OnMapServiceEvent( EMapServiceEvent::ExpiredMaps );

    if ( state == EStatus::OldData )
        for ( auto it : m_listeners )
            it->OnMapServiceEvent( EMapServiceEvent::NewMaps );
}

void MagicLaneMapService::onAvailableContentUpdate( int type, EStatus state )
{
    for ( auto it : m_listeners )
        it->OnMapServiceEvent( EMapServiceEvent::NewStyles );
}
