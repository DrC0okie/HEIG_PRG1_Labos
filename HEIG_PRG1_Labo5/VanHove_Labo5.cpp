//File: 		        VanHove_Labo5.cpp
//Author:		        Timothee Van Hove
//Date:			        29.09.2021
//Description:	        Program that outputs the hour and minute in function of the angle given in input
//                      The angles turns counter clock wise, and the 0° is at 3h (trigonometric circle)
//[Compiler][options]:  [g++][-Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic -std=c++20]

#include <cstdlib> //Ensure compatibility for compilers that use standard < c++11
#include <iostream>

using namespace std;

const double HOUR_MAX = 12.0, ANGLE_MAX = 360.0, OFFSET_TIME = 3.0, NB_MINUTES_IN_HOUR = 60.0;

void emptyBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    int angle = 0;
    cout << "Enter an angle between 0 - 360°" << endl;
    cin >> angle;
    emptyBuffer();

    //Get the decimal hour from the given angle
    //360 is used in negative because the angles rotate CCW
    double decimalHour = (angle % 360 / -ANGLE_MAX * HOUR_MAX);

    //Add 3 hours offset (90°) to align 0° with  12h
    decimalHour += OFFSET_TIME;

    //Add 12 to the hour to avoid the 0 value
    decimalHour += HOUR_MAX;

    //Get the minutes from the decimal hour
    int minutes = (int)(decimalHour * NB_MINUTES_IN_HOUR) % 60;

    //Decrement the hour to avoid the 0 value
    decimalHour--;

    //Round the decimal hour with modulo to avoid the values 13, 14 and 15
    int roundHour = (int)(decimalHour) % 12;

    //Re-increment the hour
    roundHour++;

    //Display th results
    cout << angle << "° represents " << roundHour << "h " << minutes << endl;

    return EXIT_SUCCESS;
}