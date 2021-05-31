#pragma once
#ifndef _ARRHASH_H
#define _ARRHASH_H
#include"THashTable.h"
#include"TTabRecord.h"

#define TabMaxSize 25
#define TabHashStep 5

class TArrayHash : public THashTable
{
protected:
	TTabRecord** pRecs;//память для записей таблицы
	int TabSize;  //макс.возможное кол-во записей
	int HashStep; //шаг изменения позиции при коллизии
	              // (когда его место уже занято)
	              // он же - шаг вторичного перемешивания
	int FreePos;  //первая свобод.строка, обнаруженная при поиске
	int CurrPos;  //строка памяти при завершении поиска

	TTabRecord* pMark;//?? - маркер для индикации строк с удаленными записями

	int GetNextPos(int pos)
	{
		return (pos + HashStep) % TabSize;
	}//функция открытого перемешивания

public:
	TArrayHash(TTabRecord* mark, int Size = TabMaxSize, 
		       int Step = TabHashStep);
	~TArrayHash();

	virtual int IsFull() const 
	{ 
		return DataCount >= TabSize; 
	}//заполнена?

	int GetTabSize() const
	{
		return TabSize;
	}
	string GetKey(int i)
	{
		return pRecs[i]->GetKey();
	}

	virtual Polinom* FindRecord(string k);//найти запись
	virtual Polinom* InsRecord(string k, Polinom* pVal);//вставить
	virtual Polinom* DelRecord(string k);//удалить запись

	virtual int Reset(void);//установить на первую запись
	virtual int IsTabEnded(void) const;//таблица завершена?
	virtual int GoNext(void);//преход к следующей записи

	virtual string GetKey(void) const;//ключ текущей записи
	virtual Polinom* GetValuePtr(void)const;//указатель на значение
	string GetKey(TDataPos mode);
	Polinom* GetValuePtr(TDataPos mode);
	string* GetKeys();

	virtual int SetCurrentPos(int pos)
	{
		CurrPos = ((pos > -1) && (pos < DataCount)) ? 
			pos : 0;
		return IsTabEnded();
	}

	int GetCurrentPos() const
	{
		return CurrPos;
	}
};
#endif // !_ARRHASH_H

