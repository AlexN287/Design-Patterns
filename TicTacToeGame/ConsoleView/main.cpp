#include <iostream>
#include "ITicTacToe.h"

int main()
{
	auto game = ITicTacToe::Produce(EgameType::Implem1);

	while (game->CheckWin() == false)
	{
		int row, column;
		std::cout << "Insert row:";
		std::cin >> row;
		std::cout << "Insert column:";
		std::cin >> column;
		game->NextMove(std::make_pair(row, column));
	}
	return 0;
}