#include "Pawn.h"

bool generate_all_moves(list<Move>& l, Board& b, int color)
{
	if (generate_all_captures(l, b, color))
		return true;
	return generate_all_not_capture_moves(l,b,color);
}

bool help_function1(list<Move>& l, Board& b, int color, bool (*function_kings)(list<Move>&, Board&, int,int), bool (*function_pawns)(list<Move>&, Board&, int, int))
{
	bool added = false;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (!Board::is_it_black_field(i,j) || b(i, j) == 0)
				continue;
			// b(i,j) returns 1,3 for whites, 2,4 for blacks and color is 1 for white, 2 for blacks 
			if (b(i, j) % 2 != color % 2)
				continue;

			// b(i,j) is a king
			if (b(i, j) > 2 && function_kings(l, b, i, j))
				added = true;

			// b(i,j) is a normal pawn
			if (b(i, j) <= 2 && function_pawns(l, b, i, j))
				added = true;
		}
	}
	return added;
}

bool generate_all_captures(list<Move>& l, Board& b, int color)
{
	return help_function1(l,b,color,generate_captures_king, generate_captures_pawn);
}

bool generate_all_not_capture_moves(list<Move>& l, Board& b, int color)
{
	return help_function1(l, b, color, generate_moves_king, generate_moves_pawn);
}

bool generate_moves_pawn(list<Move>& l, Board& b, int i, int j)
{
	if (b(i, j) == WHITE)
		return generate_moves_pawn_white(l,b,i,j);
	return generate_moves_pawn_black(l,b,i,j);
}
bool generate_moves_pawn_white(list<Move>& l, Board& b, int i, int j)
{
	bool added = false;
	if (b(i + 1, j + 1) == 0)
	{
		l.push_back(Move(i, j, i + 1, j + 1));
		added = true;
	}
	if (b(i + 1, j - 1) == 0)
	{
		l.push_back(Move(i, j, i + 1, j - 1));
		added = true;
	}
	return added;
}
bool generate_moves_pawn_black(list<Move>& l, Board& b, int i, int j)
{
	bool added=false;
	if (b(i - 1, j + 1) == 0)
	{
		l.push_back(Move(i, j, i - 1, j + 1));
		added = true;
	}
	if (b(i - 1, j - 1) == 0)
	{
		l.push_back(Move(i, j, i - 1, j - 1));
		added = true;
	}
	return added;
}
bool generate_moves_king(list<Move>& l, Board& b, int i, int j)
{
	bool added = false;
	if (b(i - 1, j - 1) == 0|| b(i - 1, j + 1) == 0|| b(i + 1, j + 1) == 0|| b(i + 1, j - 1) == 0)
		added = true;

	// direction: right top
	int k = 1;
	while (b(i + k, j + k)==0)
	{
		l.push_back(Move(i, j, i + k, j + k));
		k++;
	}
	// direction: left top
	k = 1;
	while (b(i + k, j - k) == 0)
	{
		l.push_back(Move(i, j, i + k, j - k));
		k++;
	}
	// direction: left down
	k = 1;
	while (b(i - k, j - k) == 0)
	{
		l.push_back(Move(i, j, i - k, j - k));
		k++;
	}
	// direction: right down
	k = 1;
	while (b(i - k, j + k) == 0)
	{
		l.push_back(Move(i, j, i - k, j + k));
		k++;
	}
	return added;
}
bool generate_captures_pawn(list<Move>& l, Board& b, int i, int j)
{
	bool added = false;
	auto localFunction = [&](int k1, int k2)
	{
		// checking if field b(i+k1*2, j+k2*2) is empty and on field b(i + k1, j + k2) is opponent
		if (b(i + k1 * 2, j + k2 * 2) != 0 || b(i + k1, j + k2) == 0 || b(i + k1, j + k2) % 2 == b(i, j) % 2)
			return false;
		l.push_back(Move(i, j, i + k1 * 2, j + k2 * 2, true));
		return true;
	};

	if (localFunction(-1, -1))
		added = true;
	if (localFunction(-1, 1))
		added = true;
	if (localFunction(1, -1))
		added = true;
	if (localFunction(1, 1))
		added = true;

	return added;
}
bool generate_captures_king(list<Move>& l, Board& b, int i, int j)
{
	bool added = false;
	auto localFunction = [&](int k1, int k2)
	{
		bool added=false;
		int k = 1;
		// going in the direction while the field is empty
		while (b(i + k * k1, j + k * k2) == 0)
		{
			k++;
		}
		// going out of board
		if (b(i + k * k1, j + k * k2) == -1)
			return false;
		// pawn is the same color 
		if (b(i + k * k1, j + k * k2) % 2 == b(i, j) % 2)
			return false;

		k++;
		while (b(i + k * k1, j + k * k2) == 0)
		{
			l.push_back(Move(i, j, i + k1 * k, j + k2 * k, true));
			k++;
			added = true;
		}
		return added;
	};

	if (localFunction(-1, -1))
		added = true;
	if (localFunction(-1, 1))
		added = true;
	if (localFunction(1, -1))
		added = true;
	if (localFunction(1, 1))
		added = true;

	return added;
}

void make_move(Board &b, Move move)
{
	Field f1 = { move.i1, move.j1 };
	Field f2 = { move.i2, move.j2 };
	color_fields_print.push_back(f1);
	color_fields_print.push_back(f2);
	if (move.capture)
		make_move_capture(b, move);
	else
		make_move_not_capture(b, move);
}

void make_move_not_capture(Board &b, Move move)
{
	b(move.i2, move.j2) = b(move.i1, move.j1);
	b(move.i1, move.j1) = 0;
	if (b(move.i2, move.j2) == 2 && move.i2 == 0) //promoting black
		b(move.i2, move.j2) = 4;
	if (b(move.i2, move.j2) == 1 && move.i2 == N - 1) //promoting white
		b(move.i2, move.j2) = 3;
}

void make_move_capture(Board& b , Move move)
{
	if (b(move.i1, move.j1) > 2)
		make_move_capture_king(b, move);
	else
		make_move_capture_pawn(b, move);
}
void make_move_capture_pawn(Board& b, Move move)
{
	b(move.i2, move.j2) = b(move.i1, move.j1);
	b(move.i1, move.j1) = 0;
	b(move.i1 + (move.i2 - move.i1) / 2, move.j1 + (move.j2 - move.j1) / 2) = 0; // capturing
	if (b(move.i2, move.j2) == 2 && move.i2 == 0) //promoting black
		b(move.i2, move.j2) = 4;
	if (b(move.i2, move.j2) == 1 && move.i2 == N-1) //promoting white
		b(move.i2, move.j2) = 3;
}
void make_move_capture_king(Board& b, Move move)
{
	b(move.i2, move.j2) = b(move.i1, move.j1);
	b(move.i1, move.j1) = 0;

	int k1 = (move.i2 - move.i1) / abs(move.i2 - move.i1);
	int k2 = (move.j2 - move.j1) / abs(move.j2 - move.j1);
	int k = 1;
	while (b(move.i1 + k1 * k, move.j1 + k2 * k) == 0)
	{
		k++;
	}
	b(move.i1 + k1 * k, move.j1 + k2 * k) = 0;
}