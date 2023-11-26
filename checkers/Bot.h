#pragma once
#include <iostream>
#include <thread>

#include "Board.h"
#include "Move.h"
#include "Pawn.h"

using namespace std;

extern const int draw_after_moves;

class Bot
{
	int color;
public:
	static int number_of_evaluate_function;
	static float bot_eval;

	Bot(int color) : color(color) {};

	// evalutate position on the board
	float Evaluate(Board& b);

	// main function of bot. it returns the best move for bot
	Move pickBestMove(Board& b, int max_depth);

	// evaluate position with alpha beta pruning, to the deep of max_deph
	float evaluateToDepth(Board& b, int max_depth,int color, float alpha, float beta, int depth = 1);

	// returns if possition is stable it means that there are no caputres on eather black or white
	bool is_possition_stable(Board &b, int color);
	
	int getColor() { return color; }
};

