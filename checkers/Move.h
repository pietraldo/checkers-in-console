#pragma once
#include <iostream>

using namespace std;

struct Move
{
	int i1;
	int j1;
	int i2;
	int j2;
	bool capture;
	Move(int i1, int j1, int i2, int j2, bool capture = false) : i1(i1), j1(j1), i2(i2), j2(j2), capture(capture) {}

	friend ostream& operator<<(ostream& out, Move& m)
	{
		out << (char)(m.j1+'a') << m.i1+1 << " -> " << (char)(m.j2+'a') << m.i2+1 <<((m.capture)?" [capture]":"") << endl;
		return out;
	}

} typedef Move;

struct Field
{
	int i;
	int j;
} typedef Field;



