// File:        VanHove_Labo16.cpp
// Author:      Timothee Van Hove
// Date:        04.11.2021
// Description: Implementation of the RSA algorithm to encrypt and decrypt a message
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

/**
 * Corrections
 * ---------------------------------------------------------------------------
 * Commentaires : Vos commentaires sont très bons. Mettez plutôt les commentaires de fonctions au-dessus les signatures de celle-ci.
 * Nom des variables et fonctions : Faites attention vous n'avez pas les mêmes noms de variables entre les signatures de vos fonctions et vos fonctions.
 * Lorsque vous codez votre programme, faites soit le programme en camelCase ou soit en snake_case, évitez un mélange des deux.
 * Utilisation des types : Vous avez une bonne utilisation des types avec la fonction d'exponentiation, vous utilisez des long long pour la base.
 * Mais, dans le reste du programme, vous utilisez des int. Il n'était pas conseillé d'utiliser ce type, car dans certains systèmes les entiers seront sur 16 bits et non 32 bits.
 * Si cela arrive, vous ne pourriez plus respecter une des directives de la donnée. Celle indiquant que des entiers à 9 chiffres peuvent être entrés.
 * Vous auriez dû utiliser un type fixe également plus particulièrement un int32_t.
 * Utilisation des fonctions : Lorsque vous faites des entrées utilisateurs évitez de faire des boucles infinies préférez mettre les vérifications des if dans la condition du while.
 * Utilisez plutôt des return; plutôt que des break.
 * Minimiser les passages par référence si vous le pouvez.
 * Typiquement, pour les entrées utilisateurs vous auriez pu faire une fonction qui vérifie les entrées pour un nombre premier et le retourne si les vérifications sont passées.
 * Forme du code : Votre code respecte la forme désirée (indentation, espaces, etc...)
 * Entrées utilisateurs : Lacune:
 * Enter 2 prime numbers, that once multipled are in range [0 - 2147483647] separated by spaces (p q): 0 3001
 * Exception en point flottant (core dumped)

 * Fonctionnement des fonctions : La fonction isInRange ne fonctionne pas
 * si son second paramètre vaut MAX_INT32, ou que int est sur moins de 32 bits.
 * Fonctionnement du chiffrement et déchiffrement : Le déchiffrement et chiffrement est effectué correctement
 * Compilation : warning: conversion from ‘long long int’ to ‘int’ may change value [-Wconversion]
 * --------------------------------------------------------------------------
 * Note Finale : 4.9
 */

#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

const int MIN = 0, MAX_INT32 = numeric_limits<int32_t>::max(),
          VERIF_ITERATIONS = 10, MSG_WIDTH = 14, TEST_WIDTH = 2;

int getRandomInt(int min, int max);
int extEuclidean(int a, int b, int &inverse);
int modularExp(long long base, int exp, int mod);
void checkPrimesInput(int &num1, int &num2);
void checkPublicValue(int &num1, int num2, int &inverse);
bool isPrime(int number);
bool streamError(int &num1);
bool primalityTest(int value);
bool inputVerification(int &prime);
bool isInRange(int number, int min, int max);
bool isCoprime(int num1, int num2, int &inverse_e);
bool verification(int publicValue, int privateValue, int keySize);

int main()
{
    int prime_p = 0, prime_q = 0;

    // User message for the input of p and q
    cout << "Enter 2 prime numbers, that once multipled are in range ["
         << MIN << " - " << MAX_INT32 << "] separated by spaces (p q): ";

    // User input stream, range, equality and primality verification for p and q
    checkPrimesInput(prime_p, prime_q);

    int phi = (prime_p - 1) * (prime_q - 1), publicValue_e, inverse_e;

    // User message for the input of the public value
    cout << "Enter a coprime number with " << phi
         << ", but strictly lower (e): ";

    // User input stream, range, and relative primality verification for e
    checkPublicValue(publicValue_e, phi, inverse_e);

    // Calculate the value of the private key for Alice
    int privateValue_d = inverse_e % phi, keySize_n = prime_p * prime_q;

    // Display the public & private key values
    cout << endl
         << "Alice's public key: e = " << publicValue_e << " n = "
         << keySize_n << endl
         << "Alice's private key: d = " << privateValue_d << " n = "
         << keySize_n << endl;

    // Automated verification
    if (verification(publicValue_e, privateValue_d, keySize_n))
        cout << endl
             << "Each message has been encrypted & decrypted correctly";
    else
        cout << endl << "Test failed";
}

/** @brief Verification that for 10 random messages, the algorithm can encrypt,
 *  decrypt and get the original message
 * @param publicValue The public value in the public key of Alice
 * @param privateValue The private value in the private key of Alice
 * @param keySize The key size (same in the public and private key)
 * @return true if the verification is successful, false if not*/
bool verification(int publicValue, int privateValue, int keySize)
{
    cout << endl << "Verifying with " << VERIF_ITERATIONS
         << " random messages, distributed on [1 - "
         << keySize - 1 << "]" << endl;

    for (int i = 1; i <= VERIF_ITERATIONS; i++)
    {
        // Get a unique message
        int originalMessage = getRandomInt(1, keySize - 1);

        // Message encryption
        int encryptedMsg = modularExp(originalMessage, publicValue, keySize);

        // Message decryption
        int decryptedMsg = modularExp(encryptedMsg, privateValue, keySize);

        // Outputs the result of the current test
        cout << "Test " << setw(TEST_WIDTH) << left << i
             << " Message: " << setw(MSG_WIDTH) << left << originalMessage
             << " Encrypted message: " << setw(MSG_WIDTH) << left << encryptedMsg
             << " Decrypted message: " << decryptedMsg << endl;

        // Automatic verification
        if (decryptedMsg != originalMessage)
        {
            cout << "For message " << originalMessage << ", decryption failed";
            return false;
        }
    }
    return true;
}

/** @brief Checks if the 2 inputs are integers, in range, not equal and prime
 * @param in1 The 1st user input (p). Used as output it the check succeeds
 * @param in2 The 2nd user input (q). Used as output it the check succeeds*/
void checkPrimesInput(int &in1, int &in2)
{
    while (true)
    {
        // stream input error verification
        if (streamError(in1) || streamError(in2))
            continue;

        // range verification
        if (!isInRange(in1, MIN, MAX_INT32) || !isInRange(in2, MIN, MAX_INT32 / in1))
            continue;

        // Equality verification
        if (in1 == in2)
        {
            cout << "The numbers must be different. Retry (p, q): ";
            continue;
        }

        // primality verification
        if (!isPrime(in1) || !isPrime(in2))
            continue;
        else
            break;
    }
}

/** @brief Checks if the input is an integer, in range, and coprime with phi
 * @param input The user input (e). Used as output if the check succeeds
 * @param phi The value used for the coprime verification (p-1 * p-1)
 * @param inverse The inverse of e used as output*/
void checkPublicValue(int &input, int phi, int &inverse)
{
    while (true)
    {
        // stream input error verification
        if (streamError(input))
            continue;

        // range verification
        if (!isInRange(input, MIN + 1, phi - 1))
            continue;

        // Relative primality verification & ouput inverse
        if (!isCoprime(phi, input, inverse))
            continue;
        else
            break;
    }
}

/** @brief Function that checks if the input stream is in error
 * @param input The user input (used as output)
 * @return true if an error is detected, false if not*/
bool streamError(int &input)
{
    if (!(cin >> input))
    {
        cout << "Input stream error! Please retry with the good input type : ";
        cin.clear();
        cin.ignore(MAX_INT32, '\n');
        return true;
    }
    return false;
}

/** @brief Checks if the number is prime
 * @param number The number to test the primality
 * @return true if the number is probably prime, false if not*/
bool isPrime(int number)
{
    if (!primalityTest(number))
    {
        cout << number << " is not prime, please retry : ";
        return false;
    }
    return true;
}

/** @brief Checks if the 2 numbers are coprime using the extEuclidean algorithm
 * @details num1 must always be > num2
 * @param num1 The first number to test
 * @param num2  The second number to test
 * @param inverse Inverse of num2 % num1 (used as output)
 * @return true if num1 and num2 are coprime, false if not*/
bool isCoprime(int num1, int num2, int &inverse)
{
    if (extEuclidean(num1, num2, inverse) != 1)
    {
        cout << num1 << " is not coprime with " << num2 << ", please retry: ";
        return false;
    }
    return true;
}

/** @brief Checks if the number is whithin the given range
 * @param number value to test
 * @param min lowest value of the range
 * @param max highest value of the range
 * @return true if the number is within the range, false if not*/
bool isInRange(int number, int min, int max)
{
    if (number < min || number > max)
    {
        cout << "The number " << number << " must be in range [" << min
             << " - " << max << "]. Please retry: ";
        return false;
    }
    return true;
}

/** @brief Primality test based on Fermat primality test
 * and Solovay–Strassen primality test
 * @details Run 10 times the tests with random numbers to decrease the chances
 * of getting an Euler–Jacobi pseudoprime
 * @param primeTest The number to test
 * @return true if primeTest is probably prime, false if not*/
bool primalityTest(int primeTest)
{
    // Elimination of simple results
    if (primeTest < 2)
    { // 0, 1 are not prime
        return false;
    }
    else if (primeTest == 2)
    { // 2 is prime
        return true;
    }
    else
    { // Run 10 iterations
        for (int i = 0; i < 10; i++)
        {
            // Get a random number
            int random = getRandomInt(2, primeTest - 1), exp = primeTest - 1;

            // Primality test with Fermat primality test
            if (modularExp(random, exp, primeTest) != 1)
                return false;

            // Solovay–Strassen primality test
            int modExp = 1;
            while (exp % 2 == 0 && modExp == 1)
            {
                exp /= 2;
                modExp = modularExp(random, exp, primeTest);
                if (modExp != 1 && modExp != primeTest - 1)
                    return false;
            }
        }
    }
    return true;
}

/** @brief Extended Euclidean algorithm that computes the GCD and
 * the multiplicative inverse of num2 % num1 if they are coprime
 * @param num1 The first number
 * @param num2 The second number
 * @param inverse Inverse of num2 % num1 if they are coprime (used as output)
 * @return The gcd of num1 and num2 */
int extEuclidean(int num1, int num2, int &inverse)
{
    int gcd = num1, new_gcd = num2, d = 0, new_d = 1;

    while (new_gcd != 0)
    {
        // Get the quotient from old gcd / new gcd
        int quotient = gcd / new_gcd;

        // Save temp values to use it later
        int temp_gcd = gcd;
        int temp_d = d;

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

    inverse = d;
    return gcd;
}

/** @brief Get a random Int number in specified range
 * @param min the lower boud of the range
 * @param max the upper boud of the range
 * @return the random integer*/
int getRandomInt(int min, int max)
{
    static random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distr(min, max);
    return distr(generator);
}

/** @brief Modular exponentiation
 * @details The base is a long long type to avoid overflows
 * @param base The base
 * @param exp  The exponent
 * @param mod The modulus
 * @return The result of modular exponentiation */
int modularExp(long long base, int exp, int mod)
{
    int result = 1;

    while (exp > 0)
    {
        if (!(exp % 2))
        { // Exponent is even
            base = base * base % mod;
            exp /= 2;
        }
        else
        { // Exponent is odd
            result = result * base % mod;
            exp--;
        }
    }
    return result;
}
