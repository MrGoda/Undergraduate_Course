/*
 * File:   main.cpp
 * Author: djj
 *
 * Created on September 17, 2015, 1:18 PM
 *
 * main program to:
 *  (1) prompt and read for the name of a file,
 *  (2) open the file,
 *  (3) call a function to stream numbers from the file
 *         into an array,
 *  (4) call a function to compute the sum of the numbers, and
 *  (5) display the number of numbers in the file and their sum
 *
 */

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "addemup.h"
#include "readMyData.h"
#include "computeVariables.h"

using namespace std;

int main(int argc, char** argv) {

    // create a double array of fixed size
    // along with a constant for the physical
    // size and a variable for the logical
    // size
    const int myNumbersSize = 200;
    int myNumbersLogicalSize = 0;
    double myNumbers[myNumbersSize];

    // prompt and read the user for a file name to
    // read numbers from, open file
    string fname;
    ifstream myDataFile;
    cout << "Enter the name of the input file: ";
    cin >> fname;
    myDataFile.open(fname.c_str());

    // call the routine to read in the numbers
    // and return the logical size
    myNumbersLogicalSize = readMyData(myDataFile, myNumbers,
                                      myNumbersSize);

    // done with file, close it
    myDataFile.close();

    //if logical size is larger than the physical size, print error
    if (myNumbersLogicalSize > myNumbersSize)
    {
      cout << "Error: The logical size of the array is larger than the physical size of it! Operation abort." << endl;
    }

    else //initiate the following functions
    {
      // call function to compute sum, mean, and standard deviation
      double sum = addemup(myNumbers,myNumbersLogicalSize);
      double mean = computeMean(myNumbers, myNumbersLogicalSize);
      double SD = computeSD(myNumbers, myNumbersLogicalSize);

      // print out the sum
      cout << "The sum of the ";
      cout << myNumbersLogicalSize;
      cout << " values in the file named ";
      cout << "<" << fname <<"> is ";
      cout << sum << endl;

      // print out the mean
      cout << "The mean of the ";
      cout << myNumbersLogicalSize;
      cout << " values in the file named ";
      cout << "<" << fname <<"> is ";
      cout << mean << endl;

      // print out the standard deviation
      cout << "The standard deviation of the ";
      cout << myNumbersLogicalSize;
      cout << " values in the file named ";
      cout << "<" << fname <<"> is ";
      cout << SD << endl;
    }

    return 0;
}
