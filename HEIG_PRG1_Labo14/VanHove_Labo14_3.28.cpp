// File:        VanHove_Labo13_3.32.cpp
// Author:      Timothee Van Hove
// Date:        18.10.2021
// Description: Program that adds the first 10^7 members of the harmonic sequence
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <cmath>

using namespace std;

const float MIN_RANGE_F = 1.f, MAX_RANGE_F = 10'000'000.f;
const double MIN_RANGE_D = 1.0, MAX_RANGE_D = 10'000'000.0;

int main()
{
    float resultf = 0.0;
    for (float i = MIN_RANGE_F; i <= MAX_RANGE_F; i++)
    {
        resultf += 1.f / i;
    }
    cout << "1 : With type float from 1 to 10^7, the result is: " << resultf << endl;

    // 2nd try with the type float from 10'000'000 to 1
    resultf = 0.0;
    for (float i = MAX_RANGE_F; i >= MIN_RANGE_F; i--)
    {
        resultf += 1.f / i;
    }
    cout << "2 : With type float from 10^7 to 1, the result is: " << resultf << endl;

    // 3rd try with the type double from 1 to 10'000'000
    double resultd = 0.0;
    for (double i = MIN_RANGE_D; i <= MAX_RANGE_D; i++)
    {
        resultd += 1.0 / i;
    }
    cout << "3 : With type double from 1 to 10^7, the result is: " << resultd << endl;

    // 4th try with the type double from 10'000'000 to 1
    resultd = 0.0;
    for (double i = MAX_RANGE_D; i >= MIN_RANGE_D; i--)
    {
        resultd += 1.0 / i;
    }
    cout << "4 : With type double  from 10^7 to 1, the result is: " << resultd << endl;

    // Note: the result in float from 1/1 to 1/10^7 is not precise because ath the end limit
    // the number is so small that it is beyond the precision of the float type, so 0 is added.
    // In the other hand, by begnning with the small values, the precision is kept.
}

