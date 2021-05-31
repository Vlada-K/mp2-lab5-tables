#include "ArrHash.h"

TArrayHash::TArrayHash(TTabRecord* mark, int Size, int Step) : THashTable()
{
	pRecs = new TTabRecord* [Size];
	TabSize = Size;
	HashStep = Step;
	CurrPos = FreePos = 0;

	for (int i = 0; i < TabSize; i++)
		pRecs[i] = NULL;

	pMark = mark;
}

TArrayHash:: ~TArrayHash()// ����������
{
	for (int i = 0; i < TabSize; i++)
		if ((pRecs[i] != NULL) && (pRecs[i] != pMark)) 
			delete pRecs[i];
	delete[] pRecs;
	delete pMark;
}

string* TArrayHash::GetKeys()
{
	string* keys = new string[DataCount];
	int pos = 0;
	for (int i = 0; i < TabSize; i++)
		if ((pRecs[i] != NULL) && (pRecs[i] != pMark))
			keys[pos++] = pRecs[i]->GetKey();
	return keys;
}

Polinom* TArrayHash::FindRecord(string k)//����� ������
{
	Polinom* pValue = NULL;
	FreePos = -1;
	Efficiency = 0;

	CurrPos = HashFunc(k) % TabSize; // &TabSize;
	for (int i = 0; i < TabSize; i++)
	{
		Efficiency++;
		if (pRecs[CurrPos] == NULL) break;//

		else if (pRecs[CurrPos] == pMark)//
		{
			if (FreePos == -1)
				FreePos = CurrPos;
		}
		else if (pRecs[CurrPos]->GetKey() == k)//
		{
			pValue = pRecs[CurrPos]->GetValuePtr();
			break;
		}
		CurrPos = GetNextPos(CurrPos);//
	}

/*	if (pValue == NULL)
		SetRetCode(TabNoRes);
	else
		SetRetCode(TabOK)*/;
	return pValue;
}
Polinom* TArrayHash::InsRecord(string k, Polinom* pVal)//�������� ������
{
	int pos = HashFunc(k) % TabSize;

	if (pRecs[pos] == NULL)
	{
		pRecs[pos] = new TTabRecord(k, pVal);
		DataCount++;
	}
	else
	{
		if(pRecs[pos]->GetKey() == k)
			pRecs[pos] = new TTabRecord(k, pVal); // ������
		else // ��������
		{
			while (pRecs[pos] != NULL && // ����� ����������
				pRecs[pos]->GetKey() != k)
			{
				pos = GetNextPos(pos);
			}
			// ������ �� ��������� �����
			pRecs[pos] = new TTabRecord(k, pVal); 
			DataCount++;
		}
	}
	return 0;
}
Polinom* TArrayHash::DelRecord(string k)//������� ������
{
	Polinom* temp = FindRecord(k);//����� �����
	if (temp == NULL)
		return NULL;

	delete pRecs[CurrPos];
	pRecs[CurrPos] = pMark;

	return temp;
}
int TArrayHash::Reset(void)// ���������� �� ������ ������
{
	CurrPos = 0;
	return GoNext();
}
int TArrayHash::IsTabEnded(void) const// ������� ���������?
{
	return CurrPos >= TabSize;
}

int TArrayHash::GoNext(void)//������� � ��������� ������
{
	if (!IsTabEnded())
	{
		while (++CurrPos < TabSize)// ����� ������� ������
			if ((pRecs[CurrPos] != NULL) && (pRecs[CurrPos] != pMark))
				break;
	}
	return IsTabEnded();
}
TKey TArrayHash::GetKey(void)const//�������� ����� ������� ������
{
	return((CurrPos < 0) || (CurrPos >= TabSize)) ? 
		string("") : pRecs[CurrPos]->GetKey();
}

Polinom* TArrayHash::GetValuePtr(void) const//��������� �� ��������
{
	return((CurrPos < 0) || (CurrPos >= TabSize)) ? 
		NULL : pRecs[CurrPos]->GetValuePtr();
}

string TArrayHash::GetKey(TDataPos mode) // ��������
{
	int pos = -1;
	if (!IsEmpty())
	{
		switch (mode)
		{
		case FIRST_POS:
			pos = 0;
			break;

		case LAST_POS:
			pos = DataCount - 1;
			break;
		default:
			pos = CurrPos;
			break;
		}
	}
	return (pos == -1) ? string("") : pRecs[pos]->GetKey();
}

Polinom* TArrayHash::GetValuePtr(TDataPos mode)// ��������
{
	int pos = -1;
	if (!IsEmpty())
	{
		switch (mode)
		{
		case FIRST_POS:
			pos = 0;
			break;

		case LAST_POS:
			pos = DataCount - 1;
			break;
		default:
			pos = CurrPos;
			break;
		}
	}
	return (pos == -1) ? NULL : pRecs[pos]->GetValuePtr();
}
