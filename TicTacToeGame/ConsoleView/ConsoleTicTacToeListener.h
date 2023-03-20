#pragma once

#include "ITicTacToeListener.h"

class ConsoleTicTacToeListener :public ITicTacToeListener
{
public:
	virtual void OnGameOver(std::string playerName);
	virtual void OnMakeMove(int i, int j);
	virtual void OnTie(bool isTie);
};

