// Полином.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream> 
#include "Polinom.h"
#include"TArrayTable.h"
#include "MyTable.h"
#include"TreeTable.h"
#include"ArrHash.h"

#include <cstdlib>
using  namespace std;


TArrayTable* pTab = NULL;
int DataCount = 0, Memsize;
TTreeTable* pTabtree = NULL;

TTabRecord* pMark = new TTabRecord(string(""), NULL);
TArrayHash* pHash = NULL;

void TableGenerator()
{
	int MaxKeyValue, RetCode;
	char Line[100];
	cout << " Input the record's number-"  ;
	cin >> DataCount;
	Memsize = DataCount + 10;
	pTab = new TArrayTable(Memsize);
	for (int i = 0; i < DataCount; i++)
	{
		string Key;
		cout << " Key=";
		cin >> Key;
		Polinom* p = new Polinom();
		cin >> *p;
		pTab->InsRecord(Key, p);
	}
	cout << " Result" << endl;
	cout << *pTab << endl;
}
void TableProcessor()
{
	int  com;
	string Key;
	while (1)
	{
		cout << " Input Command( 0-Exit, 1-Find, 2-Ins, 3-Del, 4-Print)-";
		cin >> com;
		if (com == 0)
			break;
		if (com != 4)
		{
			cout <<" Input the key of record-";
			cin>> Key; 
		}
		if (com == 1)
		{
			cout<< " Find "<< *pTabtree->FindRecord(Key);
			cout << " Effect = " << pTabtree->GetEfficiency();
			//cout << " Retcode =" << pTab->GetRetCode() << endl;
		}
		if (com == 2)
		{
			if (DataCount >= Memsize)
				cout << " MemBuffer is full" << endl;
			else
			{
				//pKeys[DataCount] = Key;
				Polinom* p = new Polinom();
				cin >> *p;
				pTabtree->InsRecord(Key, p);
				DataCount++;
			}
		}
		if (com == 3)
		{
			pTabtree->DelRecord(Key);
			cout << " Result" << endl;
			cout << *pTabtree << endl;
		}
		if (com == 4)
			cout << *pTabtree;
	}
}
void TableEvaluator()
{
	int IterCount, k;
	long Total = 0;
	string* pKeys = new string[DataCount];
	for (int i = 0; i < DataCount; i++)
	{
		pKeys[i] = pTab->GetKey(i);
	}

	cout << " Input the iteration's number-";
	cin >> IterCount;
	for (int i = 0; i < IterCount; i++)
	{
		k = rand() % DataCount;
		pTab->FindRecord(pKeys[k]);
		Total += pTab->GetEfficiency();
	}
	cout << " Insert in the table-efficiency evaluation" << endl;
	cout << " Table Size:" << pTab->GetDataCount() <<endl;
	cout << " Iterations:" << IterCount << endl;
	cout << " Average Efficiency:" << Total / double(IterCount) << endl;

}

void TreeTableGenerator()
{
	int MaxKeyValue, RetCode;
	char Line[100];
	cout << " Input the record's number-";
	cin >> DataCount;
	//Memsize = DataCount + 10;
	
	pTabtree = new TTreeTable();

	for (int i = 0; i < DataCount; i++)
	{
		string Key;
		cout << " Key=";
		cin >> Key;
		Polinom* p = new Polinom();
		cin >> *p;
		pTabtree->InsRecord(Key, p);
	}
	cout << " Result" << endl;
	pTabtree->printAll();
}
void TreeTableProcessor()
{
	int  com;
	string Key;
	Memsize = 99999;

	while (1)
	{
		cout << " Input Command( 0-Exit, 1-Find, 2-Ins, 3-Del, 4-Print)-";
		cin >> com;
		if (com == 0)
			break;
		if (com != 4)
		{
			cout << " Input the key of record-";
			cin >> Key;
		}
		if (com == 1)
		{
			cout << " Find " << *pTabtree->FindRecord(Key);
			cout << " Effect = " << pTabtree->GetEfficiency();
			//cout << " Retcode =" << pTab->GetRetCode() << endl;
		}
		if (com == 2)
		{
			if (DataCount >= Memsize)
				cout << " MemBuffer is full" << endl;
			else
			{
				//pKeys[DataCount] = Key;
				Polinom* p = new Polinom();
				cin >> *p;
				pTabtree->InsRecord(Key, p);
				DataCount++;
			}
		}
		if (com == 3)
		{
			pTabtree->DelRecord(Key);
			cout << " Result" << endl;
			cout << *pTabtree << endl;
		}
		if (com == 4)
			cout << *pTabtree;
	}
}
void TreeTableEvaluator()
{
	int IterCount, k;
	long Total = 0;
	string* pKeys = pTabtree->GetKeys();
	DataCount = pTabtree->GetDataCount();

	cout << " Input the iteration's number-";
	cin >> IterCount;
	for (int i = 0; i < IterCount; i++)
	{
		k = rand() % DataCount;
		pTabtree->FindRecord(pKeys[k]);
		Total += pTabtree->GetEfficiency();
	}

	cout << " Insert in the table-efficiency evaluation" << endl;
	cout << " Table Size:" << pTabtree->GetDataCount() << endl;
	cout << " Iterations:" << IterCount << endl;
	cout << " Average Efficiency:" << Total / double(IterCount) << endl;
}

void HashTableGenerator()
{
	int MaxKeyValue, RetCode;
	char Line[100];
	cout << " Input the record's number-";
	cin >> DataCount;
	pHash = new TArrayHash(pMark);

	for (int i = 0; i < DataCount; i++)
	{
		string Key;
		cout << " Key=";
		cin >> Key;
		Polinom* p = new Polinom();
		cin >> *p;
		pHash->InsRecord(Key, p);
	}

	cout << " Result" << endl;
	cout << *pHash << endl;
}
void HashTableProcessor()
{
	int  com;
	string Key;
	while (1)
	{
		cout << " Input Command( 0-Exit, 1-Find, 2-Ins, 3-Del, 4-Print)-";
		cin >> com;
		if (com == 0)
			break;
		if (com != 4)
		{
			cout << " Input the key of record-";
			cin >> Key;
		}
		if (com == 1)
		{
			Polinom* p = pHash->FindRecord(Key);
			if (p == NULL)
				cout << "NULL" << endl;
			else
				cout << " Find " << *p << endl;

			cout << " Effect = " << pHash->GetEfficiency();
			//cout << " Retcode =" << pTab->GetRetCode() << endl;
		}
		if (com == 2)
		{
			if (pHash->IsFull())
				cout << " MemBuffer is full" << endl;
			else
			{
				//pKeys[DataCount] = Key;
				Polinom* p = new Polinom();
				cin >> *p;
				pHash->InsRecord(Key, p);
				DataCount++;
			}
		}
		if (com == 3)
		{
			pHash->DelRecord(Key);
			cout << " Result" << endl;
			cout << *pHash << endl;
		}
		if (com == 4)
			cout << *pHash;
	}
}
void HashTableEvaluator()
{
	int IterCount, k;
	long Total = 0;
	string* pKeys = pHash->GetKeys();
	DataCount = pHash->GetDataCount();

	cout << " Input the iteration's number-";
	cin >> IterCount;
	for (int i = 0; i < IterCount; i++)
	{
		k = rand() % DataCount;
		pHash->FindRecord(pKeys[k]);
		Total += pHash->GetEfficiency();
	}

	cout << " Insert in the table-efficiency evaluation" << endl;
	cout << " Table Size:" << pHash->GetDataCount() << endl;
	cout << " Iterations:" << IterCount << endl;
	cout << " Average Efficiency:" << Total / double(IterCount) << endl;
}


int main()
{
	cout << " Testing programm support table" << endl;
	// Array table
	/*TableGenerator();
	TableProcessor();
	TableEvaluator();*/

	// TreeTable
	//TreeTableGenerator();
	//TreeTableProcessor();
	//TreeTableEvaluator();
	
	// TreeTable
	HashTableGenerator();
	HashTableProcessor();
	HashTableEvaluator();
}

