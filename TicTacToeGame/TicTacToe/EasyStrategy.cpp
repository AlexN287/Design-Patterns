#include"EasyStrategy.h"

EDifficulty EasyStrategy::GetDifficultyType() const
{
	return EDifficulty::Easy;
}

Positions EasyStrategy::GetNextMove(const Board& m_board) const
{
	return GetRandomPosition(m_board);
}
