#pragma once

#include"IStrategy.h"

class MediumStrategy : public IStrategy
{
public:
	EDifficulty GetDifficultyType() const override;
	std::pair<int, int> GetNextMove(const Board& m_board) const override;

};