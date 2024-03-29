#pragma once

#include "ITicTacToe.h"
#include "Board.h"

#include <string>
#include <vector>
#include <array>

class TicTacToe :public ITicTacToe
{
public:
	TicTacToe() = default;
	~TicTacToe() = default;

	char GetValue(int i, int j) const override;

	bool CheckWin()const override;
	bool NextMove(std::pair<int, int> position) override;
	bool PositionEmpty(std::pair<int, int>position)const override;
	bool IsTie() const override;

	void AddTicTacToeListener(ITicTacToeListener* listener) override;
	void RemoveTicTacToeListener(ITicTacToeListener* listener) override;

	std::string GetCurrentPlayer() const override;
	void SetPlayersName(const std::string& namePlayer_1, const std::string& namePlayer_2) override;

private:
	Board m_board;
	int m_turnNumber = 1;
	std::string m_player1;
	std::string m_player2;

	std::vector<ITicTacToeListener*> listeners;

};

