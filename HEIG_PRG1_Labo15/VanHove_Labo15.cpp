// File:        VanHove_Labo13_3.32.cpp
// Author:      Timothee Van Hove
// Date:        22.10.2021
// Description: finds the MCD and the modular exponent
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <limits>

using namespace std;

int ModularExponent(int base, int exp, int mod);
int MCD(int num1, int num2);

int main()
{
    // User message and input
    int num1, num2;
    cout << "MDC: enter the 2 numbers separated by spaces : ";

    while (!(cin >> num1 >> num2))
    {
        cout << "Incorrect entry, please retry : ";
        cin.clear();
        cin.ignore(numeric_limits<int>::max(), '\n');
    }

    // User ouput with the result
    cout << "The MCD is:  " << MCD(num1, num2) << endl;;

    cout << "Modular exponent: enter the base, exponent, and modulo separated by spaces : ";

    int base, exp, mod;
    while (!(cin >> base >> exp >> mod) && base < 1 && exp < 1 && mod < 1)
    {
        cout << "Incorrect entry, please retry : ";
        cin.clear();
        cin.ignore(numeric_limits<int>::max(), '\n');
    }

    cout << "The modular exponent is :  " << ModularExponent(base, exp, mod);
}

int ModularExponent(int base, int exp, int mod)
{
    int result = 1;

    while (exp > 0)
    {
        if (!(exp % 2))
        { // Exponent is even
            base = (base * base) % mod;
            exp /= 2;
        }
        else
        { // Exponent is odd
            result = (result * base) % mod;
            exp -= 1;
        }
    }
    return result;
}

int MCD(int num1, int num2)
{
    // Loop that uses the euclidean division to find the MCD
    while (num2 != 0)
    {
        // Save the value of divider
        int temp = num2;

        // find the remainder of number / divider
        num2 = num1 % num2;

        // Refresh number with divider before re-looping
        num1 = temp;
    }

    return num1;
}