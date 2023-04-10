#include "MediumStrategy.h"

EDifficulty MediumStrategy::GetDifficultyType() const
{
	return EDifficulty::Medium;
}

Positions MediumStrategy::GetNextMove(const Board& m_board) const
{
	return GetRandomPosition(m_board);
}
