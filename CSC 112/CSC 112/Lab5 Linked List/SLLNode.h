// defintion of singly linked list node
//
// David John
// March 2019

#ifndef SLLNODE_H
#define SLLNODE_H

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class SLLNode
{

	// overload the output operator
	friend ostream & operator<<(ostream & OUT,  const SLLNode & XXX);

	private:
		string Name;
		int Frequency;

		SLLNode* Next;

	public:

	// default and alternate constructor
	SLLNode() {Name="";Frequency=0;Next=NULL;}
	SLLNode(const string & iname, const int ifreq, SLLNode* inext)
	{   Name=iname; Frequency=ifreq; Next=inext; }

	// getters
	string getName() const {return Name;}
	int getFrequency() const {return Frequency;}
	SLLNode* getNext() const {return Next;}

	//set the next node to be the assigned one--temp
	void setNext(SLLNode * temp) {Next = temp;}

	void increasefrequency()
	{
		Frequency++;
	}

};

#endif
