
// David John
// September 2015
#include "addemup.h"

using namespace std;

// function to sum the sum of the element of an array
// of doubles
double addemup(const double XXX[],const int XXXsize)
{
    // compute sum
    double sum = 0.0;
    for(int i=0;i<XXXsize;i++)
    {
        sum += XXX[i];
    }

    // return result
    return sum;
}
