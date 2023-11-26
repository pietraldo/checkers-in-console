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
bool is_end_of_game(Board&, int who_move);

// function reads move from user from console and returns move
// Board - current board to print, list<Move> moves that player can do, function checks if move given by user is in this list
Move read_move(Board&, list<Move>& possible_moves);

// function converts string to number,it is used in read _move 
int num(string number);

// function returns string which prints number n in format xx.xxx.xxx
string pretty_number(int n);

// SETTINGS

int MAX_DEPTH = 8; // if even it gives better eval for white because it is white to move
const int draw_after_moves = 10; // after how many moves with kings there will be draw
const bool turn_board = false; // if false board is printed with white on bottom

int main()
{
	bool start_position = false;
	int who_move = WHITE;

	int player_color = WHITE;
	int bot_color = BLACK;

	Bot bot(bot_color);
	Board b;

	// game starts from start position or from own position
	if (start_position)
	{
		b = Board();
	}
	else
	{
		int custome_board[64] = { 0 };
		b = Board(custome_board);
		/*b["b8"] = 3;
		b["f6"] = 2;
		b["a5"] = 4;
		b["a3"] = 1;
		b["c7"] = 1;
		b["c5"] = 1;
		b["f2"] = 1;
		b["d2"] = 1;
		b["e7"] = 1;
		b["g5"] = 1;*/

		//b["d4"] = 1;
		b["b8"] = 2;
		b["a7"] = 4;
		b["g1"] = 3;

	}
	
	
	// main game function. It is repiting until someone win or draw
	while (!is_end_of_game(b, who_move))
	{
		// printing board and some info
		system("cls");
		cout << b;
		cout<<"Evaluate: "<<bot.Evaluate(b)<<endl;
		cout<<"Bot evaluate: "<<Bot::bot_eval<<endl;
		cout <<"Number of evaluated positions: " << pretty_number(Bot::number_of_evaluate_function) << endl;
		
		// clearing fields that they mean prievious move
		color_fields_print.clear();

		// deciding who has move
		if (who_move == player_color)
		{
			cout <<endl<< "Move: player" << endl;
			move_player(b, player_color);

			//changing who has now move
			who_move = bot_color;
		}
		else
		{
			// counter that show how many positions bot evaluated
			Bot::number_of_evaluate_function = 0;
			cout <<endl << "Move: bot" << endl;
			move_computer(b, bot);

			//changing who has now move
			who_move = player_color;
		}
		
	}
	
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
	// printing all moves that user have
	cout << "Aviables moves:" << endl;
	int i = 0; 
	for (auto a : possible_moves)
		cout <<++i<<". " << a;
	cout << "Your move: ";
	

	// reading player's move from console
	string player_move;
	getline(cin, player_move);

	// checking if player gave move
	if (player_move.length() == 0)
	{
		system("cls");
		cout << b;
		cout << endl << "Move is not correct" << endl;
		return read_move(b, possible_moves);
	}

	// checking if player gave number which is number of move in list of possible moves
	int number = num(player_move);
	if (number >0 && number <=possible_moves.size())
	{
		int j=1;
		for (auto& move : possible_moves)
		{
			if (j++==number)
				return move;
		}
	}
	
	// sometime user just give first field so reading second field
	if (player_move.length() == 2)
	{
		string player_move2;
		getline(cin, player_move2);
		player_move += " " + player_move2;
	}
	
	// converting string to move from player_move
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
	
	// wrong move
	system("cls");
	cout << b;
	cout << endl << "Move is not correct" << endl;
	return read_move(b,possible_moves);
}

void move_computer(Board& b, Bot& bot)
{
	Move bot_move = bot.pickBestMove(b, MAX_DEPTH);
	make_move(b, bot_move);
}

int num(string move)
{
	int x=0;
	for (int i = 0; i < move.length(); i++)
	{
		if (move[i] - '0' >= 0 && move[i] - '0' <= 9)
		{
			x *= 10;
			x += (move[i] - '0');
		}
		else
		{
			break;
		}
	}
	return x;
}

bool is_end_of_game(Board& b, int who_move)
{
	// checking if white and black have pawns on the board
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

	// generate all moves changes coloring of the last move but is must stay the same so i make a copy
	vector<Field> color_fields_print2 = color_fields_print;

	bool end = false;
	list<Move> l;
	if (!generate_all_moves(l, b, who_move)) // someone dosn't have any moves so  loses who's move it is
	{
		system("cls");
		cout << b;
		cout << (who_move==WHITE?"BLACK":"WHITE") << " WINS!!!" << endl;
		end = true;
	}
	else if (!black) // wins white
	{
		system("cls");
		cout << b;
		cout << "WHITE WINS!!!" << endl;
		end = true;
	}
	else if(!white) // wins black
	{
		system("cls");
		cout << b;
		cout << "BLACK WINS!!!" << endl;
		end = true;
	}
	else if (draw_after_moves <= b.moves_with_kings) //draw
	{
		system("cls");
		cout << b;
		cout << "DRAW!!!" << endl;
		end = true;
	}

	// returning previous coloring
	color_fields_print = color_fields_print2;

	return end;
}

string pretty_number(int n)
{
	string number="";
	int three = 0;
	while (n > 0)
	{
		if (three == 3)
		{
			three = 0;
			number = "." + number;
		}
		number = (char)('0' + n % 10) + number;
		n = n / 10;
		three++;
	}
	return number;
}