#include "Move.h"

Move::Move(const Move& m)
{
	capture = m.capture;
	for (int i = 0; i < m.fields.size(); i++)
	{
		fields.push_back(Field(m.fields[i]));
	}
}

Move::Move(Field f1, Field f2, bool capture) : capture(capture)
{
	fields.push_back(f1);
	fields.push_back(f2);
}

Move::Move(int i1, int j1, int i2, int j2, bool capture) : capture(capture)
{
	fields.push_back(Field(i1, j1));
	fields.push_back(Field(i2, j2));
}

void Move::add(Field f)
{
	fields.push_back(f);
}

bool Move::operator==(Move m)
{
	for (int i = 0; i < fields.size(); i++)
	{
		if (!(m(i) == fields[i]))
			return false;
	}
	return true;
}

ostream& operator<<(ostream& out, const Move& m)
{
	int i;
	for (i = 0; i < m.fields.size() - 1; i++)
	{
		out << (char)(m.fields[i].j + 'a') << (char)(m.fields[i].i + '1') << " -> ";
	}
	out << (char)(m.fields[i].j + 'a') << (char)(m.fields[i].i + '1');
	out << (m.capture ? "[capture]" : "") << endl;
	return out;
}