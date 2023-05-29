#pragma once
#include "INavigationInstructionItem.h"
#include "NavigationViewModel.h"
#include "NavigationView.h"

class NavigationInstructionItem : INavigationInstructionItem
{
private:
    gem::NavigationInstruction m_instruction;
public:
    NavigationInstructionItem(gem::NavigationInstruction instruction);
    virtual gem::TimeDistance GetTimeDistanceToNextTurn() override;
    virtual gem::StringRef GetNextTurnInstruction() override;
    virtual bool IsDefault() override;
    virtual gem::TimeDistance GetRemainingTravelTimeDistance() override;
    virtual gem::sense::PositionPtr GetCurrentPosition() override;
    virtual gem::TurnDetailsRef GetNextTurnDetails() const override;
    virtual bool IsNavigationInstructionNull() override;
};
