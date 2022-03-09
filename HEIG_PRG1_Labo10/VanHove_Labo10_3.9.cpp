//File: 		    VanHove_Labo10_3.9.cpp
//Author:		    Timothee Van Hove
//Date:			    12.10.2021
//Description:	    Display the minimum value of 3 number entrerd by the user (integers)
//Input(s)          [number 1] [number 2] [number 3]
//Output(s)         [Minimum value]
//Note(s)           Ex 3.9 from the file "Recueil d'exercices"
//[Compiler][opt]   [g++][-Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic -std=c++20]
//std compatible    c++98 and above

#include <iostream>

using namespace std;

int main()
{
    int number1 = 0, number2 = 0, number3 = 0;

    //User messeg & input
    cout << "Enter 3 values";
    cin >> number1 >> number2 >> number3;

    //Prefix of the user output message
    cout << "The lowest value is : ";

    // Test the values to get the lowest
    if(number1 > number2 && number1 > number3 && number2 > number3)
    {// Number 3 is the lowest
        cout << number3;
    }
    else if(number1 > number2)
    {// Number 2 is the lowest
        cout << number2;
    }
    else
    { // Number 1 is the lowest
        cout << number1;
    }
}