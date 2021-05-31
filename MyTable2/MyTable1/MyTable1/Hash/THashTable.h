#pragma once
#ifndef _HASHTAB_H
#define _HASHTAB_H
#include"TTable.h"
class TTabRecord;

#define TKey string

class THashTable:public TTable
{protected://хеш-функция
	virtual unsigned long HashFunc(const TKey key);
public:
	THashTable() : TTable() {}
};
#endif // !_HASHTAB_H

