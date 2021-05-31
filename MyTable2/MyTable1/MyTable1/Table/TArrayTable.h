#pragma once
#include"TTable.h"
#include"TTabRecord.h"

#define TabMaxSize 25

class TArrayTable : public TTable
{
protected:
	TTabRecord** pRecs;// память для записей таблицы
	int TabSize;//максимально возможное кол-во записей
	int CurrPos;//номер текущего записи(нумерация от 0)

public:
	TArrayTable(int Size = TabMaxSize);
	~TArrayTable();
	virtual int IsFull() const;

	int GetTabSize() const
	{
		return TabSize;
	}
	 string GetKey(int i)
	{
		return pRecs[i]->GetKey();
	}

	//Polinom* GetValuePtr() const
	//{
	//	return GetValuePtr(CURRENT_POS);
	//}

	string GetKey(TDataPos mode) ;
	virtual Polinom* GetValuePtr(TDataPos mode);

	virtual int Reset(void);
	virtual int IsTabEnded() const;
	virtual int GoNext();
	virtual int SetCurrentPos(int pos);

	int GetCurrentPos() const
	{
		return CurrPos;
	}

	virtual Polinom* FindRecord(string K);
	virtual Polinom* InsRecord(string K, Polinom* pVal);//вставить запись
	virtual Polinom* DelRecord(string K);
};

