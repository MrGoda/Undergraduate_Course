// Implementations of methods and friend functions for singly linked list node
//
// David John
// March 2019


#include "SLLNode.h"

// overloaded output operator
ostream & operator<<(ostream & OUT, const SLLNode & XXX)
{
	OUT << setw(10) << XXX.Name
		<< setw(5) << XXX.Frequency
		<< setw(4) << " "
		<< setw(12) << hex << XXX.Next << dec << endl;
	return OUT;
}
