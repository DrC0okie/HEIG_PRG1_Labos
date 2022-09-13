//File: 		VanHove_Labo3.cpp
//Author:		Timothée Van Hove
//Date:			24.09.2021
//Description:	Program transaforms seconds in input to weeks, days, hours, minutes and seconds

#include <iostream> // Used to input and output data in console
#include <limits>	// Used to display the max value of an int

using namespace std;

const double SECONDS_IN_WEEKS = 604800;
const double DAYS_IN_WEEKS = 7;
const double HOURS_IN_DAYS = 24;
const double MINUTES_IN_HOURS = 60;
const double SECONDS_IN_MINUTES = 60;
const int MAX_INT = numeric_limits<int>::max();

int main()
{
    int seconds;
    cout << "Enter time[sec] (1 - " << MAX_INT << ")" << endl;
    cin >> seconds;
	
	while(seconds <= 0)
	{
		cout << "Value <= 0, " << "Please enter a positive value between 1 and " << MAX_INT << ": ";
		cin >> seconds;
	}

    // Get the number of weeks
    double weeks = seconds / SECONDS_IN_WEEKS;
	
	//get the number of days left after calculating the number of weeks
	// Casting to int for truncating the real value
    double daysRemainder = (weeks - int(weeks)) * DAYS_IN_WEEKS;
	
	//get the number of hours left after calculating the number of days
    double hoursRemainder = (daysRemainder - int(daysRemainder)) * HOURS_IN_DAYS;
	
	//get the number of minutes left after calculating the number of hours
    double minutesRemainder = (hoursRemainder - int(hoursRemainder)) * MINUTES_IN_HOURS;
	
	//get the number of seconds left after calculating the number of minutes
    double secondsRemainder = (minutesRemainder - int(minutesRemainder)) * SECONDS_IN_MINUTES;

	// Display the results
    cout << (int)seconds << " seconds corresponds to : ";
    cout << (int)weeks << " Weeks,  ";
    cout << (int)daysRemainder << " Days,  ";
    cout << (int)hoursRemainder << " Hours,  ";
    cout << (int)minutesRemainder << " Minutes,  ";
    cout << secondsRemainder << " Seconds" << endl; 
}