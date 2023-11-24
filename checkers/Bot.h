#pragma once
#include <iostream>
#include "Board.h"
#include "Move.h"
#include "Pawn.h"

using namespace std;

class Bot
{
	int color;
public:
	Bot(int color) : color(color) {};
	float Evaluate(Board& b);
	Move getBestMove(Board& b);
	Move getBestMoveBlack(Board& b);
	Move getBestMoveWhite(Board& b);
	int getColor() { return color; }
};

