// File:        VanHove_Labo11_3.20.cpp
// Author:      Timothee Van Hove
// Date:        15.10.2021
// Description: Program that outputs numbers from MAX_NUMER to 1 by line of 3 numbers
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <iomanip>

using namespace std;

const int WIDTH = 4, MAX_NUMER = 20;

int main()
{
    int count = MAX_NUMER;
    while (count > 0)
    {
        // Output the number and the next width
        cout << count << setw(WIDTH);

        // If the count is a multiple of 3, add a line
        !(count % 3) && cout << "\n";

        // Decrement the counter
        count--;
    }
}

// Variant with a for loop
// int main()
// {
//     for (int i = MAX_NUMER; i > 0; i--)
//     {
//         // Output the number and the next width
//         cout << i << setw(WIDTH);

//         //If the count is a multiple of 3, add a line
//         !(i % 3) && cout << "\n";
//     }
// }