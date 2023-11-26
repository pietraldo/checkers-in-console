#include "Board.h"
#include <Windows.h>
#include <iomanip>

// fields that are in printed in another color which mean fields that show move
vector<Field> color_fields_print = {};

int& Board::operator()(int i, int j)
{
	out_of_board = -1;
	if (i<0 || j<0 || i>=N || j>=N) // if cordinates points on field that is outside of board
		return out_of_board;
	if (!is_it_black_field(i, j)) // if cordinates points to white field
		return out_of_board;
	return board[N/2 * i + j / 2 ]; // scaling 
}

int& Board::operator()(Field f)
{
	return this->operator()(f.i,f.j);
}

int& Board::operator[](string s)
{
	return this->operator()(s[1] - '1', s[0] - 'a');
}

Board::Board()
{
	for (int i = 0; i < 32; i++)
	{
		if (i < 12)
			board[i] = 1;
		else if (i < 20)
			board[i] = 0;
		else
			board[i] = 2;
	}
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

Board::Board(const Board& b)
{
	moves_with_kings = b.moves_with_kings;
	for (int i = 0; i < N * N / 2; i++)
	{
		board[i] = b.board[i];
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
			
			for(int ii=0; ii<color_fields_print.size(); ii++)
				if(color_fields_print[ii].i==i && color_fields_print[ii].j == j)
					color_field = color_move;
			
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

bool Board::is_black(int i, int j)
{
	int c=this->operator()(i, j);
	return (c == 2 || c == 4);
}
bool Board::is_white(int i, int j)
{
	int c = this->operator()(i, j);
	return (c == 1 || c == 3);
}