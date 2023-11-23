#pragma once
#include <iostream>

using namespace std;

const int N = 8;
enum pieces { WHITE = 1, BLACK, WHITE_KING, BLACK_KING };

enum colors {
	color_white_field = 9,
	color_black_field = 1,
	color_black_pawn = 0,
	color_white_pawn = 15,
	color_move = 13,
	color_move_possibility = 4
};

const bool turn_board = false;

class Board
{
	int board[N*N/2];

public:
	Board(int board[N*N]);
	Board(int board[N][N]);

	bool static is_it_black_field(int i, int j) { return (i + j) % 2 == 0; };

	int& operator()(int i, int j);

	friend ostream& operator<<(ostream&, Board&);
};

