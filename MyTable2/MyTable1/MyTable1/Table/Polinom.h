#pragma once
#include "Monom.h"
class Polinom
{
private:
	Monom* head;
public:
	Polinom();
	Polinom(const Polinom& p);
	~Polinom();
	void Add(Monom* m);
	void Delete();
	void Privide();
	void Remove(Monom* j);
	Polinom& operator=(Polinom p);

	friend istream& operator>>(istream& in, Polinom& p);
	friend ostream& operator<<(ostream& out, Polinom& p);

	string toString();
	Polinom operator- (Polinom& p);
	Polinom operator+ (Polinom& p);
	Polinom operator* (Polinom& p);
	Polinom operator*(double w);
};

