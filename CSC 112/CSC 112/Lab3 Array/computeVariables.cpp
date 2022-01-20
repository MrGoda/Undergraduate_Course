//Yepeng Fan
//Feb 15, 2019

//including functions to compute mean and standard deviation for a set of numbers

#include "computeVariables.h"
#include "addemup.h"

using namespace std;

//function to compute mean of the elements in an array
double computeMean(const double xxxArray[], const int xxxLogicalSize)
{
  //compute sum calling addemup function
  double average = 0.0;
  double sum = 0.0;
  sum = addemup(xxxArray, xxxLogicalSize);

  if (xxxLogicalSize != 0) //make sure the denominator is not 0
  {
    average = sum / xxxLogicalSize; //calculate the mean
  }

  //return the result
  return average;
}

//function to compute Standard Deviation of the elements in an array
double computeSD(const double xxxArray[], const int xxxLogicalSize)
{
  double SD;
  double average;

  //first compute the sum and the average
  double sum = 0.0;
  sum = addemup(xxxArray, xxxLogicalSize);
  average = computeMean(xxxArray, xxxLogicalSize);

  //then substract each element with the mean, squaring it
  double temp1 = 0.0; //storing the numerator in temp1
  for(int i = 0; i < xxxLogicalSize; i ++)
  {
    temp1 = temp1 + (xxxArray[i] - average) * (xxxArray[i] - average);
  }
  if (xxxLogicalSize != 0) //test if denominator is 0
  {
    //calculate the SD: square root of the devision between temp1 and xxxLogicalSize - 1
    SD = sqrt(temp1 / xxxLogicalSize - 1);
  }
  return SD;
}
