//Patrick Fan
//Feb 25, 2019

#include "groceryitem.h"

#include <iostream>

using namespace std;

//increase the inventory by value
int groceryitem::increaseInventory(const int value)
{
  //Test the case when value is smaller or equal to 0
  if (value < 0)
  {
    cout << "The increase makes sense only if value is greater than 0" << endl;
    return iteminventory; //if so return the orginal value and output error message
  }

  iteminventory += value; //otherwise add the value to itemcount
  return iteminventory;
}

//decrease the inventory by value
int groceryitem::decreaseInventory(const int value)
{
  if ((value < 0) || (iteminventory - value < 0))
  {
    cout << "The decrease makes sense only if value is greater than 0" << endl;
    return iteminventory; //if so return the orginal value and output error message
  }

  iteminventory -= value; //otherwise subtract itemcount by value
  return iteminventory;
}

int groceryitem::increasePrice(const int value)
{
  if (value < 0)
  {
    cout << "The decrease makes sense only if value is greater than 0" << endl;
    return itemprice; //if so return the orginal value and output error message
  }

  itemprice += value; //otherwise add itemPrice by value
  return itemprice;
}

int groceryitem::decreasePrice(const int value)
{
  if ((value < 0) || (itemprice - value < 0))
  {
    cout << "The decrease makes sense only if value is greater than 0" << endl;
    return itemprice; //if so return the orginal value and output error message
  }

  itemprice -= value; //otherwise subtract itemPrice by value
  return itemprice;
}
