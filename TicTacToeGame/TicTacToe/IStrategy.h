#pragma once

#include"Board.h"

#include<memory>
#include<utility>
#include<vector>
#include <random>

enum class EDifficulty
{
	Easy,
	Medium,
	Hard
};

using IStrategyPtr = std::shared_ptr<class IStrategy>;

class IStrategy
{
public:
	/*IStrategy(Board board)
	{
		m_board = board;
		m_emptyCells = m_board.GetEmptyCells();
	}*/

	virtual ~IStrategy() = default;

	static IStrategyPtr Produce(EDifficulty type);

	virtual EDifficulty GetDifficultyType() const = 0;
	virtual std::pair<int, int> GetNextMove(const Board& m_board) const = 0;

	std::pair<int, int> GetRandomPosition(const Board& m_board) const
	{
		std::vector<std::pair<int, int>> emptyCells = m_board.GetEmptyCells();

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, emptyCells.size() - 1);

		std::pair<int, int> randomPosition = emptyCells[dis(gen)];

		return randomPosition;
	}

	std::pair<int, int> GetBestPosition(const Board& m_board) const
	{
		//NU EU AM SCRIS ASTA
		for (int i = 0; i < m_board.GetSize(); i++)
		{
			if (m_board.GetValue(i, 0) != NULL && m_board.GetValue(i, 0) == m_board.GetValue(i, 1) && m_board.GetValue(i, 2) == NULL)
				return std::make_pair(i, 2);
			else if(m_board.GetValue(i,0)!=NULL && m_board.GetValue(i, 0) == m_board.GetValue(i, 2) && m_board.GetValue(i, 1) == NULL)
				return std::make_pair(i, 1);
			else if(m_board.GetValue(i, 1) != NULL && m_board.GetValue(i, 1) == m_board.GetValue(i, 2) && m_board.GetValue(i, 0) == NULL)
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

private:
	Board m_board;
	std::vector<std::pair<int, int>> m_emptyCells;
};

class EasyStrategy : public IStrategy
{
public:

	EDifficulty GetDifficultyType() const override
	{
		return EDifficulty::Easy;
	}

	std::pair<int, int> GetNextMove(const Board& m_board) const override
	{
		return GetRandomPosition(m_board);
	}
};

class MediumStrategy : public IStrategy
{
public:
	EDifficulty GetDifficultyType() const override
	{
		return EDifficulty::Medium;
	}

	std::pair<int, int> GetNextMove(const Board& m_board) const override
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
};

class HardStrategy : public IStrategy
{
public:

	EDifficulty GetDifficultyType() const override
	{
		return EDifficulty::Hard;
	}

	std::pair<int, int> GetNextMove(const Board& m_board) const override
	{
		return GetBestPosition(m_board);
	}
};

//class MultiplayerStrategy :public IStrategy
//{
//public:
//
//	EDifficulty GetDifficultyType() const override
//	{
//		return EDifficulty::Multiplayer;
//	}
//
//	std::pair<int, int> GetNextMove(const Board& m_board) const override
//	{
//
//	}
//};
