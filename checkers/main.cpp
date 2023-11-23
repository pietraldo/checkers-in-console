#include <iostream>
#include "Board.h"

using namespace std;

void move_player();
void move_computer();
bool is_end_of_game();


int main()
{
	int aa[64] = {1};
	for (int i = 0; i < 64; i++)
		aa[i] = 1;
	Board b = Board(aa);
	b(5, 3) = 2;
	cout << b;
}

void move_player()
{

}