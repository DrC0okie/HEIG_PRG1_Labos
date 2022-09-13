//File: 		    VanHove_Labo6.cpp
//Author:		    Timothee Van Hove
//Date:			    01.10.2021
//Description:	    Program that calculates the duration between 2 hours
//Input(s)          Dep. Hour [HH], Dep. minutes[MM], Arrival Hour [HH], Arrival minutes [MM]
//Output(s)         Duration [HH:MM]
//Note(s)           -Wsign-conversion will raise. The implicit casts are intended
//[Compiler][opt]   [g++][-Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic -std=c++20]

#include <iostream>
#include <limits>

const int SECONDS_IN_HOUR = 60, NB_HOUR_MAX = 24;
const double SECONDS_IN_HOUR_FP = 60.0;

using namespace std;

void emptyBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    // User messages for the input
    int startHour, startMinute, arrivalHour, arrivalMinute;
    cout << "Enter the departure hour: ";
    cin >> startHour;
	emptyBuffer();
    cout << "Enter the departure minute: ";
    cin >> startMinute;
	emptyBuffer();
    cout << "Enter the arrival hour: ";
    cin >> arrivalHour;
	emptyBuffer();
    cout << "Enter the arrival minute: ";
    cin >> arrivalMinute;
	emptyBuffer();

    // Get the total duration in seconds
	int deltaHour = arrivalHour - startHour;
	int deltaMin = arrivalMinute - startMinute;
    int totalDuration = deltaHour * SECONDS_IN_HOUR + deltaMin;

    // Get the hours from the total duration.
    // SECONDS_IN_HOUR_FP (double) is used in case of negative value (avoid the trunc before the addition)
    int durationHour = int((totalDuration / SECONDS_IN_HOUR_FP) + NB_HOUR_MAX);
    durationHour %= NB_HOUR_MAX;

    // Get the minutes from the total duration
    int durationMinutes = (totalDuration + SECONDS_IN_HOUR) % SECONDS_IN_HOUR;

    // Output the result for the user
    cout << "The trip lasted " << durationHour << ":" << durationMinutes << endl;
    return EXIT_SUCCESS;
}