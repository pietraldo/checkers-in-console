#pragma once
#include <iostream>
#include <thread>

#include "Board.h"
#include "Move.h"
#include "Pawn.h"

using namespace std;

const int draw_after_moves = 10;

class Bot
{
	int color;
public:
	static int number_of_evaluate_function;
	static float bot_eval;

	Bot(int color) : color(color) {};
	float Evaluate(Board& b);
	Move getBestMove(Board& b);
	Move getBestMoveBlack(Board& b);
	Move getBestMoveWhite(Board& b);

	void generateAllMovesToDepth(Board& b, int max_depth,int color, int depth = 1);
	float evaluateToDepth(Board& b, int max_depth,int color, float alpha, float beta, int depth = 1);
	Move pickBestMove(Board& b, int max_depth);

	// returns if possition is stable it means that there are no caputres on eather black or white
	bool is_possition_stable(Board &b, int color);
	
	Move pickBestMoveMultiThreading(Board& b);
	void evaluateToDepthMultiThreading(Board& b, int max_depth, int color, float alpha, float beta, float& answer, int depth = 1);

	int getColor() { return color; }
};

