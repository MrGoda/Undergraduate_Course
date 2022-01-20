//Patrick Fan
//Feb 25, 2019

#ifndef MYCOMMANDS_H
#define MYCOMMANDS_H

#include "groceryitem.h"
#include <utility>

using namespace std;

int readData(groceryitem GI[], int GIPS);

void writeData(groceryitem GI[], const int GILS);

pair <double, double> buyIt (istringstream & sstream, groceryitem GI[],
  const int GILS, groceryitem GItemp[], int GItempLS);

void print(istringstream & sstream, groceryitem GI[], const int GILS);

void changePrice(istringstream & sstream, groceryitem GI[], const int GILS);

pair <double, double> import(istringstream & sstream,
  groceryitem GI[], const int GILS);

string standardized(string xxx);

#endif
