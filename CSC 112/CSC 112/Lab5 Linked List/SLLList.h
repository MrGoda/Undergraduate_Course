// Define a singly linked list
//
// David John
// March 2019

#ifndef SLLLIST_H
#define SLLLIST_H

#include <iostream>
#include <string>

#include "SLLNode.h"

using namespace std;

class SLLList
{

	// overload output stream operator
	friend ostream & operator<<(ostream & OUT, const SLLList & mylist);

	private:
		SLLNode* first;
		SLLNode* last;
		int size;

	public:

	// default constructor
	SLLList() { first=NULL;last=NULL;size=0;}

	// prototypes for methods
	SLLNode* find(const string & name);
	void insertFront(const string newName);
	void insertRear(const string newName);

	double calculateSE(); //method to calculate Shannon Entropy


};



#endif
