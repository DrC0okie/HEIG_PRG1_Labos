//File: 		    VanHove_Labo8.cpp
//Author:		    Timothee Van Hove
//Date:			    06.10.2021
//Description:	    Calculates the volume of a container made of 2 cyl. and a trunc. cone
//Input(s)          [radius cyl1][height cyl1][radius cyl2][heigth cyl2][height cone]
//Output(s)         The calculted volume with 3 floating point precision
//Note(s)           Inputs are in cm output is in l (dm3)
//[Compiler][opt]   [g++][-Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic -std=c++20]
//std compatible    c++98 and above

#include <iostream>
#include <cstdio>
#include <limits>
#include <cmath>
#include <iomanip>

// used to empty the cin buffer before asking a new entry
#define EMPTY_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n');

using namespace std;

const double THIRD = 1 / 3.0, CONV_DM3 = 1000;

int main()
{
    double r1 = 0.0, h1 = 0.0, r2 = 0.0, h2 = 0.0, h3 = 0.0;

    // User message & user input
    cout << "Please enter the values to compute [r1] [h1] [r2] [h2] [h3] in cm" << endl;
    cin >> r1 >> h1 >> r2 >> h2 >> h3;

    // Get pi
    double pi = 2 * acos(0);

    // Get the volume of the bas cylinder with the formula [π * r² * h]
    double volumeCyl1 = pi * r1 * r1 * h1;

    // Get the volume of the top cylinder with the formula [π * r² * h]
    double volumeCyl2 = pi * r2 * r2 * h1;

    // Get the volume of the trucated cone with the formula [1/3 * π * h * (R² + r² + R * r)]
    double volumeCone = THIRD * pi * h3 * (r1 * r1 + r2 * r2 + r1 * r2);

    // Get the total volume by addition [V1 + V2 + V3]
    double volumeContainer = volumeCyl1 + volumeCyl2 + volumeCone;

    // Get the volume from cm³ in dm³
    volumeContainer /= CONV_DM3;

    // Output the result to the user with 3 floating point precision
    cout << setprecision(3) << fixed 
         << "The container volume is " << volumeContainer << " litres" << endl;

    // Clear the cin buffer as the \n\r is still present and the next getchar would be uneffective
    EMPTY_BUFFER

    // Use of getchar otherwise the console closes at the end of the program execution
    cout << "Hit enter to quit";
    getchar();
}