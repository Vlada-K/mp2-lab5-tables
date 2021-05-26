#include "TArrayTable.h"

TArrayTable::TArrayTable(int Size/*=TabMaxSize*/) :TTable()
{
    pRecs = new TTabRecord * [Size];

    for (int i = 0; i < Size; i++)
    {
        pRecs[i] = NULL;
    }
    TabSize = Size;
    CurrPos = 0;
}

TArrayTable::~TArrayTable()
{
    for (int i = 0; i < DataCount; i++)
        delete pRecs[i];
    delete[] pRecs;
}

int TArrayTable::IsFull() const// ������� ���������?
{
    return DataCount >= TabSize;
}

string TArrayTable::GetKey(TDataPos mode) // ��������
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

Polinom* TArrayTable::GetValuePtr(TDataPos mode)// ��������
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
    // return nullptr;
}

int TArrayTable::Reset(void)// ���������� �� ������ ������
{
    CurrPos = 0;
    return IsTabEnded();
}

int TArrayTable::IsTabEnded() const// ������� ���������?
{
    return CurrPos >= DataCount;
}

int TArrayTable::GoNext()// ������� � ��������� ������
{
    if (!IsTabEnded()) CurrPos++;
    return IsTabEnded();
}

int TArrayTable::SetCurrentPos(int pos)// ���������� ������� ������
{
    CurrPos = ((pos > -1) && (pos < DataCount)) ? pos : 0;
    return IsTabEnded();
}


    Polinom* TArrayTable::FindRecord(string k)
    {
        int i;
        for (i = 0; i < DataCount; i++)
            if (pRecs[i]->GetKey() == k)
                break;
        Efficiency = i + 1;
        if (i < DataCount)
        {
            CurrPos = i;
            return pRecs[i]->GetValuePtr();
        }
        return nullptr;
    }

    Polinom* TArrayTable::InsRecord(string k, Polinom * pVal)
    {
        pRecs[DataCount] = new TTabRecord(k, pVal);
        DataCount++;
        return nullptr;
    }

    Polinom* TArrayTable::DelRecord(string k)
    {
        int i;
        for (i = 0; i < DataCount; i++)
            if (pRecs[i]->GetKey() == k)
                break;
        if (i < DataCount)//�����
        {
            delete pRecs[i];
            pRecs[i] = pRecs[DataCount - 1];//��������� �� ����� ���������� ���������
            DataCount--;//��������� ���������� �������
        }
        return nullptr;
    }
    


