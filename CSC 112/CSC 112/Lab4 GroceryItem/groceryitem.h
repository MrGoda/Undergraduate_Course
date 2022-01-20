//Patrick Fan
//Feb 25, 2019

#ifndef GROCERYITEM_H
#define GROCERYITEM_H

#include <string>

using namespace std;

class groceryitem
{
//private variables & functions
private:
  string itemname;
  int iteminventory;
  double itemprice;
  double itemtax;

//public variables & functions
public:
  //empty constructor
  groceryitem()
  {
    itemname = "";
    iteminventory = 0;
    itemprice = 0.0;
    itemtax = 0.0;
  }

  //normal constructor
  groceryitem(const string & iName, const int iInventory, const double price, const double tax)
  {
    itemname = iName;
    iteminventory = iInventory;
    itemprice = price;
    itemtax = tax;
  }

  string getName() {return itemname;} //return the name
  int getInventory() {return iteminventory;}  //return the count of inventory
  double getPrice() {return itemprice;} //return the price of the item
  double getTax() {return itemtax;} //return the tax of the item

  //both increasing or decreasing the count in inventory. More specific codes in cpp file
  int increaseInventory(const int value);
  int decreaseInventory(const int value);
  int increasePrice(const int value);
  int decreasePrice(const int value);

};

#endif
