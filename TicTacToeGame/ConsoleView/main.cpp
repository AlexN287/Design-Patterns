#include <iostream>
#include "ITicTacToe.h"

int main()
{
	auto game = ITicTacToe::Produce(EgameType::Implem1);

	std::cout << game->CheckWin() << std::endl;
	return 0;
}