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
bool generate_captures_pawn(list<Move>& l, Board& b, int i, int j, Move m);
bool generate_captures_king(list<Move>& l, Board& b, int i, int j, Move m);

bool is_any_capture_on_board(Board& b, int color);
bool is_any_capture_pawn(Board& b, int i, int j);
bool is_any_capture_king(Board& b, int i, int j);

void promote_pawns(Board&);

void make_move(Board&, Move);
void make_move_not_capture(Board&, Move);
void make_move_capture(Board&, Move);
//void make_move_capture_pawn(Board&, Move);
//void make_move_capture_king(Board&, Move);
void delete_pawn_between(Board&, Field, Field); // if is a pawn between field 1 and field 2 there will be deleted field 1 and field 2 must be on the same diagonal


