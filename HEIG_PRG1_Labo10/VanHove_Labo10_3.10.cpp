//File: 		    VanHove_Labo10_3.10.cpp
//Author:		    Timothee Van Hove
//Date:			    12.10.2021
//Description:	    Outputs 3 numbers in order x > y > z (integers)
//Input(s)          [number x] [number y] [number z]
//Output(s)         [lowest] > [mid] > [highest]
//Note(s)           Ex 3.10 from the file "Recueil d'exercices"
//[Compiler][opt]   [g++][-Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic -std=c++20]
//std compatible    c++98 and above

#include <iostream>
#include <limits>

// used to empty the cin buffer before asking a new entry
#define EMPTY_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n');

using namespace std;

const char LOWER = '<';

int main()
{
    int number1 = 0, number2 = 0, number3 = 0;

    //User messeg & input
    cout << "Enter 3 values";
    cin >> number1 >> number2 >> number3;

    //Prefix of the user output message
    cout << "The order is : ";

    // Test the values to get the order
    if (number1 > number2 && number1 > number3)
    {//Number 1 is the highest
        if (number2 > number3)
        {
            // Number 3 is the lowest
            cout << number3 << LOWER << number2 << LOWER << number1;
        }
        else
        {
            // Number 2 is the lowest
            cout << number2 << LOWER << number3 << LOWER << number1;
        }
    }
    else if (number2 > number1 && number2 > number3)
    {//Number 2 is the highest
        if (number1 > number3)
        { // Number 3 is the lowest
            cout << number3 << LOWER << number1 << LOWER << number2;
        }
        else
        { // Number 1 is the lowest
            cout << number1 << LOWER << number3 << LOWER << number2;
        }
    }
    else if (number1 > number2)
    { //Number 3 is the highest, 2 lowest
        cout << number2 << LOWER << number1 << LOWER << number3;
    }
    else
    { //Number 3 is the highest, 1 lowest
        cout << number1 << LOWER << number2 << LOWER << number3;
    }
}