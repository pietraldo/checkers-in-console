#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct Field
{
	int i;
	int j;
	Field(int i, int j) :i(i), j(j) {};
	Field(const Field& f) { i = f.i; j = f.j; }
	bool operator==(Field f) { return (f.i == i && f.j == j);  }
} typedef Field;


struct Move
{
	vector<Field> fields;
	bool capture;
	Move() {};
	Move(const Move& m); 
	Move(Field f1, Field f2, bool capture = false);
	Move(int i1, int j1, int i2, int j2, bool capture = false);

	void add(Field f); // add field to fields vector

	Field operator()(int i) { return fields[i]; }
	bool operator==(Move m);
	
	friend ostream& operator<<(ostream& out, const Move& m);

} typedef Move;




