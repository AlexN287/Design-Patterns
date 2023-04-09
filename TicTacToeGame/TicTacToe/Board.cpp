#include "Board.h"

int Board::GetSize() const
{
	return BOARD_SIZE;
}

void Board::SetValue(char value, int i, int j)
{
	m_board[i][j] = value;
}

char Board::GetValue(int i, int j) const
{
	return m_board[i][j];
}

std::vector<std::pair<int, int>> Board::GetEmptyCells() const
{
	std::vector<std::pair<int, int>> emptyCells;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (m_board[i][j] == NULL)
			{
				emptyCells.push_back(std::make_pair(i, j));
			}
		}
	}

	return emptyCells;
}
