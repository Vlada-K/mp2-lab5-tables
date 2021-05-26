#pragma once
#include"Polinom.h"

enum TDataPos
{
	FIRST_POS, CURRENT_POS, LAST_POS
};

class TTable
{
protected:
	int DataCount;//кол-во записей в таблице
	int Efficiency;// показатель эффективности выполнения операции
public:
	TTable()
	{
		DataCount = 0;
		Efficiency = 0;
	}
	virtual~TTable()
	{}
	int GetDataCount() const//кол-во записей
	{
		return DataCount;
	}
	int GetEfficiency() const//эффуктивность
	{
		return Efficiency;
	}
	int IsEmpty() const//пуста?
	{
		return DataCount == 0;
	}
	virtual int IsFull() const = 0;//заполнена?
	virtual Polinom* FindRecord(string K) = 0;//найти запись
	virtual Polinom* InsRecord(string K, Polinom* pVal) = 0;//вставить запись
	virtual Polinom* DelRecord(string K) = 0;//удалить запись

	virtual int Reset(void) = 0;//установить на первую  запись
	virtual  int IsTabEnded(void)  const = 0;//таблица завершена?
	virtual  int GoNext(void) = 0;//переход к следующей записи
	
	virtual string GetKey(TDataPos mode) = 0;
	virtual Polinom* GetValuePtr(TDataPos mode) = 0;
	friend ostream& operator<< (ostream& os, TTable& tab);//печать таблицы

};

