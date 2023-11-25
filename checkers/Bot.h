#pragma once
#include <iostream>
#include <thread>

#include "Board.h"
#include "Move.h"
#include "Pawn.h"

using namespace std;

class Bot
{
	int color;
public:
	static int aa;
	static float bot_eval;

	Bot(int color) : color(color) {};
	float Evaluate(Board& b);
	Move getBestMove(Board& b);
	Move getBestMoveBlack(Board& b);
	Move getBestMoveWhite(Board& b);

	void generateAllMovesToDepth(Board& b, int max_depth,int color, int depth = 1);
	float evaluateToDepth(Board& b, int max_depth,int color, float alpha, float beta, int depth = 1);
	Move pickBestMove(Board& b, int max_depth);
	
	Move pickBestMoveMultiThreading(Board& b);
	void evaluateToDepthMultiThreading(Board& b, int max_depth, int color, float alpha, float beta, float& answer, int depth = 1);

	int getColor() { return color; }
};

