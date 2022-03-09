// File:        VanHove_Labo17_4.16a.cpp
// Author:      Timothee Van Hove
// Date:        08.11.2021
// Description: Program that calculates the syracuse suite of the given number
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>

using namespace std;

const int MIN = 1, MAX = 10000;
int getSyracuse(int number);

int main()
{
    // User message
    cout << "Please enter a number between " << MIN << " and " << MAX << " : ";

    // User input control
    int number;
    while (!(cin >> number) || number < MIN || number > MAX)
    {
        cout << "Please enter a integer value between" << MIN << " and " << MAX
             << "Please retry : ";
    }

    // Get the syracuse suite for the given user input
    int cnt = getSyracuse(number);
    cout << "--- " << cnt << " iterations";
}

/** @brief Computes the syracuse suite (Collatz conjecture)
 * @param number The number from which the suite starts
 * @return The number of iterations*/
int getSyracuse(int number)
{
    int cnt = 0;
    while (number != 1)
    {
        if (number % 2 == 0)
            number /= 2;
        else
            number = number * 3 + 1;
        cout << number << " ";
        cnt++;
    }
    return cnt;
}