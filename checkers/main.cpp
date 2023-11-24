#include <algorithm>
#include <iostream>
#include <list>
#include <thread>
#include <chrono>
#include <sstream>
#include <string>

#include "Board.h"
#include "Move.h"
#include "Pawn.h"
#include "Bot.h"

using namespace std;

void move_player(Board&, int);
void move_computer(Board&, Bot&);
void double_captures(Board&, Move);
void double_captures_computer(Board&, Move);
void promote_pawns(Board&);
bool is_end_of_game(Board&);
Move read_move(Board&, list<Move>& possible_moves);

int main()
{
	int aa[64] = { 0 };
	//Board b=Board();
	Board b=Board(aa);
	b["c3"] = 2;
	b["d6"] = 1;
	b["e7"] = 2;
	b["g7"] = 2;
	b["d2"] = 2;
	b["e7"] = 2;
	b["c5"] = 2;
	b["c3"] = 2;
	b["e3"] = 2;
	b["g3"] = 2;
	b["b6"] = 1;
	b["g7"] = 3;

	int who_move = WHITE;
	Bot bot(BLACK);

	while (!is_end_of_game(b))
	{
		system("cls");
		promote_pawns(b);
		cout << b;
		cout<<"Evaluate: "<<bot.Evaluate(b)<<endl;
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
			this_thread::sleep_for(std::chrono::seconds(2));
			move_computer(b, bot);
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
}



Move read_move(Board& b, list<Move>& possible_moves)
{
	cout << "Avaible moves:" << endl;
	for (auto a : possible_moves)
		cout << a;
	cout << "Your move: ";
	int xx;
	
	string player_move;
	getline(cin, player_move);
	Move move_p;
	for (int i = 0; i < player_move.length(); i+=2)
	{
		move_p.add(Field(player_move[i + 1] - '1', player_move[i] - 'a'));
		i++;
	}

	// checking if move is in the list of moves
	for (auto &move : possible_moves)
	{
		cout << move<<endl;
		if (move == move_p)
			return move;
	}
	
	cout <<endl<< "Move is not correct" << endl;
	system("cls");
	cout << b;
	return read_move(b,possible_moves);
}

void move_computer(Board& b, Bot& bot)
{
	Move bot_move = bot.getBestMove(b);
	make_move(b, bot_move);
}

void promote_pawns(Board& b)
{
	for (int j = 0; j < 4; j++)
	{
		if (b(0, j * 2) == BLACK)
			b(0, j * 2) = 4;
		if (b(N - 1, j * 2+1) == WHITE)
			b(N-1, j * 2+1) = 3;
	}
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


/*
 promotes pawn only at the end of move ( there is not somthing like go last row promote and capture as a  king

 there is obligatory capture of maximum pawns

 pawn and kings can capture forward and backwords




*/