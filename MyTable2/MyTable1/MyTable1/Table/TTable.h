#pragma once
#include"Polinom.h"

enum TDataPos
{
	FIRST_POS, CURRENT_POS, LAST_POS
};

class TTable
{
protected:
	int DataCount;//���-�� ������� � �������
	int Efficiency;// ���������� ������������� ���������� ��������
public:
	TTable()
	{
		DataCount = 0;
		Efficiency = 0;
	}
	virtual~TTable()
	{}
	int GetDataCount() const//���-�� �������
	{
		return DataCount;
	}
	int GetEfficiency() const//�������������
	{
		return Efficiency;
	}
	int IsEmpty() const//�����?
	{
		return DataCount == 0;
	}
	virtual int IsFull() const = 0;//���������?
	virtual Polinom* FindRecord(string K) = 0;//����� ������
	virtual Polinom* InsRecord(string K, Polinom* pVal) = 0;//�������� ������
	virtual Polinom* DelRecord(string K) = 0;//������� ������

	virtual int Reset(void) = 0;//���������� �� ������  ������
	virtual  int IsTabEnded(void)  const = 0;//������� ���������?
	virtual  int GoNext(void) = 0;//������� � ��������� ������
	
	virtual string GetKey(TDataPos mode) = 0;
	virtual Polinom* GetValuePtr(TDataPos mode) = 0;
	friend ostream& operator<< (ostream& os, TTable& tab);//������ �������

};

