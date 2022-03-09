// File:        VanHove_Labo11_3.19.cpp
// Author:      Timothee Van Hove
// Date:        15.10.2021
// Description: Outputs the number of year after which the initial amount has doubled
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int PERCENT = 100, PRECISION = 2;
const double DOUBLE_AMOUNT = 2;

int main()
{
    int initialAmount = 0;
    double interestRate = 0.0;

    // User message & input
    cout << "Please enter an amount and an annual interest rate" << endl;
    cin >> initialAmount >> interestRate;

    int nbYears = 0;
    double newAmount = initialAmount;

    // Calulate the number of year the amout will double
    while( initialAmount * DOUBLE_AMOUNT > newAmount)
    {
        // Get the interest amount
        double interest = newAmount * interestRate / PERCENT;

        // Get the new amount
        newAmount += interest;

        // Increment year
        nbYears ++;
    }

    cout << "After " << nbYears << " year" << (nbYears > 1? "s" : "")
    << " you will have doubled your initial amount." << endl
    << fixed << setprecision(PRECISION) << "You will have " << newAmount << ".-";
    return EXIT_SUCCESS;
}

// Without any loop
// #include <cmath>

// int main()
// {
//     int initialAmount = 0;
//     double interestRate = 0.0;

//     // User message & input
//     cout << "Please enter an amount and an annual interest rate" << endl;
//     cin >> initialAmount >> interestRate;

//     // Calulate the number of year the amout will double
//     double nbYears = ceil(log(2) / log(1 + (interestRate / 100)));

//     // Caluculaite the final amount in the account
//     double amount = initialAmount * pow(1 + interestRate / 100, nbYears);

//     // User output message with results
//     cout << "After " << nbYears << " year" << (nbYears > 1 ? "s" : "")
//          << " you will have doubled your initial amount." << endl
//          << fixed << setprecision(PRECISION) << "You will have " << amount << ".-";

//     return EXIT_SUCCESS;
// }