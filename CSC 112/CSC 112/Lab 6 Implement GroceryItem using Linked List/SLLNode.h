// defintion of singly linked list node
//
// David John
// March 2019

#ifndef SLLNODE_H
#define SLLNODE_H

#include "groceryitem.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class SLLNode: public groceryitem //newly added: inheritance to groceryitem.h
{

// overload the output operator
friend ostream & operator<<(ostream & OUT, SLLNode & XXX);

private:
	//Required only the pointer, all the rest inherited from groceryitem
	SLLNode* Next;

public:
	// default and alternate constructor
	SLLNode(): groceryitem() {Next = NULL;}
	SLLNode(const string & iName, const int iInventory, const double price,
	SLLNode* inext): groceryitem(iName, iInventory, price) {Next = inext;}

	// getters (we already have getters in groceryitem.h)
	SLLNode* getNext() const {return Next;}

	//set the next node to be the assigned one--temp
	void setNext(SLLNode* temp) {Next = temp;}

};

#endif
