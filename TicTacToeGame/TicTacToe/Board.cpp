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
