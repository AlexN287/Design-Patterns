#pragma once
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

	virtual bool CheckWin() const = 0;
	virtual void NextMove(std::pair<int, int> position) = 0;
	virtual bool PositionEmpty(std::pair<int, int>position) const = 0;

	virtual ~ITicTacToe() = default;
};
