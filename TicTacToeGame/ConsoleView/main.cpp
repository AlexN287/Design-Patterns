#include <iostream>

#include "ConsoleView.h"
#include "ConsoleTicTacToeListener.h"

int main()
{
	ITicTacToePtr game = ITicTacToe::Produce(EgameType::Implem1);

	ConsoleView consoleGame(game); 
	ConsoleTicTacToeListener listener;
	game->AddTicTacToeListener(&listener);

	
	consoleGame.Run();
	return 0;
} 