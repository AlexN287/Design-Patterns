#pragma once

#include<string>
#include<utility>

class ITicTacToeListener
{
public:
	virtual void OnGameOver(std::string playerName) = 0;
	virtual void OnMakeMove(int i, int j) = 0;
	virtual void OnTie(bool isTie) = 0;
};