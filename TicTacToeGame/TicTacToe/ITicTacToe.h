#pragma once

#include "ITicTacToeListener.h"

#include <utility>
#include <memory>

using ITicTacToePtr = std::shared_ptr<class ITicTacToe>;

enum class EgameType
{
	Implem1,
	Implem2
};

class ITicTacToe
{
public:
	static ITicTacToePtr Produce(EgameType type);

	virtual void AddTicTacToeListener(ITicTacToeListener* listener) = 0;
	virtual void RemoveTicTacToeListener(ITicTacToeListener* listener) = 0;

	virtual bool CheckWin() const = 0;
	virtual void NextMove(std::pair<int, int> position) = 0;
	virtual bool PositionEmpty(std::pair<int, int>position) const = 0;

	virtual ~ITicTacToe() = default;
};
