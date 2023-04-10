#include "HardStrategy.h"

EDifficulty HardStrategy::GetDifficultyType() const
{
	return EDifficulty::Hard;
}

std::pair<int, int> HardStrategy::GetNextMove(const Board& m_board) const
{
	return GetBestPosition(m_board);
}
