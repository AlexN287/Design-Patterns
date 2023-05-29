#pragma once
#include "NavigationInstructionItem.h"

NavigationInstructionItem::NavigationInstructionItem(gem::NavigationInstruction instruction)
{
    m_instruction = instruction;
}

gem::TimeDistance NavigationInstructionItem::GetTimeDistanceToNextTurn() {
    return m_instruction.getTimeDistanceToNextNextTurn();
}
gem::StringRef NavigationInstructionItem::GetNextTurnInstruction() {
    return m_instruction.getNextTurnInstruction();
}
bool NavigationInstructionItem::IsDefault()
{
    return m_instruction.isDefault();
}
gem::TimeDistance NavigationInstructionItem::GetRemainingTravelTimeDistance() {
    return m_instruction.getRemainingTravelTimeDistance();
}
gem::sense::PositionPtr NavigationInstructionItem::GetCurrentPosition() {
    return m_instruction.getCurrentPosition();
}
gem::TurnDetailsRef NavigationInstructionItem::GetNextTurnDetails() const {
    return m_instruction.getNextTurnDetails();
}

bool NavigationInstructionItem::IsNavigationInstructionNull()
{
    if (m_instruction) return false;

    return true;
}
