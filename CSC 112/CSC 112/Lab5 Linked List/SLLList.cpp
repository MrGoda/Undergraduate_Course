// Implementations for methods and friend functions
// for SLLList class
//
// David John
// March 2019

#include <math.h>

#include "SLLList.h"

using namespace std;

// find
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


// insert at front of list
void SLLList::insertFront(const string newName)
{
	// create a new node that fits at the front of the list, and
	// increment the size of the list

	SLLNode * index = find(newName);

	//if "newName" has not occured in the list
	if (index == NULL)
	{
		if (first == NULL)
		{
			first = new SLLNode(newName, 1, NULL);
			last = first;
			size++;
		}

		else //if there is at least one element in the list
		{
			first = new SLLNode(newName, 1, first);
			size++;
		}
	}

	//if "newName" occurs at one point in the list, increase frequency of "newName" by 1
	else
	{
		index -> increasefrequency();
	}

}

//insert at the end of the list
void SLLList::insertRear(const string newName)
{
	// create a new node that fits at the front of the list, and
	// increment the size of the list

	SLLNode * index = find(newName);

	//if "newName" has not occured in the list
	if (index == NULL)
	{
		if (first == NULL)
		{
			first = new SLLNode(newName, 1, NULL);
			last = first;
			size++;
		}

		else // if there is at least one element in the list
		{
			SLLNode * temp = new SLLNode(newName, 1, NULL); //new node that would be placed by the end
			SLLNode * current = last;
			current -> setNext(temp);
			last = temp;
			size ++;
		}
	}

	//if "newName" occurs at one point in the list, increase frequency of "newName" by 1
	else
	{
		index -> increasefrequency();
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
		eachFrequency[i] = current->getFrequency();
		frequency += current->getFrequency();
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
