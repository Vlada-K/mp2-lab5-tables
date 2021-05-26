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
	TTabRecord** pRecs;//������ ��� ������� �������
	int TabSize;  //����.��������� ���-�� �������
	int HashStep; //��� ��������� ������� ��� ��������
	              // (����� ��� ����� ��� ������)
	              // �� �� - ��� ���������� �������������
	int FreePos;  //������ ������.������, ������������ ��� ������
	int CurrPos;  //������ ������ ��� ���������� ������

	TTabRecord* pMark;//?? - ������ ��� ��������� ����� � ���������� ��������

	int GetNextPos(int pos)
	{
		return (pos + HashStep) % TabSize;
	}//������� ��������� �������������

public:
	TArrayHash(TTabRecord* mark, int Size = TabMaxSize, 
		       int Step = TabHashStep);
	~TArrayHash();

	virtual int IsFull() const 
	{ 
		return DataCount >= TabSize; 
	}//���������?

	int GetTabSize() const
	{
		return TabSize;
	}
	string GetKey(int i)
	{
		return pRecs[i]->GetKey();
	}

	virtual Polinom* FindRecord(string k);//����� ������
	virtual Polinom* InsRecord(string k, Polinom* pVal);//��������
	virtual Polinom* DelRecord(string k);//������� ������

	virtual int Reset(void);//���������� �� ������ ������
	virtual int IsTabEnded(void) const;//������� ���������?
	virtual int GoNext(void);//������ � ��������� ������

	virtual string GetKey(void) const;//���� ������� ������
	virtual Polinom* GetValuePtr(void)const;//��������� �� ��������
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

