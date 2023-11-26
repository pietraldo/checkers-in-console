#include "Pawn.h"

bool generate_all_moves(list<Move>& l, Board& b, int color)
{
	if (generate_all_captures(l, b, color))
		return true;
	return generate_all_not_capture_moves(l,b,color);
}

bool generate_all_captures(list<Move>& l, Board& b, int color)
{
	list<Move> captures;
	list<Move> captures2;
	list<Move> no_more_captures;
	bool added = false;

	// generating single captures
	Move m = Move();
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (!Board::is_it_black_field(i, j) || b(i, j) == 0)
				continue;

			// b(i,j) returns 1,3 for whites, 2,4 for blacks and color is 1 for white, 2 for blacks 
			if (b(i, j) % 2 != color % 2)
				continue;

			// b(i,j) is a king
			if (b(i, j) > 2 && generate_captures_king(captures, b, i, j,m))
				added = true;

			// b(i,j) is a normal pawn
			if (b(i, j) <= 2 && generate_captures_pawn(captures, b, i, j,m))
				added = true;
		}
	}

	// if there is no single captures so there is no double captures so return
	if (!added) return false;

	// generating captures that are not single
	// first checking if capture list is empty
	// if not, taking first move from list and then generating next captures after first if there is no captures it means that it is 
	// max capture and adding to no_more_captures if threre are more captures then i add it to captures and now this move has one more capture
	while (!captures.empty())
	{
		Move m = captures.front();
		captures.pop_front();
		Board b2 = Board(b);
		make_move(b2, m);
		
		if (b(m.fields[0]) <= 2 && !generate_captures_pawn(captures,b2, m.fields.rbegin()->i, m.fields.rbegin()->j,m)) // pawns
		{
			no_more_captures.push_back(m);
		}
		if (b(m.fields[0]) > 2 && !generate_captures_king(captures,b2, m.fields.rbegin()->i, m.fields.rbegin()->j,m)) // kings
		{
			no_more_captures.push_back(m);
		}
	}

	// finding max capture
	int max = 0;
	for (auto i : no_more_captures)
	{
		int size_of_capture = i.fields.size();
		if (size_of_capture > max)
		{
			max = size_of_capture;
			captures2.clear();
			captures2.push_back(i);
		}
		else if (size_of_capture == max)
		{
			captures2.push_back(i);
		}
	}

	// adding to list max capture
	for (auto i : captures2)
		l.push_back(i);

	return added;
}

bool generate_all_not_capture_moves(list<Move>& l, Board& b, int color)
{
	// checking every field of board and if it is not empty -> generate all moves for this pawn and add to list
	bool added = false;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (!Board::is_it_black_field(i, j) || b(i, j) == 0)
				continue;
			// b(i,j) returns 1,3 for whites, 2,4 for blacks and color is 1 for white, 2 for blacks 
			if (b(i, j) % 2 != color % 2)
				continue;

			// b(i,j) is a king
			if (b(i, j) > 2 && generate_moves_king(l, b, i, j))
				added = true;

			// b(i,j) is a normal pawn
			if (b(i, j) <= 2 && generate_moves_pawn(l, b, i, j))
				added = true;
		}
	}
	return added;
}
bool generate_moves_pawn(list<Move>& l, Board& b, int i, int j)
{
	if (b(i, j) == WHITE)
		return generate_moves_pawn_white(l,b,i,j);
	return generate_moves_pawn_black(l,b,i,j);
}
bool generate_moves_pawn_white(list<Move>& l, Board& b, int i, int j)
{
	// checking if field is empty and add to list
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
	// checking if field is empty and add to list
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
	while (b(i + k, j + k)==0) // go until it is empty
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
bool generate_captures_pawn(list<Move>& l, Board& b, int i, int j, Move m)
{
	// move given in arguments is empty so add field of where pawn is now 
	if (m.fields.size() == 0)
		m.add(Field(i, j));

	bool added = false;
	auto localFunction = [&](int k1, int k2)
	{
		// checking conditions of capture with pawn
		// if field b(i+k1*2, j+k2*2) is empty and on field b(i + k1, j + k2) is opponent
		if (b(i + k1 * 2, j + k2 * 2) != 0 || b(i + k1, j + k2) == 0 || b(i + k1, j + k2) % 2 == b(i, j) % 2)
			return false;

		// adding to list
		Move m2 = Move(m);
		m2.add(Field(i + k1 * 2, j + k2 * 2));
		m2.capture = true;
		l.push_back(m2);
		return true;
	};

	// doing captures in for directions
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
bool generate_captures_king(list<Move>& l, Board& b, int i, int j, Move m)
{
	// move given in arguments is empty so add field of where pawn is now 
	if (m.fields.size() == 0)
		m.add(Field(i, j));

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
			Move m2 = Move(m);
			m2.add(Field(i + k1 * k, j + k2 * k));
			m2.capture = true;
			l.push_back(m2);
			k++;
			added = true;
		}
		return added;
	};

	// checking all four directions
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
	// clear printing previus move
	color_fields_print.clear();

	// add coloring of move
	for(int i=0; i<move.fields.size(); i++)
		color_fields_print.push_back(move.fields[i]);

	// make move capture or normal
	if (move.capture)
	{
		b.moves_with_kings = 0;
		make_move_capture(b, move);
	}
	else
	{
		if(b(move.fields[0].i, move.fields[0].j) >2)
			b.moves_with_kings++;
		make_move_not_capture(b, move);
	}

	// promoting pawns if any went to last row
	promote_pawns(b);
}
void promote_pawns(Board& b)
{
	for (int j = 0; j < 4; j++)
	{
		if (b(0, j * 2) == BLACK)
			b(0, j * 2) = 4;
		if (b(N - 1, j * 2 + 1) == WHITE)
			b(N - 1, j * 2 + 1) = 3;
	}
}

void make_move_not_capture(Board &b, Move move)
{
	b(move(1)) = b(move(0));
	b(move(0)) = 0;
}

void make_move_capture(Board& b , Move move)
{
	for (int i = 0; i < move.fields.size()-1; i++)
	{
		b(move.fields[i + 1]) = b(move.fields[i]);
		delete_pawn_between(b,move.fields[i+1], move.fields[i]);
		b(move.fields[i]) = 0;
	}
}

bool is_any_capture_on_board(Board& b, int color)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (!Board::is_it_black_field(i, j) || b(i, j) == 0)
				continue;
			if (b(i, j) % 2 != color%2)
				continue;

			// b(i,j) is a king
			if (b(i, j) > 2 && is_any_capture_king(b, i, j))
				return true;

			// b(i,j) is a normal pawn
			if (b(i, j) <= 2 && is_any_capture_pawn(b, i, j))
				return true;
			
		}
	}
	return false;
}

bool is_any_capture_pawn(Board& b, int i, int j)
{
	auto localFunction = [&](int k1, int k2)
	{
		// checking if field b(i+k1*2, j+k2*2) is empty and on field b(i + k1, j + k2) is opponent
		if (b(i + k1 * 2, j + k2 * 2) != 0 || b(i + k1, j + k2) == 0 || b(i + k1, j + k2) % 2 == b(i, j) % 2)
			return false;
		return true;
	};

	if (localFunction(-1, -1))
		return true;
	if (localFunction(-1, 1))
		return true;
	if (localFunction(1, -1))
		return true;
	if (localFunction(1, 1))
		return true;

	return false;
}
bool is_any_capture_king(Board& b, int i, int j)
{
	auto localFunction = [&](int k1, int k2)
	{
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

		return true;
	};

	if (localFunction(-1, -1))
		return true;
	if (localFunction(-1, 1))
		return true;
	if (localFunction(1, -1))
		return true;
	if (localFunction(1, 1))
		return true;

	return false;
}

void delete_pawn_between(Board& b, Field f1, Field f2)
{
	// counting directions
	int d1 = (f2.i - f1.i) / abs(f2.i - f1.i);
	int d2 = (f2.j - f1.j) / abs(f2.j - f1.j);

	//going from first field to second and clearing everthing between
	int k = 1;
	while (b(f1.i + k * d1, f1.j + k * d2) != b(f2.i, f2.j))
	{
		b(f1.i + k * d1, f1.j + k * d2) = 0;
		k++;
	}
}