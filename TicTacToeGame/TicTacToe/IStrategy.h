#pragma once

#include<memory.h>
#include<utility>

enum class EDifficulty
{
	Easy,
	Medium,
	Hard
};

class IStrategy
{
public:
	virtual ~IStrategy() = default;

	virtual EDifficulty GetDifficultyType() const = 0;
	virtual std::pair<int, int> GetNextMove() const = 0;
};

class EasyStrategy : public IStrategy
{
public:

	EDifficulty GetDifficultyType() const override
	{
		return EDifficulty::Easy;
	}

	std::pair<int, int> GetNextMove() const override
	{
		//TO DO
	}
};

class MediumStrategy : public IStrategy
{
public:

	EDifficulty GetDifficultyType() const override
	{
		return EDifficulty::Medium;
	}

	std::pair<int, int> GetNextMove() const override
	{
		//TO DO
	}
};

class HardStrategy : public IStrategy
{
public:

	EDifficulty GetDifficultyType() const override
	{
		return EDifficulty::Hard;
	}

	std::pair<int, int> GetNextMove() const override
	{
		//TO DO
	}
};

