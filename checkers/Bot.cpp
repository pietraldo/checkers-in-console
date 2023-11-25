#include "Bot.h"

float Bot::Evaluate(Board& b)
{
	float white=0;
	float black=0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			switch (b(i, j))
			{
				case WHITE:
					white += 1;
					if (i > 3)
						white +=(float) (i-3)/3;
					break;
				case BLACK:
					black -= 1;
					if (i <4)
						black -= (float)(4-i) / 3;
					break;
				case WHITE_KING:
					white += 8;
					break;
				case BLACK_KING:
					black -= 8;
					break;
				default:
					break;
			}
		}
	}

	return white + black;
}

Move Bot::getBestMove(Board& b)
{
	if (color == WHITE)
		return getBestMoveWhite(b);
	return getBestMoveBlack(b);
}

Move Bot::getBestMoveWhite(Board& b)
{
	cout << "Avaible moves" << endl;
	list<Move> l;
	generate_all_moves(l, b, WHITE);
	return l.front();
}
Move Bot::getBestMoveBlack(Board& b)
{
	cout << "Avaible moves" << endl;
	list<Move> l;
	generate_all_moves(l, b, color);

	Move best = Move(l.front());
	float best_eval = 10000;
	for (auto m : l)
	{
		Board b2 = Board(b);
		make_move(b2, m);
		float current_eval=Evaluate(b2);
		cout << m << " -> " << current_eval<<endl;
		if (best_eval > current_eval)
		{
			best_eval = current_eval;
			best = Move(m);
		}
	}


	return best;
}

void Bot::generateAllMovesToDepth(Board& b, int max_depth, int color, int depth)
{
	
	if (depth >= max_depth)
	{
		cout << "Depth " << depth << ": " << endl;
		cout << b << endl;
		return;
	}
		

	list<Move> l;
	generate_all_moves(l, b, color);
	for (auto move : l)
	{
		Board b2 = Board(b);
		make_move(b2, move);
		generateAllMovesToDepth(b2, max_depth, color == WHITE ? BLACK : WHITE, depth+1);
	}
}


int Bot::aa = 0;
float Bot::bot_eval = 0;
float Bot::evaluateToDepth(Board& b, int max_depth, int color, float alpha, float beta, int depth)
{
	aa++;
	//cout << b;
	if (depth >= max_depth)
	{
		return Evaluate(b);
	}

	list<Move> l;
	generate_all_moves(l, b, color);

	float best=color==WHITE?-1000000:10000000;
	float value;

	for (auto move : l)
	{
		Board b2 = Board(b);
		make_move(b2, move);
		value=evaluateToDepth(b2, max_depth, color == WHITE ? BLACK : WHITE, alpha,beta,depth+1);

		if (color == WHITE)
		{
			if (value > best)
			{
				best = value;
				alpha = value;
			}
		}
		else
		{
			if (value < best)
			{
				best = value;
				beta = value;
			}
		}

		if (alpha > beta)
			break;
	}
	
	return best;
}


Move Bot::pickBestMove(Board& b, int max_depth)
{
	Move best_move;
	float best_eval=color==WHITE?-10000000:10000000;
	float eval;

	list<Move> l;
	generate_all_moves(l, b, color);
	for (auto move : l)
	{
		Board b2 = Board(b);
		make_move(b2, move);
		eval=evaluateToDepth(b2, max_depth, color == WHITE ? BLACK : WHITE, -1000000,10000000);

		if (color == WHITE)
		{
			if (eval > best_eval)
			{
				best_eval = eval;
				best_move = Move(move);
			}
		}
		else
		{
			if (eval < best_eval)
			{
				best_eval = eval;
				best_move = Move(move);
			}
		}
	}
	bot_eval = best_eval;
	return best_move;
}

void Bot::evaluateToDepthMultiThreading(Board& b, int max_depth, int color, float alpha, float beta, float& answer, int depth)
{
	aa++;
	//cout << b;
	if (depth >= max_depth)
	{
		answer= Evaluate(b);
		return;
	}

	list<Move> l;
	generate_all_moves(l, b, color);

	float best = color == WHITE ? -1000000 : 10000000;
	float value;

	for (auto move : l)
	{
		Board b2 = Board(b);
		make_move(b2, move);
		value = evaluateToDepth(b2, max_depth, color == WHITE ? BLACK : WHITE, alpha, beta, depth + 1);

		if (color == WHITE)
		{
			if (value > best)
			{
				best = value;
				alpha = value;
			}
		}
		else
		{
			if (value < best)
			{
				best = value;
				beta = value;
			}
		}

		if (alpha > beta)
			break;
	}

	answer = best;
}

Move Bot::pickBestMoveMultiThreading(Board& b)
{
	Move best_move;
	float best_eval = color == WHITE ? -10000000 : 10000000;
	float eval;

	list<Move> l;
	generate_all_moves(l, b, color);
	for (auto move : l)
	{
		Board b2 = Board(b);
		make_move(b2, move);
		float answer;
		
		evaluateToDepthMultiThreading(b2, 10, color == WHITE ? BLACK : WHITE, -1000000, 10000000, answer);
		
		if (color == WHITE)
		{
			if (answer > best_eval)
			{
				best_eval = answer;
				best_move = Move(move);
			}
		}
		else
		{
			if (answer < best_eval)
			{
				best_eval = answer;
				best_move = Move(move);
			}
		}
	}
	bot_eval = best_eval;
	return best_move;
}