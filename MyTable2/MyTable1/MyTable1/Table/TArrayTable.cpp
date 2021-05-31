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

int TArrayTable::IsFull() const// таблица заполнена?
{
    return DataCount >= TabSize;
}

string TArrayTable::GetKey(TDataPos mode) // значение
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

Polinom* TArrayTable::GetValuePtr(TDataPos mode)// значение
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

int TArrayTable::Reset(void)// установить на первую запись
{
    CurrPos = 0;
    return IsTabEnded();
}

int TArrayTable::IsTabEnded() const// таблица завершена?
{
    return CurrPos >= DataCount;
}

int TArrayTable::GoNext()// переход к следующей записи
{
    if (!IsTabEnded()) CurrPos++;
    return IsTabEnded();
}

int TArrayTable::SetCurrentPos(int pos)// установить текущую запись
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
        if (i < DataCount)//нашли
        {
            delete pRecs[i];
            pRecs[i] = pRecs[DataCount - 1];//последний на место удаляемого переносим
            DataCount--;//уменьшаем количество записей
        }
        return nullptr;
    }
    


