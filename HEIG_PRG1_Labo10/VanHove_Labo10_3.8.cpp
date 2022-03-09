//File: 		    VanHove_Labo10_3.8.cpp
//Author:		    Timothee Van Hove
//Date:			    12.10.2021
//Description:	    Program that outputs the number of days in a month entered by the user
//Input(s)          [Month number(1-12)]
//Output(s)         [Number of days in this month]
//Note(s)           An alternative is commented
//[Compiler][opt]   [g++][-Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic -std=c++20]
//std compatible    c++98 and above

#include <iostream>
#include <string>

const int MONTH_WITH_31_ODD = 7, FEBRUARY = 2;

using namespace std;

int main()
{
    int month = 0;

    //User message
    cout << "Enter a month number (1-12) : ";
    cin >> month;

    // Get the info if the entered month is < or > 7
    bool odd = month <= MONTH_WITH_31_ODD ? true : false;

    //If the month < 7, all the odd month will be 31 if %2 != 0
    //Else all the even month will be 31 if %2 == 0
    bool has31 = odd ? month % 2 : !(month % 2);

    //Get the special number in a string, with the special case of february
    string outResult = month == FEBRUARY ? "28 or 29" : has31 ? "31" : "30";

    //User output
    cout << "This month counts " << outResult << " days" << endl;
}

// Alternative with a generic formula (you must #include <math>)
// int main()
// {
//     int month = 0;

//     //User message
//     cout << "Enter a month number (1-12) : ";
//     cin >> month;

//     // Generic formula to get the number of days in a month
//     int result = 28 + (month + (int)floor(month/8)) % 2 + 2 % month + 2 * floor(1/month);

//     //Get the special case of february (the formula return 28 if 2 is entered)
//     string outResult = result == 28 ? "28 or 29" : to_string(result);

//     //User output
//     cout << "This month counts " << outResult << " days" << endl;
// }


