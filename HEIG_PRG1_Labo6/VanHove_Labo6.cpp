//File: 		    VanHove_Labo6.cpp
//Author:		    Timothee Van Hove
//Date:			    01.10.2021
//Description:	    Program that calculates the duration between 2 hours
//Input(s)          Dep. Hour [HH], Dep. minutes[MM], Arrival Hour [HH], Arrival minutes [MM]
//Output(s)         Duration [HH:MM]
//Note(s)           -Wsign-conversion will raise. The implicit casts is intended
//[Compiler][opt]   [g++][-Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic -std=c++20]

#include <cstdlib> //Ensure compatibility for compilers that use standard < c++11
#include <iostream>
#include <limits>

// used to empty the cin buffer before asking a new entry
#define EMPTY_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n');

const int SECONDS_IN_HOUR = 60, NB_HOUR_MAX = 24;
const double SECONDS_IN_HOUR_FP = 60.0;

using namespace std;

int main()
{
    // User messages for the input
    int startHour = 0, startMinute = 0, arrivalHour = 0, arrivalMinute = 0;
    cout << "Enter the departure hour: ";
    cin >> startHour;
    cout << "Enter the departure minute: ";
    cin >> startMinute;
    cout << "Enter the arrival hour: ";
    cin >> arrivalHour;
    cout << "Enter the arrival minute: ";
    cin >> arrivalMinute;

    // Get the total duration in seconds
    int totalDuration = (arrivalHour - startHour) * SECONDS_IN_HOUR + (arrivalMinute - startMinute);

    // Get the hours from the total duration.
    // SECONDS_IN_HOUR_FP (double) is used in case of negative value (avoid the trunc before the addition)
    // This implicit cast will raise -Wsign-conversion message.
    int durationHour = (totalDuration / SECONDS_IN_HOUR_FP) + NB_HOUR_MAX;
    durationHour %= NB_HOUR_MAX;

    // Get the minutes from the total duration
    int durationMinutes = (totalDuration + SECONDS_IN_HOUR) % SECONDS_IN_HOUR;

    // Output the result for the user
    cout << "The trip lasted " << durationHour << ":" << durationMinutes << endl;

    cout << "Hit enter to quit...";
    EMPTY_BUFFER
    getchar();
    return EXIT_SUCCESS;
}