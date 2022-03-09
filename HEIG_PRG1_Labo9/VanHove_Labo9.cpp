//File: 		    VanHove_Labo9.cpp
//Author:		    Timothee Van Hove
//Date:			    08.10.2021
//Description:	    Convertion of °C to °F or °F => °C depending of the user's input
//Input(s)          [temperature] [conversion unit]
//Output(s)         [temperature]
//Note(s)           Not case sensitive for the conversion unit
//[Compiler][opt]   [g++][-Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic -std=c++20]
//std compatible    c++98 and above

#include <iostream>
#include <limits>

// used to empty the cin buffer before asking a new entry
#define EMPTY_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n');

using namespace std;

const double CONVERT_FACTOR = 1.8;

const int CONVERT_OFFSET = 32, ASCII_SHIFT = 32, ASCII_LOW_CASE = 97;

int main()
{
    char destUnit = 0;
    double temperatureIn = 0.0, result = 0.0;
    char depUnit;

    // User message & user input
    cout << "Enter the temperature and the unit to conver to: [temp] [=> unit]" << endl;
    cin >> temperatureIn >> destUnit;

    // Transforms the letter to upper case => conversion input not case sensitive
    destUnit = destUnit >= ASCII_LOW_CASE ? destUnit - ASCII_SHIFT : destUnit;

    // Input verification for the char conversion input
    if(destUnit != 'C' && destUnit != 'F')
    {
        cout << "Wrong unit entered. Hit enter to close the program";
        EMPTY_BUFFER
        getchar();
        return 0;
    }
    else if (destUnit == 'C')
    {// Convert to Celsius if entered letter c or C
        result = (temperatureIn - CONVERT_OFFSET) / CONVERT_FACTOR;
        depUnit = 'F';
    }
    else 
    {// Convert to Faranheit if entered letter f or F
        result = temperatureIn * CONVERT_FACTOR + CONVERT_OFFSET;
        depUnit = 'C';
    }

    // Output message & result for the user
    cout << temperatureIn << " °" << depUnit << " = " << result << " °" << destUnit << endl;

    // Clear the cin buffer as the \n\r is still present and the next getchar would be uneffective
    EMPTY_BUFFER

    // Use of getchar otherwise the console closes at the end of the program execution
    cout << "Hit enter to quit";
    getchar();
}