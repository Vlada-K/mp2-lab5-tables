#include "TTabRecord.h"

TTabRecord* TTabRecord::GetCopy()
{
	TTabRecord* temp = new TTabRecord(Key, pValue);
	return temp;
}

ostream& operator<<(ostream& os, TTabRecord& tab)
{
	os << tab.Key << endl;
	os << (tab.pValue->toString()) << endl;
	return os;
}
