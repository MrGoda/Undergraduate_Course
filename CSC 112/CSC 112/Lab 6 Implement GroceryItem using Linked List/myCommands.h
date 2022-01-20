//Patrick Fan
//Feb 25, 2019

#ifndef MYCOMMANDS_H
#define MYCOMMANDS_H

#include "groceryitem.h"
#include "SLLList.h"
#include "SLLNode.h"

#include <utility>

using namespace std;

void readData(SLLList & GI, const string & fname);

void writeData(SLLList & GI, const string & fname);

pair <double, double> buyIt (istringstream & sstream, SLLList & GI, SLLList & GItemp);

void print(istringstream & sstream, SLLList & GI);

void changePrice(istringstream & sstream, SLLList GI);

pair <double, double> import(istringstream & sstream, SLLList & GI);

pair <double, double> add(istringstream & sstream, SLLList & GI);

void remove(istringstream & sstream, SLLList & GI);

string standardized(string xxx);

#endif
