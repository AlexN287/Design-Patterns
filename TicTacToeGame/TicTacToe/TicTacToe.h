#pragma once

#include "ITicTacToe.h"

#include <string>
#include <vector>
#include <array>

class TicTacToe :public ITicTacToe
{
public:
	TicTacToe() = default;
	~TicTacToe() = default;

	std::array<std::array<char, 3>, 3> GetBoard() const override;

	bool CheckWin()const override;
	void NextMove(std::pair<int, int> position) override;
	bool PositionEmpty(std::pair<int, int>position)const override;

	void AddTicTacToeListener(ITicTacToeListener* listener) override;
	void RemoveTicTacToeListener(ITicTacToeListener* listener) override;

private:
	static const int BOARD_SIZE = 3;
	std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> m_board;
	int m_turnNumber;
	std::string m_player1;
	std::string m_player2;

	std::vector<ITicTacToeListener*> listeners;
};

