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
using Positions = std::pair<int, int>;

class IStrategy
{
public:
	virtual ~IStrategy() = default;

	static IStrategyPtr Produce(EDifficulty type);

	virtual EDifficulty GetDifficultyType() const = 0;
	virtual Positions GetNextMove(const Board& m_board) const = 0;

	Positions GetRandomPosition(const Board& m_board) const;
	Positions GetBestPosition(const Board& m_board) const;

private:
	
};

