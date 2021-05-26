#pragma once

#include<iostream>
#include"Polinom.h"

class TTabRecord
{
protected:
	string Key;//ключ записи
	Polinom* pValue;// указатель на значение

public:
	TTabRecord(string K = "", Polinom* pVal = 0)
	{
		Key = K;
		pValue = pVal;
	}

	void SetKey(string K)
	{
		Key = K;
	}

	string GetKey()
	{
		return Key;
	}
	void SetValuePtr(Polinom* p)
	{
		pValue = p;
	}
	Polinom* GetValuePtr()
	{
		return pValue;
	}
	TTabRecord& operator=(TTabRecord& tr)
	{
		Key = tr.Key;
		pValue = tr.pValue;
		return*this;
	}
	int operator==(const TTabRecord& tr)
	{
		return Key == tr.Key;
	}
	int operator>(const TTabRecord& tr)
	{
		return Key > tr.Key;
	}
	int operator<(const TTabRecord& tr)
	{
		return Key < tr.Key;
	}
	void Print(ostream& os)
	{
		os << Key << " " << *pValue;
	}
	TTabRecord* GetCopy();
	friend ostream& operator<< (ostream& os, TTabRecord& tab);
};

