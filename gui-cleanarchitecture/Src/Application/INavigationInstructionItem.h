#pragma once
#include "Entities.h"

#include "WindowInfo.h"
#include "IMapServiceListener.h"
#include "INavigationService.h"
#include "IResourceRepository.h"
#include <API/GEM_Position.h>
#include "API/GEM_NavigationInstruction.h"

#include <memory>
#include <string>
#include <functional>

class INavigationInstructionItem
{
public:
    virtual gem::TimeDistance GetTimeDistanceToNextTurn() = 0;
    virtual gem::StringRef GetNextTurnInstruction() = 0;
    virtual bool IsDefault() = 0;
    virtual gem::TimeDistance GetRemainingTravelTimeDistance() = 0;
    virtual gem::sense::PositionPtr GetCurrentPosition() = 0;
    virtual gem::TurnDetailsRef GetNextTurnDetails() const = 0;
    virtual bool IsNavigationInstructionNull() = 0;
};
