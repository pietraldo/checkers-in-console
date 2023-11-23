#include <algorithm>
#include <iostream>
#include <list>
#include <thread>
#include <chrono>

#include "Board.h"
#include "Move.h"
#include "Pawn.h"

using namespace std;

void move_player(Board&, int);
void move_computer(Board&, int);
void double_captures(Board&, Move);
void double_captures_computer(Board&, Move);
bool is_end_of_game(Board&);
Move read_move(Board&, list<Move>& possible_moves);

int main()
{
	int aa[64] = { 0 };
	Board b=Board(aa);
	b["f6"] = 2;
	//b["f4"] = 1;
	b["d2"] = 2;
	//b["e7"] = 2;
	b["b6"] = 1;
	b["g7"] = 3;
	int who_move = WHITE;
	while (!is_end_of_game(b))
	{
		
		system("cls");
		cout << b;
		color_fields_print.clear();
		if (who_move == WHITE)
		{
			cout << "Move player" << endl;
			move_player(b, WHITE);
			who_move = BLACK;
		}
		else
		{
			cout << "Move computer" << endl;
			this_thread::sleep_for(std::chrono::seconds(1));
			move_computer(b, BLACK);
			who_move = WHITE;
		}
		
	}
	cout << b;
	cout << endl << "koniec gry"<<endl;
}

void move_player(Board& b, int color)
{
	list<Move> l;
	generate_all_moves(l, b, color);

	Move players_move = read_move(b, l);
	make_move(b, players_move);
	if (players_move.capture)
		double_captures(b, players_move);
}

void double_captures(Board& b, Move m)
{
	system("cls");
	cout << b;
	list<Move> l;
	if (b(m.i2, m.j2) < 2)
		generate_captures_pawn(l,b, m.i2, m.j2);
	else
		generate_captures_king(l,b,m.i2,m.j2);
	if (l.size() == 0)
		return;
	Move players_move = read_move(b, l);
	make_move(b, players_move);
	if (players_move.capture)
		double_captures(b, players_move);
}

void double_captures_computer(Board& b, Move m)
{
	list<Move> l;
	if (b(m.i2, m.j2) < 2)
		generate_captures_pawn(l, b, m.i2, m.j2);
	else
		generate_captures_king(l, b, m.i2, m.j2);
	if (l.size() == 0)
		return;

	make_move(b, l.front());
	double_captures_computer(b, l.front());
}

Move read_move(Board& b, list<Move>& possible_moves)
{
	cout << "Avaible moves:" << endl;
	for (auto a : possible_moves)
		cout << a;
	cout << "Your move: ";
	string move1;
	string move2;
	cin >> move1 >> move2;
	cout << move1 << move2;

	// checking if move is in the list of moves
	for (auto a : possible_moves)
	{
		if (a.i1 == move1[1] - '1' && a.j1 == move1[0] - 'a' && a.i2 == move2[1] - '1' && a.j2 == move2[0] - 'a')
		{
			return a;
		}
	}
	cout <<endl<< "Move is not correct" << endl;
	system("cls");
	cout << b;
	read_move(b,possible_moves);
}

void move_computer(Board& b, int color)
{
	cout << "Avaible moves" << endl;
	list<Move> l;
	generate_all_moves(l, b, color);
	make_move(b, l.front());
	if (l.front().capture)
		double_captures_computer(b, l.front());
}

bool is_end_of_game(Board& b)
{
	bool white=false;
	bool black=false;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (b.is_black(i, j))
				black = true;
			if (b.is_white(i, j))
				white = true;
		}
	}
	return !(white && black);
}