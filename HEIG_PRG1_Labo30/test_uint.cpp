#include "Uint.hpp"
#include <iostream>
#include <random>

using namespace std;

/** @brief Modular exponentiation
 * @param base The base
 * @param exp  The exponent
 * @param mod The modulus
 * @return The result of modular exponentiation */
Uint modularExp(Uint base, Uint exp, const Uint &mod);

/** @brief Checks if the given number is prime
 * @details based on Fermat primality test and Solovay–Strassen primality test
    Run 10 times the primality tests with random numbers to decrease the chances
    of getting an Euler–Jacobi pseudoprime
 * @param number The number to test
 * @return true if primeTest is probably prime, false if not*/
bool primalityTest(Uint &number);

/** @brief Get a random number of n digits
 * @param digits The number of digits of the number to be returned
 * @return The random number with n digits */
Uint getRandom(uint32_t digits);

int main()
{
    string nombre;
    cout << "Introduire un nombre entier: ";
    cin >> nombre;
    size_t nb = stoul(nombre);
    Uint n;           // Vérification constructeur vide
    n = Uint(nombre); // Vérification constructeur par string

    cout << "Nombre lu " << n << endl; // Vérification opérateur <<

    Uint factorielle(1); // Vérification constructeur par entier (explicite)
    cout << factorielle << endl;
    for (size_t i = 2; i <= nb; ++i)
    {
        factorielle *= uint32_t(i); // Vérification *= size_t
        cout << i << "! = " << factorielle << endl;
    }

    factorielle = 1;              // Vérification constructeur par entier implicite
    for (Uint i = 2; i <= n; ++i) // Vérification <= et ++
    {
        factorielle *= i; // Vérification *= Uint
        cout << i << "! = " << factorielle << endl;
    }

    Uint fibo_m2(0), fibo_m1(1), fibonacci;
    for (Uint i = 2; i <= n; ++i)
    {
        fibonacci = fibo_m2 + fibo_m1; // Vérification Uint + Uint
        cout << "fibonacci(" << i << ") = " << fibonacci << endl;
        fibo_m2 = fibo_m1;
        fibo_m1 = fibonacci;
    }

    // Vérification -, > et -=
    for (Uint i = n - 2; i > 0; i -= 1)
    {
        cout << "fibonacci(" << i + 1 << ") = " << fibo_m2 << endl;
        fibonacci = fibo_m1;
        fibo_m1 = fibo_m2;
        fibo_m2 = fibonacci - fibo_m2; // Vérification -
    }

    for (Uint i = n; i > 0; i -= 1)
    {
        cout << i << "! = " << factorielle << endl;
        factorielle = factorielle / i; // Vérification Uint/Uint
    }

    Uint p;
    do
    {
        p = getRandom((uint32_t)nb); // Vérification gen_random
        cout << p << endl;
    } while (!primalityTest(p)); // Vérification exponentiation modulaire, prime
}

Uint getRandom(uint32_t digits)
{
    // Creation of the generator and the distribution
    static random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distr(0, 9);

    // Get the first random digit and cast it to string
    string temp = to_string(distr(generator));

    // While the first digit is 0, re-generate the number
    while (temp == "0")
        temp = to_string(distr(generator));

    // Get all other random digits
    for (size_t i = 0; i < digits - 1; ++i)
        temp += to_string(distr(generator));

    return Uint(temp);
}

bool primalityTest(Uint &primeTest)
{
    if (primeTest.getSize() == 0)
        primeTest = 0;

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
    {
        for (int i = 0; i < 10; ++i)
        {
            // Get a random number
            Uint random = (getRandom(primeTest.getSize()) % primeTest) + 1;
            Uint exp = primeTest - 1;

            // Fermat primality test
            if (modularExp(random, exp, primeTest) != 1)
                return false;

            // Solovay–Strassen primality test
            Uint modExp = 1;
            while (exp.isEven() && modExp == 1)
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

Uint modularExp(Uint base, Uint exp, const Uint &mod)
{
    Uint result = 1;

    while (exp > 0)
    {
        if (exp.isEven())
        { // Exponent is even
            base = base * base % mod;
            exp /= 2;
        }
        else
        { // Exponent is odd
            result = result * base % mod;
            --exp;
        }
    }
    return result;
}