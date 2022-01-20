// Implementations of methods and friend functions for singly linked list node
//
// David John
// March 2019


#include "SLLNode.h"

// overloaded output operator
ostream & operator<<(ostream & OUT, SLLNode & XXX)
{
	OUT << setw(10) << XXX.getName()
		<< setw(5) << XXX.getInventory()
		<< setw(5) << XXX.getPrice()
		<< setw(5) << XXX.getTax()
		<< setw(4) << " "
		<< setw(12) << hex << XXX.getNext() << dec << endl;
	return OUT;
}
