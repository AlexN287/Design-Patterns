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
#include "IMapService.h"
#include "SDKUtils.h"

#include "API/GEM_NavigationService.h"
#include "API/GEM_OperationScheduler.h"

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
    , m_activeOperation( EOperation::None )
{
    m_textureRepository = new TextureRepository();
    m_resourceRepository = new ResourceRepository();

    const char* token = std::getenv( "GEM_TOKEN" );
    if ( token )
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

IMapViewPtr MagicLaneMapService::GetMapView( RectF area )
{
    if (!m_mapView)
    {
        m_mapView = std::make_shared<MapView>( m_screen, area, m_openGLContext->getDpi() );
        m_mapView->SetRenderFps( m_bRenderFps );
    }

    return m_mapView;
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

void MagicLaneMapService::UpdateMaps()
{
	GetResourceRepository()->UpdateMaps();
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

// Progress listener
using ProgressCompleteFunc = std::function<void( int, gem::String )>;

class ProgressListenerImpl : public gem::IProgressListener
{
public:
    ProgressListenerImpl( ProgressCompleteFunc func )
        : m_func( func )
    {

    }

    virtual void notifyStart( bool hasProgress ) override
    {

    }

    virtual void notifyComplete( int reason, gem::String hint = gem::String() ) override
    {
        m_func( reason, hint );
    }

private:
    ProgressCompleteFunc m_func;
};
// end progress listener

int MagicLaneMapService::ComputeRoutes( gem::LandmarkList waypoints, ComputeRoutesCallback callback, ETransportMode mode /*= ETransportMode::Car*/ )
{
    gem::ERouteTransportMode transportMode = gem::RTM_Car;
    gem::EBikeProfile bikeProfile = gem::EBikeProfile::BP_Road;
    bool isSpecific = false;

    switch ( mode )
    {
    case ETransportMode::Car:
        transportMode = gem::RTM_Car;
        break;
    case ETransportMode::Truck:
        transportMode = gem::RTM_Lorry;
        break;
    case ETransportMode::Bike:
        transportMode = gem::RTM_Bicycle;
        break;
    case ETransportMode::Pedestrian:
        transportMode = gem::RTM_Pedestrian;
        break;
    case ETransportMode::RoadBike:
        transportMode = gem::RTM_Bicycle;
        bikeProfile = gem::EBikeProfile::BP_Road;
        isSpecific = true;
        break;
    case ETransportMode::CrossBike:
        transportMode = gem::RTM_Bicycle;
        bikeProfile = gem::EBikeProfile::BP_Cross;
        isSpecific = true;
        break;
    case ETransportMode::CityBike:
        transportMode = gem::RTM_Bicycle;
        bikeProfile = gem::EBikeProfile::BP_City;
        isSpecific = true;
        break;
    case ETransportMode::MountainBike:
        transportMode = gem::RTM_Bicycle;
        bikeProfile = gem::EBikeProfile::BP_Mountain;
        isSpecific = true;
        break;
    }

    if ( m_activeOperation != EOperation::None )
        return gem::error::KBusy;

    m_routes.clear();

    m_computeRoutesCallback = callback;

    auto func = [&]( int reason, gem::String hint )
    {
        m_operationListener.reset();

        if ( m_computeRoutesCallback )
        {
            m_computeRoutesCallback( reason, hint, m_routes );
            m_routes.clear();
            m_computeRoutesCallback = nullptr;
        }

        m_activeOperation = EOperation::None;
    };

    m_operationListener = gem::StrongPointerFactory<ProgressListenerImpl>( func );

    gem::RoutePreferences preferences;
    preferences.setTransportMode( transportMode );
    if ( isSpecific )
        preferences.setBikeProfile( bikeProfile );

    m_activeOperation = EOperation::ComputeRoute;

    int err = gem::RoutingService().calculateRoute( m_routes, waypoints, preferences, m_operationListener );

    if ( err != gem::KNoError )
    {
        m_activeOperation = EOperation::None;
        m_computeRoutesCallback = nullptr;
    }

    return err;
}

void MagicLaneMapService::CancelComputeRoutes()
{
    if ( m_activeOperation == EOperation::ComputeRoute && m_operationListener )
    {
        gem::RoutingService().cancelRoute( m_operationListener );
        m_operationListener.reset();
        m_routes.clear();
        m_activeOperation = EOperation::None;
    }
}

int MagicLaneMapService::StartNavigation( gem::Route route, DestinationReachedCallback callback )
{
	if ( m_activeOperation != EOperation::None )
		return gem::error::KBusy;

	m_destinationReachedCallback = callback;

	int err;

	m_activeOperation = EOperation::Simulate;

	m_navigationHandler = std::make_shared<NavigationHandler>( this, callback );

    err = gem::NavigationService().startSimulation( route, m_navigationHandler.get(), gem::ProgressListener(), 1 );

	if ( err != gem::KNoError )
	{
		m_activeOperation = EOperation::None;
		m_destinationReachedCallback = nullptr;
		m_navigationHandler = {};
	}

	return err;
}

void MagicLaneMapService::StopNavigation()
{
    if ( m_activeOperation == EOperation::Navigate || m_activeOperation == EOperation::Simulate )
    {
        if ( gem::NavigationService().isSimulationActive() || gem::NavigationService().isNavigationActive() )
            gem::NavigationService().cancelNavigation();

        // reset instruction text
        std::lock_guard<std::mutex> guard( m_sync );
        m_instruction = gem::NavigationInstruction();

        m_destinationReachedCallback = nullptr;

        m_navigationHandler = {};

        m_activeOperation = EOperation::None;
    }
}

gem::NavigationInstruction MagicLaneMapService::GetNavigationInstruction()
{
	std::lock_guard<std::mutex> guard( m_sync );

	return m_instruction;
}

void MagicLaneMapService::SetInstruction( const gem::NavigationInstruction& instruction )
{
    std::lock_guard<std::mutex> guard( m_sync );

    m_instruction = instruction;
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

NavigationHandler::NavigationHandler( MagicLaneMapService* mapService, DestinationReachedCallback callback )
    : m_mapService( mapService )
    , m_callback( callback )
{

}

void NavigationHandler::onNavigationInstructionUpdated( const gem::NavigationInstruction& instruction )
{
    m_mapService->SetInstruction( instruction );
}

void NavigationHandler::onDestinationReached( const gem::Landmark& )
{
    if ( m_callback )
        m_callback();

    auto stopNavFunc = [&]()
    {
        m_mapService->StopNavigation();
    };

    // execute async (otherwise dead-lock - the engine still keeps references
    // to used data sources until navigation completely ends after onDestinationReached)
    gem::OperationScheduler().timeoutOperation( 0, stopNavFunc, gem::ProgressListener(), true );
}

class MapElementImpl: public IMapElement
{
    gem::ContentStoreItem m_item;
    IResourceRepository* m_resourceRepository;
    ITextureRepository* m_textureRepository;

public:
    MapElementImpl(gem::ContentStoreItem item, IResourceRepository* resourceRepository, ITextureRepository* textureRepository):
        m_item{item},
        m_resourceRepository{resourceRepository},
        m_textureRepository{textureRepository}
    {
    }

    virtual long int GetID() const override
    {
        return m_item.getId();
    }

    virtual long int GetTotalSize() const override
    {
        return m_item.getTotalSize();
    }

    virtual std::string GetName() const override
    {
        return m_item.getName().toStdString().c_str();
    }

    virtual EItemState GetState() const override
    {
        switch (m_item.getStatus())
        {
        case gem::EContentStoreItemStatus::CIS_Completed:
            return EItemState::Completed;
        case gem::EContentStoreItemStatus::CIS_Unavailable:
            return EItemState::Unavailable;
        case gem::EContentStoreItemStatus::CIS_DownloadQueued:
        case gem::EContentStoreItemStatus::CIS_DownloadWaiting:
        case gem::EContentStoreItemStatus::CIS_DownloadWaitingFreeNetwork:
        case gem::EContentStoreItemStatus::CIS_DownloadRunning:
        case gem::EContentStoreItemStatus::CIS_UpdateWaiting:
            return EItemState::InProgress;
        case gem::EContentStoreItemStatus::CIS_Paused:
            return EItemState::Paused;
        }

        return EItemState::Other;
    }

    virtual unsigned int GetTexture(int width, int height, bool sync=true) const override
    {
        return m_textureRepository->GetTexture(m_item.getImagePreview(), width, height, sync);
    }

    virtual void StartDownload() override
    {
        m_resourceRepository->DownloadAsync(m_item);
    }

    virtual void StopDownload() override
    {
        m_item.pauseDownload();
    }

    virtual bool IsImagePreviewAvailable() const override
    {
        return m_item.isImagePreviewAvailable();   
    }

    virtual gem::Image GetImagePreview() const override
    {
        return m_item.getImagePreview();
    }

    /*virtual int GetDownloadProgress() const override
    {
        return m_item.getDownloadProgress();
    }*/

    virtual gem::String getname2() override
    {
        return m_item.getName();
    }

    virtual std::string FormatStringDownload(const char16_t* format) override
    {
        gem::String name = m_item.getName();
        return gem::String::formatString(format, m_item.getDownloadProgress(), name).toStdString();
    }

    virtual std::string FormatStringDownload(const char16_t* format, const char* text) override
    {
        gem::String name = m_item.getName();
        return gem::String::formatString(format, text, name).toStdString();
    }

    virtual void FallbackToLegacyUnicode() override
    {
        gem::String countryCode = m_item.getCountryCodes()[0];
        
        //return s.fallbackToLegacyUnicode().toStdString();
        
        countryCode.fallbackToLegacyUnicode();
    }

    unsigned int GetTexture(const float iconSizeX, const float iconSizeY) const override
    {
        gem::String countryCode = m_item.getCountryCodes()[0];
        return m_textureRepository->GetTexture(m_resourceRepository->GetFlagImage(countryCode), iconSizeX, iconSizeY);
    }

    virtual gem::StringListRef GetCountryCodes() override
    {
        return m_item.getCountryCodes();
    }
};

class MapsCollectionImpl : public IMapsCollection
{
public:
    MapsCollectionImpl(gem::ContentStoreItemList items, IResourceRepository* resourceRepository, ITextureRepository* textureRepository) :
        m_items{ items },
        m_resourceRepository{ resourceRepository },
        m_textureRepository{ textureRepository }
    {
    }


    virtual int GetSize() const override
    {
        return m_items.size();
    }

    virtual IMapElementPtr GetItem(int index) const override
    {
        return std::make_shared<MapElementImpl>(m_items[index], m_resourceRepository, m_textureRepository);
    }

    virtual bool isEmpty() const override
    {
        return m_items.empty();
    }

    

private:
    //std::vector<MapsCollectionImpl> m_mapsCollection;
    gem::ContentStoreItemList m_items;
    ITextureRepository* m_textureRepository;
    IResourceRepository* m_resourceRepository;
};


std::shared_ptr<IMapsCollection> IMapsCollection::Produce(gem::ContentStoreItemList items, IResourceRepository* resourceRepository, ITextureRepository* textureRepository)
{
    return std::make_shared<MapsCollectionImpl>(items, resourceRepository, textureRepository);
}

