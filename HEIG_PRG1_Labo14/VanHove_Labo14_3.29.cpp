// File:        VanHove_Labo14_3.28.cpp
// Author:      Timothee Van Hove
// Date:        20.10.2021
// Description: Program that finds the Lowest common multiple of 2 numbers (LCM)
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <limits>

using namespace std;

int main()
{

    int num1 = 0, num2 = 0;
    cout << "Enter the 2 numbers separated by spaces : ";
    cin >> num1 >> num2;

    // User input control
    while (num1 <= 0 && num2 <= 0)
    {
        cout << "The numbers must be > 0, please re-enter the numbers : ";
        cin >> num1 >> num2;
    }

    // maximum value between num1 and num2 is stored in i
    int max = (num1 > num2) ? num1 : num2;
    int i = max;

    // If num1 % num2 = 0 the LCM is found
    while (i % num1 != 0 || i % num2 != 0)
    {
        // Verify that i does not exceed INT_MAX
        if (INT_MAX - i > num2 or num2 < INT_MIN - i)
        {
            // We increment i with max, to avoid too many loops
            i += max;
        }
        else
        {
            cout << "The LCM was not found in the range 0 - " << INT_MAX;
            return 1;
        }
    }

    cout << "Lowest common multiple = " << i << endl;
}