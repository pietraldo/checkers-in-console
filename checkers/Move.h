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
	Move(const Move& m)
	{
		capture = m.capture;
		for (int i = 0; i < m.fields.size(); i++)
		{
			fields.push_back(Field(m.fields[i]));
		}
	}
	Move(Field f1, Field f2, bool capture = false) : capture(capture) 
	{
		fields.push_back(f1);
		fields.push_back(f2);
	}
	Move(int i1, int j1, int i2, int j2, bool capture = false) : capture(capture)
	{
		fields.push_back(Field(i1,j1));
		fields.push_back(Field(i2,j2));
	}
	void add(Field f)
	{
		fields.push_back(f);
	}
	Field operator()(int i) { return fields[i]; }
	bool operator==(Move m) 
	{ 
		for (int i = 0; i < fields.size(); i++)
		{
			if (!(m(i) == fields[i]))
				return false;
		}
		return true;
	}
	friend ostream& operator<<(ostream& out, Move& m)
	{
		int i;
		for (i = 0; i < m.fields.size()-1; i++)
		{
			out << (char)(m.fields[i].j + 'a') << (char)(m.fields[i].i + '1') << " -> ";
		}
		out << (char)(m.fields[i].j + 'a') << (char)(m.fields[i].i + '1');
		out << (m.capture ? "[capture]" : "")<<endl;
		return out;
	}

} typedef Move;




