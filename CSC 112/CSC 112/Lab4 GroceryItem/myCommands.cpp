//Patrick Fan
//Feb 25, 2019

#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>

#include "myCommands.h"

using namespace std;

//method for "open"
int readData(groceryitem GI[], const int GIPS)
{
  ifstream myfile;
  myfile.open("inventory.txt");

  //temporary variables for constructing groceryitem
  string titemname;
  int titeminventory;
  double titemprice;
  double titemtax;

  //temporary logical size
  int tempLS = 0;

  //initialize GI, make sure it does not exceed the physical size
  while ((tempLS < GIPS) && (myfile >> titemname >> titeminventory >> titemprice >> titemtax))
  {
    GI[tempLS] = groceryitem(titemname, titeminventory, titemprice, titemtax);
    tempLS ++;
  }

  //close and return
  myfile.close();
  return tempLS;
}

//method for "close"
void writeData(groceryitem GI[], const int GILS)
{
  //import data in GI to the inventory file
  ofstream myfile;
  myfile.open("inventory.txt");

  //import until exceeding logical size
  for (int i = 0; i < GILS; i ++)
  {
    myfile << GI[i].getName() << " " << GI[i].getInventory() << " " <<
    GI[i].getPrice() << " " << GI[i].getTax() << endl;
  }

  //close
  myfile.close();
}

//method for "buy"
pair <double, double> buyIt (istringstream & sstream, groceryitem GI[], const int GILS, groceryitem GItemp[], int GItempLS)
{
  string iName;
  int iUnit;
  double iPrice;
  double iTax;

  int Unit; //to be brought

  //find the inventory being referred to, output the price and tax
  sstream >> iName >> Unit;

  for (int i = 0; i < GILS; i ++)
  {
    //find "iName" in the scope of GI
    if (iName == GI[i].getName())
    {
      double iPrice = GI[i].getPrice();
      double iTax = GI[i].getTax();
      int iUnit = GI[i].getInventory();

      //check if the inventory is larger than number to be brought
      if (iUnit >= Unit)
      {
        //output the price and tax information
        cout << setw(30) << "The price will be " << iPrice * Unit << endl;
        cout << setw(30) << "The tax will be " << iTax * Unit << endl;

        //decrease inventory
        GI[i].decreaseInventory(Unit);

        int find = 0; //if iName is found in GItemp?
        for (int j = 0; j < GItempLS; j ++)//store info of what is brought in GItemp
        {
          //case when same groceryitem was purchased by other customers before
          if (iName == GItemp[j].getName())
          {
            GItemp[j].increaseInventory(Unit);
            find = 1;
          }
        }
        if (find == 0)
        {
          GItemp[GItempLS] = groceryitem(iName, Unit, iPrice, iTax);
          GItempLS ++;
        }


        //return
        pair <double, double> dues (iPrice * Unit, GItempLS);
        return dues;
      }

      else //Unit is larger than iUnit
      {
        cout << "Err: There is not enough number of items in the inventory." << endl;
        pair <double, double> dues2 (0.0, GItempLS);
        return (dues2);
      }
    }
  }
  //if iName is not found
  cout << "Err: The name you enterred cannot be found in the inventory." << endl;
  pair <double, double> dues3 (0.0, GItempLS);
  return (dues3);
}

void print(istringstream & sstream, groceryitem GI[], const int GILS)
{
  string iName;

  //if the commandline specifies a name
  if (sstream >> iName)
  {
    for (int i = 0; i <= GILS; i ++)
    {
      if (iName == GI[i].getName() && i < GILS)
      {
        //cout the name, inventory, price, tax
        cout << setw(10) << iName << setw(10) << GI[i].getInventory() << setw(10) <<
        GI[i].getPrice() << setw(10) << GI[i].getTax() << endl;
      }

      //wrong name is entered
      else if (i == GILS)
      {
        cout << "Err: The name you enterred cannot be found in the inventory." << endl;
      }
    }
  }

  //if such name is not specified
  else
  {
    for (int i = 0; i < GILS; i ++)
    {
      //cout the name, inventory, price, tax
      cout << setw(10) << GI[i].getName() << setw(10) << GI[i].getInventory() << setw(10) <<
      GI[i].getPrice() << setw(10) << GI[i].getTax() << endl;
    }
  }
}

void changePrice(istringstream & sstream, groceryitem GI[], const int GILS)
{
  string iName;
  double iPrice;
  double Value;

  //strema in from myline
  sstream >> iName >> Value;

  for (int i = 0; i < GILS; i ++)
  {
    //find "iName" in the scope of GI
    if (iName == GI[i].getName())
    {
      iPrice = GI[i].getPrice();
      if (Value < GI[i].getPrice())
      {
        GI[i].decreasePrice(GI[i].getPrice() - Value);
      }
      else if (Value >= GI[i].getPrice())
      {
        GI[i].increasePrice(Value - GI[i].getPrice());
      }
    }
  }
}

pair <double, double> import(istringstream & sstream, groceryitem GI[], const int GILS)
{
  string iName;
  int iUnit;
  double iPrice;
  double iTax;
  int Unit; //to be imported

  //find the inventory being referred to, output the price and tax
  sstream >> iName >> Unit;

  for (int i = 0; i < GILS; i ++)
  {
    //find "iName" in the scope of GI
    if (iName == GI[i].getName())
    {
      //import the item
      GI[i].increaseInventory(Unit);

      //get the price and tax so as to calculate the charge
      iPrice = GI[i].getPrice();
      iTax = GI[i].getTax();

      //output the price and tax information
      cout << setw(30) << "The price will be " << iPrice * Unit << endl;
      cout << setw(30) << "The tax will be " << iTax * Unit << endl;

      //return
      pair <double, double> charges (iPrice * Unit, iTax * Unit);
      return charges;
    }
  }



  //if the name cannot be found
  cout << "Err: The name you enterred cannot be found in the inventory." << endl;
  pair <double, double> charges (0.0, 0.0);
  return charges;
}

//method to convert all forms of characters to lower case one.
string standardized(string xxx)
{
  string str = xxx;
  for (string::size_type i=0; i < xxx.length(); i ++)
  {
    str[i] = tolower(str[i]);
  }

  return str;
}
