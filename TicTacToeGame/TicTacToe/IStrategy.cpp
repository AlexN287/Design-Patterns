#include "IStrategy.h"
#include "EasyStrategy.h"
#include "MediumStrategy.h"
#include "HardStrategy.h"

IStrategyPtr IStrategy::Produce(EDifficulty type)
{
	switch (type)
	{
	case EDifficulty::Easy:
		return std::make_shared<EasyStrategy>();
		break;

	case EDifficulty::Medium:
		return std::make_shared<MediumStrategy>();
		break;

	case EDifficulty::Hard:
		return std::make_shared<HardStrategy>();
		break;

	/*case EDifficulty::Multiplayer:
		return std::make_shared<MultiplayerStrategy>();
		break;*/
	}

	return {};
}

Positions IStrategy::GetRandomPosition(const Board& m_board) const
{
	std::vector<std::pair<int, int>> emptyCells = m_board.GetEmptyCells();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, emptyCells.size() - 1);

	std::pair<int, int> randomPosition = emptyCells[dis(gen)];

	return randomPosition;
}

Positions IStrategy::GetBestPosition(const Board& m_board) const
{
	for (int i = 0; i < m_board.GetSize(); i++)
	{
		if (m_board.GetValue(i, 0) != NULL && m_board.GetValue(i, 0) == m_board.GetValue(i, 1) && m_board.GetValue(i, 2) == NULL)
			return std::make_pair(i, 2);
		else if (m_board.GetValue(i, 0) != NULL && m_board.GetValue(i, 0) == m_board.GetValue(i, 2) && m_board.GetValue(i, 1) == NULL)
			return std::make_pair(i, 1);
		else if (m_board.GetValue(i, 1) != NULL && m_board.GetValue(i, 1) == m_board.GetValue(i, 2) && m_board.GetValue(i, 0) == NULL)
			return std::make_pair(i, 0);
	}

	for (int j = 0; j < m_board.GetSize(); j++)
	{
		if (m_board.GetValue(0, j) != NULL && m_board.GetValue(0, j) == m_board.GetValue(1, j) && m_board.GetValue(2, j) == NULL)
			return std::make_pair(2, j);
		else if (m_board.GetValue(0, j) != NULL && m_board.GetValue(0, j) == m_board.GetValue(2, j) && m_board.GetValue(1, j) == NULL)
			return std::make_pair(1, j);
		else if (m_board.GetValue(1, j) != NULL && m_board.GetValue(1, j) == m_board.GetValue(2, j) && m_board.GetValue(0, j) == NULL)
			return std::make_pair(0, j);
	}

	if (m_board.GetValue(0, 0) != NULL && m_board.GetValue(0, 0) == m_board.GetValue(1, 1) && m_board.GetValue(2, 2) == NULL)
		return std::make_pair(2, 2);
	if (m_board.GetValue(0, 0) != NULL && m_board.GetValue(0, 0) == m_board.GetValue(2, 2) && m_board.GetValue(1, 1) == NULL)
		return std::make_pair(1, 1);
	if (m_board.GetValue(1, 1) != NULL && m_board.GetValue(1, 1) == m_board.GetValue(2, 2) && m_board.GetValue(0, 0) == NULL)
		return std::make_pair(0, 0);

	if (m_board.GetValue(0, 2) != NULL && m_board.GetValue(0, 2) == m_board.GetValue(1, 1) && m_board.GetValue(2, 0) == NULL)
		return std::make_pair(2, 0);
	if (m_board.GetValue(0, 2) != NULL && m_board.GetValue(0, 2) == m_board.GetValue(2, 0) && m_board.GetValue(1, 1) == NULL)
		return std::make_pair(1, 1);
	if (m_board.GetValue(1, 1) != NULL && m_board.GetValue(1, 1) == m_board.GetValue(2, 0) && m_board.GetValue(0, 2) == NULL)
		return std::make_pair(0, 2);

	return GetRandomPosition(m_board);
}
