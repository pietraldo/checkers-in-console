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

	if (!added) return false;
	//return added;

	int x;
	int num;
	//cin >> x;
	while (captures.size() > 0)
	{
		Move m = captures.front();
		captures.pop_front();
		Board b2 = Board(b);
		make_move(b2, m);
		//cout << m << endl;
		//cout << b2<<endl;
		//int x;
		//cin >> x;
		if (b(m.fields[0]) <= 2 && !generate_captures_pawn(captures,b2, m.fields.rbegin()->i, m.fields.rbegin()->j,m)) // pawns
		{
			//cout << "aaaaaa";
			no_more_captures.push_back(m);
		}
		if (b(m.fields[0]) > 2 && !generate_captures_king(captures,b2, m.fields.rbegin()->i, m.fields.rbegin()->j,m)) // kings
		{
			//cout << "aaaaaaaa";
			no_more_captures.push_back(m);
		}
		//cout << m;
		//cin >> x;
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
	// adding to list
	for (auto i : captures2)
		l.push_back(i);


	
	

	return added;
}

bool generate_all_not_capture_moves(list<Move>& l, Board& b, int color)
{
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
bool generate_captures_pawn(list<Move>& l, Board& b, int i, int j, Move m)
{
	if (m.fields.size() == 0)
		m.add(Field(i, j));

	bool added = false;
	auto localFunction = [&](int k1, int k2)
	{
		// checking if field b(i+k1*2, j+k2*2) is empty and on field b(i + k1, j + k2) is opponent
		if (b(i + k1 * 2, j + k2 * 2) != 0 || b(i + k1, j + k2) == 0 || b(i + k1, j + k2) % 2 == b(i, j) % 2)
			return false;
		Move m2 = Move(m);
		m2.add(Field(i + k1 * 2, j + k2 * 2));
		m2.capture = true;
		l.push_back(m2);
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
bool generate_captures_king(list<Move>& l, Board& b, int i, int j, Move m)
{
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
	color_fields_print.clear();
	for(int i=0; i<move.fields.size(); i++)
		color_fields_print.push_back(move.fields[i]);

	if (move.capture)
		make_move_capture(b, move);
	else
		make_move_not_capture(b, move);

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
	/*if (b(move.i1, move.j1) > 2)
		make_move_capture_king(b, move);
	else
		make_move_capture_pawn(b, move);*/
}
void make_move_capture_pawn(Board& b, Move move)
{
	//b(move.i2, move.j2) = b(move.i1, move.j1);
	//b(move.i1, move.j1) = 0;
	//b(move.i1 + (move.i2 - move.i1) / 2, move.j1 + (move.j2 - move.j1) / 2) = 0; // capturing
}
void make_move_capture_king(Board& b, Move move)
{
	/*b(move.i2, move.j2) = b(move.i1, move.j1);
	b(move.i1, move.j1) = 0;

	int k1 = (move.i2 - move.i1) / abs(move.i2 - move.i1);
	int k2 = (move.j2 - move.j1) / abs(move.j2 - move.j1);
	int k = 1;
	while (b(move.i1 + k1 * k, move.j1 + k2 * k) == 0)
	{
		k++;
	}
	b(move.i1 + k1 * k, move.j1 + k2 * k) = 0;*/
}

void delete_pawn_between(Board& b, Field f1, Field f2)
{
	int d1 = (f2.i - f1.i) / abs(f2.i - f1.i);
	int d2 = (f2.j - f1.j) / abs(f2.j - f1.j);
	int k = 1;
	while (b(f1.i + k * d1, f1.j + k * d2) != b(f2.i, f2.j))
	{
		b(f1.i + k * d1, f1.j + k * d2) = 0;
		k++;
	}
}