//File: 		VanHove_Labo3.cpp
//Author:		Timothée Van Hove
//Date:			24.09.2021
//Description:	Program transaforms seconds in input to weeks, days, hours, minutes and seconds

#include <iostream> // Used to input and output data in console
#include <cmath>    // Used to trunc values
#include <cstdio>   // Used to pause the console with getchar()
#include <limits>	// Used to display the mx value of an int

using namespace std;

const double SECONDS_IN_WEEKS = 604800;
const double DAYS_IN_WEEKS = 7;
const double HOURS_IN_DAYS = 24;
const double MINUTES_IN_HOURS = 60;
const double SECONDS_IN_MINUTES = 60;

int main()
{
    int seconds;
    cout << "Time in seconds to transform in week, day, hour, miute, second: " << endl;
	cout << "Please enter a positive value between 1 and " << INT_MAX << ": ";
    cin >> seconds;
	
	while(seconds <= 0)
	{
		cout << "Value <= 0, " << "Please enter a positive value between 1 and " << INT_MAX << ": ";
		cin >> seconds;
	}

    // Get the number of weeks
    double weeks = seconds / SECONDS_IN_WEEKS;
	
	//get the number of days left after calculating the number of weeks
    double daysRemainder = (weeks - trunc(weeks)) * DAYS_IN_WEEKS;
	
	//get the number of hours left after calculating the number of days
    double hoursRemainder = (daysRemainder - trunc(daysRemainder)) * HOURS_IN_DAYS;
	
	//get the number of minutes left after calculating the number of hours
    double minutesRemainder = (hoursRemainder - trunc(hoursRemainder)) * MINUTES_IN_HOURS;
	
	//get the number of seconds left after calculating the number of minutes
    double secondsRemainder = (minutesRemainder - trunc(minutesRemainder)) * SECONDS_IN_MINUTES;

	// Display the results
    cout << (int)seconds << " seconds is: ";
    cout << (int)weeks << " Weeks,  ";
    cout << (int)daysRemainder << " Days,  ";
    cout << (int)hoursRemainder << " Hours,  ";
    cout << (int)minutesRemainder << " Minutes,  ";
	
	//Don't cast the seconds as int, it will roud it to the lower value
    cout << secondsRemainder << " Seconds" << endl; 

    cout << "Hit enter to quit";
    getchar();
	getchar();
}