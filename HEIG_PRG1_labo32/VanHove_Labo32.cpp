// File:        VanHove_Labo32.cpp
// Author:      Timothee Van Hove
// Date:        17.01.2022
// Description: Get the duration of prime number generation
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <limits>
#include <random>
#include <iomanip>
#include <iostream>
#include "Sint.hpp"
#include "Uint.hpp"
#include <chrono>

using namespace std;
using namespace chrono;

const uint64_t ITERATIONS = 20;

/** @brief Generates a prime number with n digit
 * @param digits The number of digits in the prime number to return
 * @return The prime number */
Uint getPrime(uint64_t digits);

/** @brief Generates a random odd number with n digits
 * @param digits The number of digits in the random number to return
 * @return The random number */
Uint getRandomOdd(uint64_t digits);

/** @brief Primality test based on Fermat primality test
 * and Solovay–Strassen primality test
 * @param number The number to test
 * @return true if primeTest is probably prime, false if not*/
bool isPrime(Uint &number);

/** @brief Extended Euclidean algorithm that computes the GCD and
 * the multiplicative inverse of num2 % num1 if they are coprime
 * @param num1 The first number
 * @param num2 The second number
 * @param inverse Inverse of num2 % num1 if they are coprime (used as output)
 * @return The gcd of num1 and num2 */
Uint extEuclidean(const Uint &num1, const Uint &num2, Uint &inverse);

int main()
{
    int64_t n = ITERATIONS;

    // Welcome message
    cout << "---------------------------------------" << endl
         << "Large prime generation duration counter" << endl
         << "---------------------------------------" << endl;

    for (size_t i = 0; i < 10; i++)
    {

        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        for (size_t j = 0; j < 10; j++)
        {
            // Generation of the prime
            Uint p = getPrime(uint64_t(n));
        }

        duration<double> time_span =
            duration_cast<duration<double>>(high_resolution_clock::now() - t1);
        cout << "Prime " << i + 1 << "(n = " << n << ") "
             << " : " << time_span.count() << endl;

        // Multiply by 1.1
        n += n / 10;
    }
}

Uint getPrime(uint64_t digits)
{
    Uint prime;
    do
    { // Generate a random number
        prime = getRandomOdd(uint64_t(digits));

        // Test if the number is prime
    } while (!isPrime(prime));

    return prime;
}

Uint getRandomOdd(uint64_t digits)
{
    static random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int32_t> distr(0, 9);

    // transform the random number to string
    string temp = to_string(distr(generator));

    // Discard the prefixed zero
    while (temp == "0")
        temp = to_string(distr(generator));

    // Concat the following random numbers to the string
    for (size_t i = 0; i < digits - 1; ++i)
        temp += to_string(distr(generator));

    // If the last digit is % 2, increment to get an odd number
    // if (temp.back() % 2 == 0)
    //     temp.at(temp.size() - 1)++;

    return Uint(temp);
}

bool isPrime(Uint &number)
{
    for (int i = 0; i < 10; ++i)
    {
        Uint random = getRandomOdd(number.getSize());

        // Use of ++ and -- as it is way faster thant + 1, and -1 for Uint
        ++random;
        Uint exp = number;
        --exp;

        // Use a temporary value to avoid a subtraction later
        Uint oldExp = exp;

        // Fermat primality test
        if (mod_pow(random, exp, number) != 1)
            return false;

        // Solovay–Strassen primality test
        Uint modExp = 1;
        while (exp.isEven() && modExp == 1)
        {
            exp /= 2;
            modExp = mod_pow(random, exp, number);
            if (modExp != 1 && modExp != oldExp)
                return false;
        }
    }

    return true;
}

Uint extEuclidean(const Uint &num1, const Uint &num2, Uint &inverse)
{
    Sint gcd = num1, new_gcd = num2, d = 0, new_d = 1;

    while (new_gcd != 0)
    {
        // Get the quotient from old gcd / new gcd
        Sint quotient = gcd / new_gcd;

        // Save temp values to use it later
        Sint temp_gcd = gcd;
        Sint temp_d = d;

        // Update the 2 values
        gcd = new_gcd;
        d = new_d;

        // Get the gcd and the temp. muliplicative inverse
        new_gcd = temp_gcd - quotient * new_gcd;
        new_d = temp_d - quotient * new_d;
    }
    // Add a to the temp muliplicative inverse if it's < 0
    if (d < 0)
        d += num1;

    // Return the inverse by reference
    inverse = d.abs();

    return gcd.abs();
}