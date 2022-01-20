//Patrick Fan
//Apr 24, 2019

#include <stack>
#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <math.h>

using namespace std;

//method declarations
void eval2 (stack<float> &, double (*)(double, double));
void eval1 (stack<float> &, double (*)(double));
double add(double, double);
double funcDelete(double, double);
double time(double, double);
double divide(double, double);

int main(int argc, char ** argv)
{
  stack <float> mystack;
  float operant1;
  float operant2;

  //loop through all parameters in argv
  for (int i = 1; i < argc; i ++)
  {
    char myword = argv[i][0];

    //check if argv[i] is digit
    if (isdigit(myword))
    {
      mystack.push(atof(argv[i])); //record the value
    }

    else //if argv[i] is not digit
    {
      //do + operation
      if (myword == '+')
      {
        eval2(mystack, add);
      }

      //do - operation
      else if (myword == '-')
      {
        eval2(mystack, funcDelete);
      }

      // * operation
      else if (myword == '*')
      {
        eval2(mystack, time);
      }

      // / operation
      else if (myword == '/')
      {
        eval2(mystack, divide);
      }

      //do power operation
      else if (myword == '^')
      {
        eval2(mystack, pow);
      }

      //do square root operation
      else if (myword == 's')
      {
        eval1(mystack, sqrt);
      }

      else //if argv[i] is any other symbols, abort and report error
      {
        cout << "ERR: The " << i << " character cannot be read." << endl;
        return -1;
      }
    }
  }

  if (mystack.size() == 1) //the program runs well
  {
    cout << "Result: " << mystack.top() << endl;
  }

  else //wrong vaue of stack
  {
     cout << "ERR: more than/no value in stack." << endl;
  }

  return 0;
}

//taking care of repeated methods, with methods involving two parameters
void eval2 (stack<float> & mystack, double (*f)(double, double))
{
  double operant1 = mystack.top();
  mystack.pop();
  double operant2 = mystack.top();
  mystack.pop();
  mystack.push(f(operant1, operant2));
}

//taking care of repeated methods, with methods involving one parameters
void eval1 (stack<float> & mystack, double (*f)(double))
{
  double operant1 = mystack.top();
  mystack.pop();
  mystack.push(f(operant1));
}

//wrapper function for adding
double add(double x, double y)
{
  return x + y;
}

//wrapper function for deleting
double funcDelete(double x, double y)
{
  return x - y;
}

//wrapper function for timing
double time(double x, double y)
{
  return x * y;
}

//wrapper function for dividing
double divide(double x, double y)
{
  return x / y;
}
