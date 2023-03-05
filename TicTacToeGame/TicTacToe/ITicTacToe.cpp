#include "ITicTacToe.h"
#include "TicTacToe.h"

ITicTacToePtr ITicTacToe::Produce(EgameType type)
{
	if (type == EgameType::Implem1) {
		return std::make_shared<TicTacToe>();
	}

	return {};
}