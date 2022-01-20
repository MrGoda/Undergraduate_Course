// Implementations for methods and friend functions
// for SLLList class
//
// David John
// March 2019

#include <math.h>

#include "SLLList.h"

using namespace std;


SLLNode* SLLList::find(const string & name)
{
	// sequentially search the list, from the first to the end
	for(SLLNode* current = first;
		current != NULL;
		current = current->getNext())
	{
		// if name is found then return the location of the match
		if(current->getName() == name)
		{
			return current;
		}
	}

	// no match for name so return NULL pointer
	return NULL;
}

bool SLLList::fancyFind(const string & name, SLLNode* & lag, SLLNode* & current)
{
	//sequentially search through the list, give back lag and current value
	lag = NULL;
	current = first;

	//loop to find where name is
	while (current != NULL)
	{
		if (current -> getName() == name) //if found
		{
			return true;
		}

		else if (name < current -> getName()) //else if name is less than current.name alphabetically
		{
			return false;
		}

		lag = current;
		current = current -> getNext();
	}

	return false; //if current is NULL (Search through all SLL, current = last)
}

//insert so that SLLList is in ordered form
void SLLList::fancyInsert(const string & newName, const int number, const double price)
{
	//parameters for fancyFind & Insertion
	SLLNode * lag = NULL;
	SLLNode * current = NULL;

	//return if newName can be found in the list
	bool ifFind = fancyFind(newName, lag, current);

	if (lag == NULL) //if no value has been stored in the list
	{
		insertFront(newName, number, price);
	}

	else
	{
		if (ifFind == true) //if another item named "newName" has been found
		{
			current -> increaseInventory(number);
		}
		else if (ifFind == false) //no item named "newName" has been stored before
		{
			SLLNode * temp = new SLLNode(newName, number, price, current);
			lag -> setNext(temp);
			size ++;

			if (current == NULL) //if newName is the last element of the list
			{
				last = temp;
			}
		}
	}
}

// insert at front of list
void SLLList::insertFront(const string & newName, const int number, const double price)
{

	//if there is not a single element in the SLLList
	if (first == NULL)
	{
		first = new SLLNode(newName, number, price, NULL);
		last = first;
		size ++;
	}

	else //if there is at least one element in the list
	{
		first = new SLLNode(newName, number, price, first);
		size++;
	}
}

//insert at the end of the list
void SLLList::insertRear(const string & newName, const int number, const double price)
{
	// create a new node that fits at the front of the list, and
	// increment the size of the list

	//if there is not a single element in the SLLList
	if (first == NULL)
	{
		first = new SLLNode(newName, number, price, NULL);
		last = first;
		size ++;
	}

	else if (first != NULL)//if there is at least one element in the list
	{
		SLLNode* lastNode = last;
		SLLNode * newNode = new SLLNode(newName, number, price, NULL);
		lastNode -> setNext(newNode);
		last = newNode;
		size ++;
	}
}

// overload output operator
ostream & operator<<(ostream & OUT, const SLLList & mylist)
{

	// print size of list and then step through the list and
	// print information about each node
	OUT << endl << "List has size: " << mylist.size << endl;
	for(SLLNode* current = mylist.first;
		current != NULL;
		current = current->getNext())
	{
		OUT << "<" << hex << current << dec << "> : ";
		OUT << *current;
	}
	OUT << endl;

	return OUT;

}

//method to set current to be NULL
void SLLList::setNull(const string & Name)
{
	//parameters for fancyFind & Insertion
	SLLNode * lag = NULL;
	SLLNode * current = NULL;

	//return if newName can be found in the list
	bool ifFind = fancyFind(Name, lag, current);

	if (lag == NULL) //if no value has been stored in the list
 	{
	 	cout << "No element is in the list. " << endl;
 	}

 	else
 	{
	 	if (ifFind == true) //if another item named "newName" has been found
	 	{
			if (current -> getNext() == NULL) // if current is the last element
			{
				lag -> setNext(NULL);
				last = lag;
			}
			else //if current is not the last element
			{
				lag -> setNext(current -> getNext());
				current = NULL;
			}
	 	}
	 	else if (ifFind == false) //no item named "newName" has been stored before
	 	{
		 	cout << "No such element is in the list" << endl;
	 	}
 	}
}

//method to calculate Shannon Entropy
double SLLList::calculateSE()
{
	double sum = 0.0; //value of Shannon Entropy
	int frequency = 0; //total number of words

	int * eachFrequency; //frequency for each node stored in a dynamic array
	eachFrequency = new int[size];
	int i = 0;

	//loop going through the entire SLLList, use getter to get the frequency of each node
	for(SLLNode* current = first; current != NULL; current = current->getNext())
	{
		eachFrequency[i] = current -> getInventory();
		frequency += current -> getInventory();
		i ++;
	}

	//loop to calculate the "sum"--shannon entropy
	for (int j = 0; j < size; j ++)
	{
		sum += - ((double)eachFrequency[j] / (double)frequency) * log2 ((double) eachFrequency[j] / (double) frequency);
	}

	//delete dynamic array
	delete[] eachFrequency;
	eachFrequency = NULL;

	return sum;
}
