#pragma once

#include "ITicTacToe.h"
#include "IStrategy.h"

#include<utility>
#include"Board.h"

class ConsoleView
{
public:
	ConsoleView(ITicTacToePtr game);
	~ConsoleView() = default;

	Positions GetInputPositions();
	void DisplayBoard();
	void Run();
	void GetPlayersName(std::string& namePlayer_1, std::string& namePlayer_2);
	Board GetBoard();
	void DisplayGameOptions();
	void DisplayGameDifficulties();

private:
	ITicTacToePtr m_game;
};

