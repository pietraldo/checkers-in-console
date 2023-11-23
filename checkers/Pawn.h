#pragma once
#include <iostream>
#include <list>
#include "Board.h"
#include "Move.h"

// returns true if something was added to list
bool generate_all_moves(list<Move>& l, Board& b, int color);
bool generate_all_not_capture_moves(list<Move>& l, Board& b, int color);
bool generate_all_captures(list<Move>& l, Board& b, int color);

bool generate_moves_pawn(list<Move>& l, Board& b, int i, int j);
bool generate_moves_pawn_white(list<Move>& l, Board& b, int i, int j);
bool generate_moves_pawn_black(list<Move>& l, Board& b, int i, int j);
bool generate_moves_king(list<Move>& l, Board& b, int i, int j);
bool generate_captures_pawn(list<Move>& l, Board& b, int i, int j);
bool generate_captures_king(list<Move>& l, Board& b, int i, int j);

void make_move(Board&, Move);
void make_move_not_capture(Board&, Move);
void make_move_capture(Board&, Move);
void make_move_capture_pawn(Board&, Move);
void make_move_capture_king(Board&, Move);

// function to avoid duplicating code
bool help_function1(list<Move>& l, Board& b, int color, bool (*function_kings)(list<Move>&, Board&, int, int), bool (*function_pawns)(list<Move>&, Board&, int, int));
