// File:        VanHove_Labo31.cpp
// Author:      Timothee Van Hove
// Date:        15.01.2022
// Description: Generates arbitrary long public and private key pairs
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <limits>
#include <random>
#include <iomanip>
#include <iostream>
#include "Sint.hpp"
#include "Uint.hpp"

using namespace std;

const int WIDTH = 2, WAIT_COUNT = 3;
const char LOAD_CHAR = '.';

/** @brief Generates a prime number with n digit
 * @param digits The number of digits in the prime number to return
 * @return The prime number */
Uint getPrime(uint64_t digits, bool display = false);

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

/** @brief displays 1 char at each call, after 3 calls erase the 3 char
 * @param countInit Used to track the count of calls
 * @param c The char to display
 * @return The increment count or reseted count */
int displayLoadSign(int countInit, char c);

/** @brief Erase n char displayed in cout
 *  @param count The number of char to erase */
void eraseSign(int count);

int main()
{
    int64_t digitNumber;

    // Welcome message
    cout << "--------------------------------------------" << endl
         << "Public / private key pair generation program" << endl
         << "--------------------------------------------" << endl << endl
         << "Enter the number of digits needed for the keys : ";

    // User input verification
    while (!(cin >> digitNumber) || digitNumber < 1)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Wrong input. Please enter an integer > 0" << endl;
    }

    // Clear the cin buffer in case th user added space char
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Generation of the 2 base numbers p & q (they must be different)
    Uint p, q;
    cout << "Generating primes p and q ";
    do
    {
        cout << "(0/2) ";
        p = getPrime(uint64_t(digitNumber), true);
        eraseSign(6);
        cout << "(1/2) ";
        q = getPrime(uint64_t(digitNumber), true);
        eraseSign(6);
        cout << "(2/2) ";
    } while (p == q);

    // Generate the public and private keys
    Uint phi = (p - 1) * (q - 1), publicKeyE, privateKeyD;
    cout << "...done" << endl << "Generating public, private keys ";

    do
    { // The plublic key is generated randomly
        publicKeyE = getPrime(uint64_t(digitNumber), true);

        // Generate the private key with extEuclidean
    } while (extEuclidean(phi, publicKeyE, privateKeyD) != 1);

    // Finally, calculate the key size
    Uint keySizeN = p * q;

    // User output message
    cout << "...done" << endl << endl
         << "Public key e: " << setw(WIDTH + 1) << publicKeyE << endl
         << "Private key d: " << setw(WIDTH) << privateKeyD << endl
         << "Key size n: " << setw(WIDTH + 3) << keySizeN;
}

Uint getPrime(uint64_t digits, bool display)
{
    int count = 0;
    Uint prime;
    do
    {   // Display the loading sign
        if(display)
            count = displayLoadSign(count, LOAD_CHAR);

        //Generate a random number
        prime = getRandomOdd(uint64_t(digits));

        // Test if the number is prime
    } while (!isPrime(prime));

    //Erase the loading signs
    eraseSign(count);
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
    if (temp.back() % 2 == 0)
        temp.at(temp.size() - 1)++;

    return Uint(temp);
}

bool isPrime(Uint &number)
{
    if (number.getSize() == 0)
        number = 0;

    // Elimination of simple results
    if (number < 2)
        return false;
    else if (number == 2)
        return true;
    else
    {
        for (int i = 0; i < 10; ++i)
        {
            Uint random = (getRandomOdd(number.getSize()) % number);

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

int displayLoadSign(int countInit, char c)
{
    int count = countInit;
    if (count == WAIT_COUNT)
    {// After 3 char displayed, erase them
        eraseSign(WAIT_COUNT);
        count = 0;
    }
    else
    {   //Else display a char
        cout << c;
        count++;
    }
    return count;
}

void eraseSign(int count)
{
    for (int i = 0; i < count; i++)
        cout << "\b" << " " << "\b" << flush;
}
