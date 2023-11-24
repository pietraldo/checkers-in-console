#pragma once
#include <iostream>
#include <vector>
#include "Move.h"

using namespace std;

const int N = 8;
enum pieces { WHITE = 1, BLACK, WHITE_KING, BLACK_KING };

extern vector<Field> color_fields_print;

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
	int out_of_board = -1;

public:
	Board();
	Board(int board[N*N]);
	Board(int board[N][N]);
	Board(const Board&);

	bool static is_it_black_field(int i, int j) { return (i + j) % 2 == 0; };
	bool is_black(int i, int j);
	bool is_white(int i, int j);

	int& operator()(int i, int j);
	int& operator()(Field);
	int& operator[](string);

	friend ostream& operator<<(ostream&, Board&);
};

