// David John
// September 2015

// function to read floating point numbers from
// a fstream into an array of fixed size

#include "readMyData.h"

// inputFile is a reference parameter that is what the '&' is
// all about instead of a value parameter,  dlist is an array
// parameter (also a reference parameter), dlistPSize is a
// const value parameter
int readMyData(ifstream  & inputFile, double dlist[], const int dlistPSize)
{
    // keep up with size as we stream in the numbers
    // and store them in the array
    int mysize;
    for(mysize=0;inputFile >> dlist[mysize];mysize++);

    // return logical size of the array
    return mysize;

}
