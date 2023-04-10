#pragma once

#include"IStrategy.h"

class HardStrategy : public IStrategy
{
public:

	EDifficulty GetDifficultyType() const override;
	Positions GetNextMove(const Board& m_board) const override;

};
