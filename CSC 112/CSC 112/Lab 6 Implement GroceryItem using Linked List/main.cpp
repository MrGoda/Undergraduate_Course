//Patrick Fan
//Feb 25, 2019

#include <utility>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>

#include "myCommands.h"
#include "groceryitem.h"
#include "SLLList.h"
#include "SLLNode.h"

using namespace std;

//basic i/o, deals with reading the command and executing the command
int main()
{
  string xxx; //store cin temporarily

  SLLList GI; //Storage
  SLLList GItemp; //temporary storage storing what is brought

  //If any item is brought, the dues are stored here
  double pricedue = 0.0;
  double taxdue = 0.0;

  //the total price paid and spent
  double pricesum = 0.0;
  double taxsum = 0.0;
  double pricecharge = 0.0;
  double taxcharge = 0.0;

  int itemp = 0; //itemp determine if the file is opened/in operation

  cout << "Hey! Plz type your command here: "; //cout

  //extract the first word in cin, store it in xxx
  while (getline (cin, xxx))
  {
    istringstream myline (xxx); //use sstream to seperate words

    //temp to store the first word, and comm to be standardized first word
    string temp, comm;
    myline >> temp;
    comm = standardized(temp); //convert temp to lower case mode

    //open the file and write the data into GI
    if (comm == "open")
    {
      readData(GI, "inventory.txt");
      itemp = 1;
    }

    //close the file while wirte the data into the text file
    else if (comm == "close")
    {
      //Operate only if open operation has been executed
      if (itemp == 1)
      {
        writeData(GI, "inventory.txt");
        itemp = 0;

        //record the total money and tax collected. Number of items sold
        cout << setw(40) << "The money collected is: " << setw(10) << pricesum << endl;
        cout << setw(40) << "The tax collected is: " << setw(10) << taxsum << endl;
        cout << setw(40) << "The money spent on importing/additem is: " << setw(10) << pricecharge << endl;
        cout << setw(40) << "The tax spent on importing/additem is: " << setw(10) << taxcharge << endl;
        cout << setw(40) << "The items being sold today include: " << endl;
        cout << setw(8) << "Name" << setw(8) << "Unit" << setw(8) << "Price" << setw(8) << "Tax" << endl;
        for (SLLNode * index = GItemp.getFirst(); index != NULL; index = index -> getNext())
        {
          cout << setw(8) << index -> getName() << setw(8) << index -> getInventory() <<
          setw(8) << (index -> getPrice()) * (index -> getInventory()) << setw(8) <<
          (index -> getTax()) * (index -> getInventory()) << endl;
        }

        break;
      }

      else //If open operation has not been executed, cout error message
      {
        cout << "Err: The file has not been opened yet." << endl;
      }
    }

    //buy the item required, show the information for that method
    else if (comm == "buy")
    {
      if (itemp == 1) //if the file is opened
      {
        pair <double, double> dues; //return type for buyIt
        dues = buyIt(myline, GI, GItemp);

        //import the dues
        pricedue += dues.first;
        taxdue += dues.second;
      }

      else //If open operation has not been executed, cout error message
      {
        cout << "Err: The file has not been opened yet." << endl;
      }
    }

    //pay the dues
    else if (comm == "pay")
    {
      if (itemp == 1)
      {
        //import dues to sum being paid, clear dues.
        pricesum += pricedue;
        taxsum += taxdue;

        cout << "You pay: " << pricedue << " and " << taxdue << " of tax." << endl;

        pricedue = 0;
        taxdue = 0;
      }

      else //If open operation has not been executed, cout error message
      {
        cout << "Err: The file has not been opened yet." << endl;
      }
    }

    //print what is in the inventory
    else if (comm == "status")
    {
      if (itemp == 1)
      {
        print(myline, GI);
      }

      else //If open operation has not been executed, cout error message
      {
        cout << "Err: The file has not been opened yet." << endl;
      }
    }

    //if the price is updated
    else if (comm == "changeprice")
    {
      if (itemp == 1)
      {
        changePrice(myline, GI);
      }

      else //If open operation has not been executed, cout error message
      {
        cout << "Err: The file has not been opened yet." << endl;
      }
    }

    //e.g "import sofa 2" will add two sofa to the inventory
    else if (comm == "import")
    {
      if (itemp == 1)
      {
        pair <double, double> charges; //return type for buyIt
        charges = import(myline, GI);

        //import the charges
        pricecharge += charges.first;
        taxcharge += charges.second;
      }

      else //If open operation has not been executed, cout error message
      {
        cout << "Err: The file has not been opened yet." << endl;
      }
    }

    else if (comm == "additem")
    {
      if (itemp == 1)
      {
        pair <double, double> addingCharges; //return type for buyIt
        addingCharges = add(myline, GI);

        //import the charges
        pricecharge += addingCharges.first;
        taxcharge += addingCharges.second;
      }

      else //If open operation has not been executed, cout error message
      {
        cout << "Err: The file has not been opened yet." << endl;
      }
    }

    else if (comm == "remove")
    {
      if (itemp == 1)
      {
        remove(myline, GI);
      }

      else //If open operation has not been executed, cout error message
      {
        cout << "Err: The file has not been opened yet." << endl;
      }
    }

    else
    {
      cout << "Err: wrong spelling or incorrect commands." << endl;
    }

    cout << "Next command: "; //cout loop
  }

  return 0;
}
