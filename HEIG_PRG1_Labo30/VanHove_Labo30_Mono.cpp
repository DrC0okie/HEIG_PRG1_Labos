// File:        VanHove_Labo30.cpp
// Author:      Timothee Van Hove
// Date:        31.12.2021
// Description: Creation of a class Uint to manipulate arbitrary large numbers
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <random>

const uint32_t GETNUM = 48, BASE = 10;

class Uint
{
private:
    std::vector<uint32_t> iValue;
    Uint &carry();
    int comp(const Uint &left, const Uint &right) const;
    void eraseZero();
    Uint divAndRem(const Uint &dividend, const Uint &divizor, Uint &rem);

public:
    void clear();
    Uint();
    Uint(const std::string &s);
    Uint(uint64_t);

    bool isEven() const;

    uint32_t getSize() const;

    friend Uint operator*(uint32_t left, const Uint &right);
    friend std::ostream &operator<<(std::ostream &out, const Uint &u);

    Uint operator+(const Uint &right) const;
    Uint operator-(const Uint &right) const;
    Uint operator*(const Uint &right) const;
    Uint operator*(uint32_t right) const;
    Uint operator/(const Uint &right) const;
    Uint operator/(uint32_t right) const;
    Uint operator%(const Uint &right) const;
    Uint operator%(uint32_t right) const;
    Uint operator++(int);
    Uint &operator++();
    Uint operator--(int);
    Uint &operator--();
    Uint &operator+=(const Uint &right);
    Uint &operator-=(const Uint &right);
    Uint &operator*=(const Uint &right);
    Uint &operator*=(uint32_t right);
    Uint &operator/=(const Uint &right);
    Uint &operator/=(uint32_t right);
    Uint &operator%=(const Uint &right);
    Uint &operator%=(uint32_t right);
    bool operator<(const Uint &right) const;
    bool operator<=(const Uint &right) const;
    bool operator>(const Uint &right) const;
    bool operator>=(const Uint &right) const;
    bool operator==(const Uint &right) const;
    bool operator!=(const Uint &right) const;
};

Uint::Uint() {}

Uint::Uint(const std::string &s)
{
    for (auto i = s.crbegin(); i != s.crend(); ++i)
    {
        if (isdigit(*i))
            iValue.push_back(uint32_t(*i) - GETNUM);

        else
            throw std::invalid_argument(
                "Construction error : the string is not a valid number");
    }

    eraseZero();
}

bool Uint::isEven() const { return (iValue.front() % 2) == 0; }

Uint::Uint(uint64_t c) { *this = std::to_string(c); }

Uint &Uint::carry()
{
    for (size_t i = 0; i < iValue.size(); ++i)
    {
        // If this->iValue hasn't space to put the nth, push back
        if (i == iValue.size() - 1)
        { // Push back only if this->iValue[i] contains 2 digit number
            if (iValue.at(i) >= BASE)
                iValue.push_back(iValue.at(i) / BASE);
        }
        else // Else just put the nth in this->iValue[i]
            iValue.at(i + 1) += iValue.at(i) / BASE;

        // Only keep the digit part
        iValue.at(i) %= BASE;
    }

    return *this;
}

int Uint::comp(const Uint &left, const Uint &right) const
{
    // First, compare the size of internal values
    if (left.iValue.size() == right.iValue.size())
    {
        // Then, compare each element's values
        for (auto l = left.iValue.crbegin(), r = right.iValue.crbegin();
             l != left.iValue.crend(); ++l, ++r)
        {
            if (*l < *r)
                return -1;
            else if (*l > *r)
                return 1;
        }
        return 0;
    }
    else if (left.iValue.size() < right.iValue.size())
        return -1;

    return 1;
}

void Uint::eraseZero()
{
    while (iValue.size() > 1 && *(iValue.end() - 1) == 0)
        iValue.erase((iValue.end() - 1));
}

Uint Uint::divAndRem(const Uint &dividend, const Uint &divizor, Uint &rem)
{
    Uint pTemp(1), divizorTemp = divizor, quotient(0);

    while (divizorTemp <= dividend)
    {
        pTemp *= 2;
        divizorTemp *= 2;
    }

    rem = dividend;

    while (rem >= divizor)
    {
        divizorTemp /= 2;
        pTemp /= 2;

        if (rem >= divizorTemp)
        {
            quotient += pTemp;
            rem -= divizorTemp;
        }
    }
    return quotient;
}

uint32_t Uint::getSize() const { return uint32_t(iValue.size()); }

Uint operator*(uint32_t left, const Uint &right) { return right * left; }

std::ostream &operator<<(std::ostream &out, const Uint &u)
{
    for (auto i = u.iValue.crbegin(); i != u.iValue.crend(); ++i)
        out << *i;

    return out;
}

Uint Uint::operator+(const Uint &right) const
{
    Uint temp = *this;
    temp += right;
    return temp;
}

Uint Uint::operator-(const Uint &right) const
{
    Uint temp = *this;
    temp -= right;
    return temp;
}

Uint Uint::operator*(const Uint &right) const
{
    Uint temp = *this;
    temp *= right;
    return temp;
}

Uint Uint::operator*(uint32_t right) const
{
    Uint temp = *this;
    temp *= right;
    return temp;
}

Uint Uint::operator/(const Uint &right) const
{
    Uint temp = *this;
    temp /= right;
    return temp;
}

Uint Uint::operator/(uint32_t right) const
{
    Uint temp = *this;
    temp /= right;
    return temp;
}

Uint Uint::operator%(const Uint &right) const
{
    Uint temp = *this;
    temp %= right;
    return temp;
}

Uint Uint::operator%(uint32_t right) const
{
    Uint temp = *this;
    temp %= right;
    return temp;
}

Uint Uint::operator++(int)
{
    Uint tmp = *this;
    ++(*this);

    // Return the previous value
    return tmp;
}

Uint &Uint::operator++()
{
    ++iValue.front();
    if (iValue.front() > 9)
        carry();
    return *this;
}

Uint Uint::operator--(int)
{
    Uint tmp = *this;
    --(*this);

    //return the previous value
    return tmp;
}

Uint &Uint::operator--()
{ 
    //Simple case : increase the front
    if (iValue.front() > 1)
        --iValue.front();
    else
    {//else use the costly operation -=
        *this -= 1;
        return carry();
    }
    return *this;
}

Uint &Uint::operator+=(const Uint &right)
{
    // Resize this->iValue in case < right.iValue
    if (iValue.size() < right.iValue.size())
        iValue.resize(uint32_t(right.iValue.size()), 0);

    // sum each element of internal values
    for (size_t i = 0; i < right.iValue.size(); ++i)
        iValue.at(i) += right.iValue.at(i);

    // carry the multiple-digits numbers in different indexes
    return carry();
}

Uint &Uint::operator-=(const Uint &right)
{
    Uint temp = right;

    // Verification taht the right member is strictly lower
    if (*this < right)
        throw std::invalid_argument("Cannot substract an Uint with a greater Uint");

    // Resize the temp variable in case this->iValue is larger
    if (iValue.size() > temp.iValue.size())
        temp.iValue.resize(uint32_t(iValue.size()), 0);

    // Columnar substration
    for (size_t i = 0; i < iValue.size(); ++i)
    {
        if (iValue.at(i) < temp.iValue.at(i))
        { // Increase the next column of temp
            temp.iValue.at(i + 1)++;

            // Add 10 to this to get a positive value
            iValue.at(i) += BASE;
        }

        // Substract the column
        iValue.at(i) -= temp.iValue.at(i);
    }

    // Erase possible prefixed zeros
    eraseZero();

    return *this;
}

Uint &Uint::operator*=(const Uint &right)
{
    // Use a temporary value to work on it
    Uint temp = 0;

    // Iterates on each members of the right value
    for (size_t i = 0; i != right.iValue.size(); i++)
    {
        // Adds in temp the result of the multiplication of right and left
        temp += right.iValue.at(i) * *this;

        // If the size of the right value is too small, insert
        if (i != right.iValue.size() - 1)
            iValue.insert(iValue.cbegin(), 0);
    }

    *this = temp;

    return *this;
}

Uint &Uint::operator*=(uint32_t right)
{
    // Multiply each index by right
    for (uint32_t i = 0; i < iValue.size(); ++i)
        iValue.at(i) *= right;

    // Report the multiple digits numbers
    return carry();
}

Uint &Uint::operator/=(const Uint &right)
{
    // Verification that the divizor is not 0
    if (right == Uint(0))
        throw std::runtime_error("Division by 0");

    Uint rem;
    *this = divAndRem(*this, right, rem);
    return *this;
}

Uint &Uint::operator/=(uint32_t right)
{
    // Verification that the divizor is not 0
    if (right == 0)
        throw std::runtime_error("Division by 0");

    for (size_t i = iValue.size() - 1; i > 0; i--)
    {
        iValue.at(i - 1) += (iValue.at(i) % right) * BASE;
        iValue.at(i) /= right;
    }

    iValue.at(0) /= right;
    eraseZero();

    return *this;
}

Uint &Uint::operator%=(const Uint &right)
{
    divAndRem(*this, right, *this);
    return *this;
}

Uint &Uint::operator%=(uint32_t right)
{
    //Quick and dirty way to get the mod with a uint32_t without divAndRem()
    return *this -= (*this / right) * right;
}

bool Uint::operator<(const Uint &right) const { return comp(*this, right) == -1; }

bool Uint::operator<=(const Uint &right) const { return comp(*this, right) != 1; }

bool Uint::operator>(const Uint &right) const { return comp(*this, right) == 1; }

bool Uint::operator>=(const Uint &right) const { return comp(*this, right) != -1; }

bool Uint::operator==(const Uint &right) const { return comp(*this, right) == 0; }

bool Uint::operator!=(const Uint &right) const { return comp(*this, right) != 0; }

using namespace std;

Uint modularExp(Uint base, Uint exp, const Uint &mod);
bool primalityTest(Uint &primeTest);
Uint getRandom(uint32_t digits);

Uint getRandom(uint32_t digits)
{
    static random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distr(0, 9);

    string temp = to_string(distr(generator));

    while (temp == "0")
        temp = to_string(distr(generator));

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