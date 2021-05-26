#include "Polinom.h"

Polinom::Polinom()
{
	head = 0;
}

Polinom::Polinom(const Polinom& p)
{
	head = 0;
	Monom* i;
	for (i = p.head; i != 0; i = i->next)
	{
		Add(new Monom(*i));
	}
}

Polinom::~Polinom()
{
	Delete();
}

void Polinom::Delete()
{
	Monom* i;
	Monom* del;
	i = head;
	while (i != 0)
	{
		del = i;
		i = i->next;
		delete del;
	}
	head = 0;
}

void Polinom::Privide()
{
	Monom* i, * j;
	for (i = head; i != 0; i = i->next)
		for (j = i->next; j != 0; j = j->next)
		{
			if (i->GetStep() == j->GetStep())
			{
				i->Plus(j);
				Remove(j);
				break;
			}
		}

}
void Polinom::Remove(Monom* j)
{
	Monom* i;
	for (i = head; i->next != j; i = i->next)
	{
	}
	i->next = j->next;
	delete j;
}



void Polinom::Add(Monom* m)
{
	Monom* tmp = new Monom(*m);
	if (head == 0)
	{
		head = tmp;
	}
	else//головая не пустая
	{
		Monom* i;
		for (i = head; i->next != 0; i = i->next)//  поис последнего элемента
		{
		}
		i->next = tmp;
	}
}

Polinom& Polinom::operator=(Polinom p)
{
	Delete();
	Monom* i;
	for (i = p.head; i != 0; i = i->next)
	{
		Add(new Monom(*i));
	}
	return *this;
}

Polinom Polinom::operator+(Polinom& p)
{
	Polinom result(*this);
	Monom* i;
	for (i = p.head; i != 0; i = i->next)
	{
		result.Add(new Monom(*i));
	}
	result.Privide();
	return result;
}

string Polinom::toString()
{
	string out;
	Monom* i;
	for (i = head; i != 0; i = i->next)//  поис последнего элемента
	{
		out += i->toString() + " ";
		if (i->next != 0)
		{
			out += "+ ";
		}
	}
	out += "\n";
	return out;
}

Polinom Polinom::operator-(Polinom& p)
{
	Polinom result(*this);
	Monom* i;
	for (i = p.head; i != 0; i = i->next)
	{
		Monom f(*i);
		f.SetCoef(-f.GetCoef());
		result.Add(new Monom(f));
	}
	result.Privide();
	return result;
}

Polinom Polinom::operator*(Polinom& p)
{
	Polinom result;
	Monom* i, * j;
	for (i = head; i != 0; i = i->next)
	{
		for (j = p.head; j != 0; j = j->next)
		{
			Monom f(i->Mult(*j));
			result.Add(new Monom(f));
		}
	}
	result.Privide();
	return result;
}

Polinom Polinom::operator*(double w)
{
	Polinom result(*this);
	Monom* i;
	for (i = result.head; i != 0; i = i->next)
	{
		//i->GetCoef()* w;
		i->SetCoef(i->GetCoef() * w);
	}
	return result;
}

ostream& operator<<(ostream& out, Polinom& p)
{
	Monom* i;
	for (i = p.head; i != 0; i = i->next)//  поис последнего элемента
	{
		out << *i << " ";
		if (i->next != 0)
		{
			out << "+ ";
		}
	}
	out << endl;
	return out;
}
istream& operator>>(istream& in, Polinom& p)
{
	while (true)
	{
		Monom* m = new Monom();
		cout << " vvedine coef , step" << endl;
		cin >> *m;
		p.Add(m);
		cout << " next Monom? (yes/no): ";
		char answer[8];
		cin >> answer;
		if (answer[0] == 'n')
		{
			break;
		}
	}
	return in;
}
