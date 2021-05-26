#include "TTable.h"

ostream& operator<<(ostream& os, TTable& tab)
{
    os << " Table Print" << endl;
    for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
    {
        //Polinom p = *(tab.GetValuePtr());
        os << "Key:" << tab.GetKey(CURRENT_POS) << " Val:" 
           << (tab.GetValuePtr(CURRENT_POS)->toString());
        os << endl;
    }
    return os;
}
