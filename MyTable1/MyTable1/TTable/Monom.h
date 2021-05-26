#pragma once
#include <iostream>
using namespace std;

class Monom
{
private:
	double coef;
	int step;
public:
	Monom* next;// указатель на следующий моном в полиноме

	Monom();
	Monom(double, int);
	Monom(const Monom& m);
	void Plus(Monom* m);
	Monom Mult(Monom& m);
	int GetStep()
	{
		return step;
	}
	double GetCoef()
	{
		return coef;
	}
	void SetCoef(double q);

	Monom  operator*(const Monom& m);

	friend istream& operator>>(istream& in, Monom& m);
	friend ostream& operator<<(ostream& out, const Monom& m);
	string toString();
};

