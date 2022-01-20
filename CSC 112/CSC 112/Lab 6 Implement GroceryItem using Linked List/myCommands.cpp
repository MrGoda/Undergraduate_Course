//Patrick Fan
//Feb 25, 2019

#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <string>

#include "myCommands.h"

using namespace std;

//method for "open"
void readData(SLLList & GI, const string & fname)
{
  ifstream myfile;
  myfile.open(fname);

  //temporary variables for constructing SLLList
  string titemname;
  int titeminventory;
  double titemprice;
  double titemtax;

  //initialize GI
  while (myfile >> titemname >> titeminventory >> titemprice >> titemtax)
  {
    GI.fancyInsert(titemname, titeminventory, titemprice);
  }

  //close and return
  myfile.close();
}

//method for "close"
void writeData(SLLList & GI, const string & fname)
{
  //import data in GI to the inventory file
  ofstream myfile;
  myfile.open(fname);

  //loop to import all data in GI to ofstream
  for (SLLNode* index = GI.getFirst(); index != NULL; index = index -> getNext())
  {
    myfile << index -> getName() << " " << index -> getInventory() << " " << index -> getPrice() <<
    " " << index -> getTax() << endl;
  }

  //close
  myfile.close();
}

//method for "buy", pair.first is total price, pair.second is total tax
pair <double, double> buyIt (istringstream & sstream, SLLList & GI, SLLList & GItemp)
{
  //information stored
  int iUnit;
  double iPrice;
  double iTax;

  //name and unit to be brought
  string Name;
  int Unit;

  //find the inventory being referred to, output the price and tax
  sstream >> Name >> Unit;

  //find "Name" in the scope of GI, return found
  SLLNode* found = GI.find(Name);

  if (found != NULL)
  {
    iPrice = found -> getPrice();
    iTax = found -> getTax();
    iUnit = found -> getInventory();

    //check if the inventory is larger than number to be brought
    if (iUnit >= Unit)
    {
      //output the price and tax information
      cout << setw(30) << "The price will be " << iPrice * Unit << endl;
      cout << setw(30) << "The tax will be " << iTax * Unit << endl;

      //decrease inventory
      found -> decreaseInventory(Unit);

      //Record the purchase
      GItemp.fancyInsert(Name, Unit, iPrice);

      //return
      pair <double, double> dues (iPrice * Unit, iTax * Unit);
      return dues;
    }

    else //Unit is larger than iUnit
    {
      cout << "Err: There is not enough number of items in the inventory." << endl;
      pair <double, double> dues2 (0.0, 0.0);
      return (dues2);
    }
  }

  else //found is NULL, Name is not found
  {
    cout << "Err: The name you enterred cannot be found in the inventory." << endl;
    pair <double, double> dues3 (0.0, 0.0);
    return (dues3);
  }
}

void print(istringstream & sstream, SLLList & GI)
{
  string iName;

  //if the commandline specifies a name
  if (sstream >> iName)
  {
    //find name in the scope
    SLLNode* found = GI.find(iName);
    if (found != NULL)
    {
      //cout the name, inventory, price, tax
      cout << setw(10) << iName << setw(10) << found -> getInventory() << setw(10) <<
      found -> getPrice() << setw(10) << found -> getTax() << endl;
    }

    //else if wrong name is entered
    else if (found == NULL)
    {
      cout << "Err: The name you enterred cannot be found in the inventory." << endl;
    }
  }

  //if such name is not specified
  else
  {
    for (SLLNode* index = GI.getFirst(); index != NULL; index = index -> getNext())
    {
      //cout the name, inventory, price, tax
      cout << setw(10) << index -> getName() << setw(10) << index -> getInventory() << setw(10) <<
      index -> getPrice() << setw(10) << index -> getTax() << endl;
    }
  }
}

void changePrice(istringstream & sstream, SLLList GI)
{
  //parameters of interest
  string iName;
  double iPrice;
  double Value;

  //stream in from myline
  sstream >> iName >> Value;

  //find Name
  SLLNode* found = GI.find(iName);

  //if iName is found in the scope
  if (found != NULL)
  {
    iPrice = found -> getPrice(); //return iPrice, and change it
    if (Value < iPrice)
    {
      found -> decreasePrice(iPrice - Value);
    }
    else if (Value >= iPrice)
    {
      found -> increasePrice(Value - iPrice);
    }
  }

  //else if wrong name is entered
  else if (found == NULL)
  {
    cout << "Err: The name you enterred cannot be found in the inventory." << endl;
  }
}

pair <double, double> import(istringstream & sstream, SLLList & GI)
{
  int iUnit;
  double iPrice;
  double iTax;

  //to be imported
  string Name;
  int Unit;

  //find the inventory being referred to, output the price and tax
  sstream >> Name >> Unit;

  //find "Name" in the scope of GI, return found
  SLLNode * found = GI.find(Name);

  if (found != NULL)
  {
    //import the item
    found -> increaseInventory(Unit);

    //get the price and tax so as to calculate the charge
    iPrice = found -> getPrice();
    iTax = found -> getTax();

    //output the price and tax information
    cout << setw(30) << "The price will be " << iPrice * Unit << endl;
    cout << setw(30) << "The tax will be " << iTax * Unit << endl;

    //return
    pair <double, double> charges (iPrice * Unit, iTax * Unit);
    return charges;
  }

  else if (found == NULL)//found is NULL, Name is not found
  {
    cout << "Err: The name you enterred cannot be found in the inventory." << endl;
    pair <double, double> charges (0.0, 0.0);
    return charges;
  }
}

pair <double, double> add(istringstream & sstream, SLLList & GI)
{
  string Name;
  int Unit;
  double Price;
  double Tax;

  //stream name, unit, and price
  sstream >> Name >> Unit >> Price;

  //try find "Name" in the scope of GI, return found
  SLLNode * found = GI.find(Name);

  if (found == NULL) //if no such item exists in the scope
  {
    GI.fancyInsert(Name, Unit, Price); //Insertion
    cout << Unit << " items called " << Name << " has been added." << endl;
    //return
    Tax = round(Price * 4.75) / 100;
    pair <double, double> charges (Price * Unit, Tax * Unit);
    return charges;
  }

  else if (found != NULL)//found exists
  {
    found -> increaseInventory(Unit);

    //get the price and tax so as to calculate the charge
    Price = found -> getPrice();
    Tax = found -> getTax();

    //return
    pair <double, double> charges (Price * Unit, Tax * Unit);
    return charges;
  }
}

void remove(istringstream & sstream, SLLList & GI)
{
  string Name;
  sstream >> Name; //stream name

  GI.setNull(Name); //delete current from the list
}

//method to convert all forms of characters to lower case one.
string standardized(string xxx)
{
  string str = "";
  for (int i=0; i < xxx.length(); i ++)
  {
    str.push_back(tolower(xxx[i]));
  }

  return str;
}
