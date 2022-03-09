//File: 		    VanHove_Labo7.cpp
//Author:		    Timothee Van Hove
//Date:			    05.10.2021
//Description:	    Program that adds 2 distances entered in input and outputs the result
//Input(s)          [1st distance][2nd distance]
//Output(s)         1st distance + 2nd distance
//Note(s)           Input and output format is [0-999Km] [0-999m] [0-99cm] [0-9mm]
//[Compiler][opt]   [g++][-Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic -std=c++20]
//std compatible    c++98 and above

#include <iostream>
#include <cstdio>
#include <limits>

// used to empty the cin buffer before asking a new entry
#define EMPTY_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n');

using namespace std;

const int KM_FACTOR = 1000, MOD_LAST_3_DIGITS = 1000, MOD_LAST_2DIGITS = 100, MOD_LAST_DIGIT = 10;
const double MM_DIVIDER = 1000.0, CM_DIVIDER = 100.0;

int main()
{
    //To save int variables, it is possible to store the inputs in only one set of 4 int var
    //But then it would'nt be possible to output the result in the format asked by the lab
    int firstInDist_Km = 0, firstInDist_m = 0, firstInDist_cm = 0, firstInDist_mm = 0;
    int secondInDist_Km = 0, secondInDist_m = 0, secondInDist_cm = 0, secondInDist_mm = 0;
    int result_Km = 0, result_m = 0, result_cm = 0, result_mm = 0;

    // First user message + user input
    cout << "Enter the 1st distance: [0-999Km] [0-999m] [0-99cm] [0-9mm]" << endl;
    cin >> firstInDist_Km >> firstInDist_m >> firstInDist_cm >> firstInDist_mm;

    // The Addition of all the entered values with corresponding factor
    double result = firstInDist_mm / MM_DIVIDER
                    + firstInDist_cm / CM_DIVIDER
                    + firstInDist_m 
                    + firstInDist_Km * KM_FACTOR;

    // Second user message + user input
    cout << "Enter the 2nd distance: [0-999Km] [0-999m] [0-99cm] [0-9mm]" << endl;
    cin >> secondInDist_Km >> secondInDist_m >> secondInDist_cm >> secondInDist_mm;

    // Addition of the first entered values with the second entered values
    result = result + (secondInDist_mm / MM_DIVIDER
                    + secondInDist_cm / CM_DIVIDER
                    + secondInDist_m
                    + secondInDist_Km * KM_FACTOR);

    // Get the km from the result by simple division + cast
    result_Km = (int)(result / KM_FACTOR);

    // Get the m from the result with modulo
    result_m = (int)result % MOD_LAST_3_DIGITS;

    // Get the cm & mm from the result by shifting the floating point & modulo
    result_cm = (int)(result * CM_DIVIDER) % MOD_LAST_2DIGITS;
    result_mm = (int)(result * MM_DIVIDER) % MOD_LAST_DIGIT;

    // Output the result for the user
    cout << firstInDist_Km << "km, " << firstInDist_m << "m, "
         << firstInDist_cm << "cm, " << firstInDist_mm << "mm + ";

    cout << secondInDist_Km << "km, " << secondInDist_m << "m, "
         << secondInDist_cm << "cm, " << secondInDist_mm << "mm is:" << endl;;

    cout << result_Km << "km, " << result_m << "m, " 
         << result_cm << "cm, " << result_mm << "mm" << endl;

    // Clear the cin buffer as the \n\r is still present and the next getchar would be uneffective
    EMPTY_BUFFER

    // Use of getchar otherwise the console closes at the en of the program execution
    cout << "Hit enter to quit";
    getchar();
}