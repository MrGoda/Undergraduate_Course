// Function to read the words of a text file into a list consistency of
// word and frequency information.
//
// David John
// March 2019

#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

#include "SLLList.h"
#include "SLLNode.h"

string cleanitup(const string & token);
void readdata(SLLList & mylist, const string & fname);

// main functions drives the I/O
int main(int argc, char** argv)
{

	// get filename from the command line, check the number
	// of command line arguments, if not 2 then abort
	if (argc !=2)
	{
		cout << "Usage:  a.out <filename>" << endl;
		return -1;
	}

	// create list and then fill it using the input file
	SLLList mylist;
	readdata(mylist,argv[1]);

	// dump the list
	cout << mylist;

	//calculate Shannon Entropy and output the value
	double sum = mylist.calculateSE();
	cout << "Shannon Entropy of this singly linked list is: " << sum << endl;


	return 0;
}

// for each token extracted remove all non alphanumeric characters
// and convert to lower case.  This function can return the empty
// string.
string cleanitup(const string & token)
{

	// clean up character by character
	string newone = "";
	for(int i=0;i<token.length();i++)
	{
		// for each alphanumeric character store the lower
		// case version
		if (isalnum(token.at(i)))
		{
		    newone.push_back(tolower(token.at(i)));
		}
	}

	return newone;
}


// function to open a file, extract the strings, clean them up, and
// update the list using all nonempty tokens
void readdata(SLLList & mylist, const string & fname) //fname is the name of inputfile
{
	// open the input file
	ifstream inputFile;
	inputFile.open(fname);

	// stream out the individual strings
	string myword;
	while(inputFile >> myword)
	{
	   // clean the string
	   myword = cleanitup(myword);

           // continue if cleaned word is not empty
	   if (!myword.empty())
	   {

		// find the word, if not in the list the insert
		// it, otherwise increase the frequency associated
		// with the word
	       SLLNode* index = mylist.find(myword);
	       if (index == NULL)
               {
                   mylist.insertFront(myword);
	       } else
	       {
                  index->increasefrequency();
               }
       	  }
        }

	// close file and return to calling function
	inputFile.close();
       return;
}
