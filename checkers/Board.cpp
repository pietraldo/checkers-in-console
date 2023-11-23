#include "Board.h"
#include <Windows.h>
#include <iomanip>



int& Board::operator()(int i, int j)
{
	return board[N/2 * i + j / 2 ];
}

Board::Board(int board[N*N])
{
	for (int i = 0; i < N*N; i++)
	{
		this->operator()(i/N, i%N) = board[i/N+i%N];
	}
}

Board::Board(int board[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			this->operator()(i, j) = board[i][j];
		}
	}
}

ostream& operator<<(ostream& out, Board& p)
{
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << endl << endl;
	for (int i = (turn_board) ? 0 : N - 1; i >= 0 && i < N; i += (turn_board) ? 1 : -1)
	{
		SetConsoleTextAttribute(hconsole, 15);//resetuje ustwaienia
		cout << "  " << fixed << setw(3) << i + 1 << " ";
		for (int j = (turn_board) ? N - 1 : 0; j < N && j >= 0; j += (turn_board) ? -1 : 1)
		{
			// setting color
			int color_pawn = ((p(i, j) == WHITE || (p(i, j) == WHITE_KING))) ? color_white_pawn : color_black_pawn;
			int color_field = (((i + j) % 2 == 0) ? color_black_field : color_white_field);
			SetConsoleTextAttribute(hconsole, color_pawn + (color_field<<4));
			if (Board::is_it_black_field(i,j))
			{
				switch (p(i, j))
				{
				case WHITE:
				case BLACK:
					cout << " o ";
					break;
				case WHITE_KING:
				case BLACK_KING:
					cout << " O ";
					break;
				default:
					cout << "   ";
					break;
				}
			}
			else
			{
				cout << "   ";
			}
			SetConsoleTextAttribute(hconsole, 15);//resetuje ustwaienia
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hconsole, 15);//resetuje ustwaienia
	cout << "      ";
	for (int i = (turn_board) ? N - 1 : 0; i >= 0 && i < N; i += (turn_board) ? -1 : 1)
		cout << " " << (char)('a' + i) << " ";


	SetConsoleTextAttribute(hconsole, 15);//resetuje ustwaienia
	cout << endl;
	return out;
}