#include "Bot.h"

float Bot::Evaluate(Board& b)
{
	float white=0;
	float black=0;
	if (b.moves_with_kings >= draw_after_moves)
		return 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			switch (b(i, j))
			{
				case WHITE:
					white += 1;

					// getting additional points if pawn is after the half of board
					if (i > 3)
						white +=(float) (i-3)/4;
					break;
				case BLACK:
					black -= 1;

					// getting additional points if pawn is after the half of board
					if (i <4)
						black -= (float)(4-i) / 4;
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


int Bot::number_of_evaluate_function = 0;
float Bot::bot_eval = 0;
float Bot::evaluateToDepth(Board& b, int max_depth, int color, float alpha, float beta, int depth)
{
	number_of_evaluate_function++;

	// condition of stopping recuretion 
	if (depth >= 11 || (depth >= max_depth && is_possition_stable(b, color)))
	{
		return Evaluate(b);
	}
		
	list<Move> l;
	generate_all_moves(l, b, color);

	float best=color==WHITE?-1000000:10000000;
	float value;

	for (auto move : l)
	{
		// evaluating next moves
		Board b2 = Board(b);
		make_move(b2, move);
		value=evaluateToDepth(b2, max_depth, color == WHITE ? BLACK : WHITE, alpha,beta,depth+1);


		// alpha beha pruninung
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

	// generate all moves in this possition for bot
	list<Move> l;
	generate_all_moves(l, b, color);

	// setting best move to first, just in case
	best_move = Move(l.front());

	// evaluating every move and picking best
	for (auto move : l)
	{
		// copy bord and make move on board
		Board b2 = Board(b);
		make_move(b2, move);

		// evaluate position after move
		eval=evaluateToDepth(b2, max_depth, color == WHITE ? BLACK : WHITE, -1000000,10000000);
		cout << "   ";
		printf("%.2f", eval);
		cout<< " " << move;

		// checking if this move is better than best. For white is better if eval is high but for black is better is eval is low
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

	// just to print as fun fact 
	bot_eval = best_eval;
	
	return best_move;
}


bool Bot::is_possition_stable(Board& b, int color)
{
	// this must be tested
	// 
	//return !is_any_capture_on_board(b, color);
	//return !(is_any_capture_on_board(b, WHITE) || is_any_capture_on_board(b, BLACK));
	 
	return true;
}