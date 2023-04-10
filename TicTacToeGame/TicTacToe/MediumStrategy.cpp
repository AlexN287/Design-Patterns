#include "MediumStrategy.h"

EDifficulty MediumStrategy::GetDifficultyType() const
{
	return EDifficulty::Medium;
}

std::pair<int, int> MediumStrategy::GetNextMove(const Board& m_board) const
{
	/*std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(0.0f, 1.0f);

		if (dis(gen) > 0.5)
		{
			return GetBestPosition(m_board);
		}*/

	return GetRandomPosition(m_board);
}
