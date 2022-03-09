// File:        VanHove_Labo18.cpp
// Author:      Timothee Van Hove
// Date:        10.11.2021
// Description: Calculates the sinus with the Maclaurin series and benchmarks it vs sin from cmath
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

typedef chrono::high_resolution_clock Clock;
typedef chrono::nanoseconds nanoseconds;

const double PI = atan(1) * 4.0;

double macLaurinSinus(double angle);
double restrictToSinDomain(double angle);

int main()
{
    double angle;

    // User message
    cout << "Please enter an angle in radians : ";

    // User input with verification
    while (!(cin >> angle))
        cout << "Please enter a integer value "<< "Please retry : ";

    // Convert the angle in sin domain
    angle = restrictToSinDomain(angle);

    // Clocks declaration
    Clock::time_point t0, t1, t2, t3;

    //Value & user output of sin with MacLaurin function
    t0 = Clock::now();
    double sinus = macLaurinSinus(angle);
    t1 = Clock::now();
    nanoseconds timeMacLaurin = chrono::duration_cast<nanoseconds>(t1 - t0);
    cout << "Sinus of " << angle << " with Maclaurin series: " << sinus << endl;

    //Value & user output of sin with cmath function
    t2 = Clock::now();
    sinus = sin(angle);
    t3 = Clock::now();
    nanoseconds timeCmathSin = chrono::duration_cast<nanoseconds>(t3 - t2);
    cout << "Sinus of " << angle << " with cmath sin: " << sinus << endl;

    // Execution time comparison
    cout << "MacLaurin execution time[ns] : " << timeMacLaurin.count() << endl
         << "cmath execution time[ns] : " << timeCmathSin.count() << endl;
}

/** @brief Calculates the sinus of the given parameter with MacLaurin's series
 * @details Iterates the series until no significance to the value of the sinus
 * @param angle The angle in radians
 * @return The sinus value of the angle */
double macLaurinSinus(double angle)
{
    //Factorization of the angle
    double z = -(angle * angle), sinus = 1;

    // Get the sinus using 10 iterations for the factorial (enough precision) 
    for (int i = 10; i > 0; i--)
    {
        sinus *= z / ((2 * i + 1) * 2 * i);
        sinus += 1;
    }
    return sinus * angle;
}

/** @brief Converts the angle in domain -PI/2 -  PI/2
 * @param angle The angle to convert in the sin domain
 * @return the converted value */
double restrictToSinDomain(double angle)
{
    // Reduce to range -360 to 360
    angle = fmod(angle, 2 * PI);

    // Reduce to range -180 to 180
    if (angle >= PI)
    {
        angle -= PI;
        angle = -angle;
    }
    else if (angle <= -PI)
    {
        angle += PI;
        angle = -angle;
    }

    // Reduce to range -90 to 90
    if (angle >= PI / 2)
        angle = PI - angle;

    else if (angle <= -PI / 2)
        angle = -PI - angle;
    return angle;
}