// File:        VanHove_Labo13_3.32.cpp
// Author:      Timothee Van Hove
// Date:        18.10.2021
// Description: Program that approximate the number pi with the Monte-Carlo method
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <random>
#include <cmath>
#include <functional>

using namespace std;

int main()
{
    unsigned iterations = 0;

    // User message & input
    cout << "Please enter a number of iteration for the approximation: " << endl;
    cin >> iterations;

    // User input value control
    while (iterations > numeric_limits<unsigned int>::max() || iterations < 1)
    {
        cin >> iterations;
        cout << "Number too large. Please enter a number between 1 and "
             << numeric_limits<unsigned int>::max();
    }

    // Obtain a random number from hardware
    random_device rd;

    // Seed the generator
    mt19937 gen(rd());

    // Define the range
    uniform_real_distribution<double> distr(0, 1);

    double approxPi = 0.0, circleCount = 0.0;

    // Sequence to approximate pi value.
    for (unsigned rectCount = 1; rectCount < iterations; rectCount++)
    {
        // If the hypotenuse of generated point is >= 1, the point is outside of the circle
        if (hypot(distr(gen), distr(gen)) <= 1.0)
            circleCount++;

        // Ratio of points inside the circle vs inside the rectangle * 4
        approxPi = 4 * circleCount / rectCount;
    }

    // User message with the results
    cout << "After " << iterations << " iterations, pi equals: " << approxPi;
    return 1;
}