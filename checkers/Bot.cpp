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
		if (best_eval > current_eval)
		{
			best_eval = current_eval;
			best = Move(m);
		}
	}


	return best;
}