#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctype.h>
#include <bits/stdc++.h>

using namespace std;

string pigLatin(string); //make sure that pigLatin is valid in main()

int main()
{
  //insteam
  ifstream myFile;
  myFile.open("data.txt");
  string myLine;
  int tempA = 0;

  //load in words from data.txt to istringstream
  while (getline(myFile, myLine))
  {
    istringstream myWords(myLine);
    string indiv;

    //Load in words from myLine to indiv
    while (myWords >> indiv)
    {
      string PSymbol = ""; //Punctuation Symbol

      if (ispunct(indiv.back()))
      {
        //reorganize the word with punctuation in the back
        PSymbol = indiv.back();
        indiv.pop_back();
      }

      //check if there is digit
      int n = indiv.length();
      char char_array[n + 1];
      strcpy(char_array, indiv.c_str());
      for (int i = 0; i < n; i ++)
      {
        if (isdigit(char_array[i]))
        {
          tempA = 1;
        }
      }
      cout << pigLatin(indiv) << PSymbol << " ";
    }

    cout << endl;
  }

  //Print error message if there exists digits
  if (tempA == 1)
  {
    cout << endl;
    cout << "ERR in conversion: Digit Detected." << endl;
  }

  myFile.close(); //close the ifstream
}

string pigLatin(string xxx)
{
  string original = xxx;
  string tempB;

  //treat the word differently in 3 ways
  if ((original.find_first_of("aeiou") == string::npos))
  {
    //case 1: it is not a word (with no vowel. This word is then converted to "*"")
    if ((original.find_first_of("y") == string::npos))
    {
      tempB = "*";
    }
    //case 2: y is the first vowel.
    else if((original.find_first_of("y") != string::npos))
    {
      size_t found = original.find_first_of("y");
      tempB = original.substr(found, string::npos) + original.substr(0, found) + "ay";
    }
  }

  //case 3: the first vowel is a normal vowel (aeiou).
  else if (original.find_first_of("aeiou") != string::npos)
  {
    size_t found = original.find_first_of("aeiou");
    tempB = original.substr(found, string::npos) + original.substr(0, found) + "ay";
  }

  return tempB;
}
