#include <iostream>

#include "ConsoleView.h"

int main()
{
	ITicTacToePtr game = ITicTacToe::Produce(EgameType::Implem1);

	ConsoleView consoleGame(game); 
	consoleGame.Run();
	return 0;
} 