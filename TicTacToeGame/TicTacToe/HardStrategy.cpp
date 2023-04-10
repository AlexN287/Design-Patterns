#include "HardStrategy.h"

EDifficulty HardStrategy::GetDifficultyType() const
{
	return EDifficulty::Hard;
}

Positions HardStrategy::GetNextMove(const Board& m_board) const
{
	return GetBestPosition(m_board);
}
