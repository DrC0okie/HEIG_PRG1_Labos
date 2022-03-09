// File:        VanHove_Labo29.cpp
// Author:      Timothee Van Hove
// Date:        15.12.2021
// Description: Creation of a class Uint to manipulate arbitrary large numbers
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <random>

const uint32_t GETNUM = 48;

class Uint
{
private:
    std::vector<uint32_t> iValue;
    Uint &carry();
    int comp(const Uint &left, const Uint &right) const;
    Uint &eraseZero();

public:
    void clear();
    Uint();
    Uint(std::string s);
    Uint(uint64_t);

    friend Uint operator*(uint32_t left, const Uint &right);
    friend std::ostream &operator<<(std::ostream &out, const Uint &u);

    Uint operator+(const Uint &right) const;
    Uint operator-(const Uint &right) const;
    Uint operator*(const Uint &right) const;
    Uint operator*(uint32_t right) const;
    Uint operator++(int);
    Uint &operator++();
    Uint &operator+=(const Uint &right);
    Uint &operator-=(const Uint &right);
    Uint &operator*=(const Uint &right);
    Uint &operator*=(uint32_t right);

    bool operator<(const Uint &right) const;
    bool operator<=(const Uint &right) const;
    bool operator>(const Uint &right) const;
    bool operator>=(const Uint &right) const;
    bool operator==(const Uint &right) const;
    bool operator!=(const Uint &right) const;
};

Uint::Uint() : iValue({0}) {}

Uint::Uint(std::string c)
{
    for (auto i = c.rbegin(); i != c.rend(); ++i)
    {
        if (isdigit(*i))
        {
            iValue.push_back(uint32_t(*i) - GETNUM);
        }
        else
        {
            std::cerr << "Construction of Uint failed."
                      << "The string contained non digital characters"
                      << std::endl;
        }
    }

    eraseZero();
}

Uint::Uint(uint64_t c) { *this = std::to_string(c); }

Uint &Uint::carry()
{
    for (size_t j = 0; j < iValue.size(); j++)
    {
        // If a hasn't space to put the nth, push back
        if (j == iValue.size() - 1)
        {
            if (iValue.at(j) >= 10) // Push back only if a[j] contains 2 digit number
                iValue.push_back(iValue.at(j) / 10);
        }
        else // Else just put the nth in it
            iValue.at(j + 1) += iValue.at(j) / 10;

        iValue.at(j) %= 10; // Only keep the digit part
    }
    return *this;
}

int Uint::comp(const Uint &left, const Uint &right) const
{
    if (left.iValue.size() == right.iValue.size())
    {
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

Uint &Uint::eraseZero()
{
    size_t cnt = 0;
    for (auto i = iValue.crbegin(); *i == 0; ++i)
        cnt++;

    // Delete the prefixed "0" of the number
    iValue.resize(iValue.size() - cnt);
    return *this;
}

Uint &Uint::operator+=(const Uint &right)
{
    if (iValue.size() < right.iValue.size())
        iValue.resize(uint32_t(right.iValue.size()), 0);

    for (size_t i = 0; i < right.iValue.size(); i++)
        iValue.at(i) += right.iValue.at(i); // Add each term of a and b

    // split all the digits numbers in different indexes
    return carry();
}

Uint operator*(uint32_t left, const Uint &right)
{
    return right * left;
}

Uint Uint::operator*(uint32_t right) const
{
    Uint temp = *this;
    temp *= right;
    return temp;
}

Uint Uint::operator*(const Uint &right) const
{
    Uint temp = *this;
    temp *= right;
    return temp;
}

Uint Uint::operator++(int)
{ // Postfixed
    Uint temp = *this;
    ++(*this);
    return temp;
}

Uint &Uint::operator++()
{ // Prefixed
    ++iValue.front();
    return carry();
}

Uint &Uint::operator*=(uint32_t right)
{
    // Multiply each index by right
    for (size_t i = 0; i < iValue.size(); ++i)
        iValue.at(i) *= right;

    // Report the multiple digits numbers
    return carry();
}

Uint &Uint::operator*=(const Uint &right)
{
    Uint tmp = 0;

    for (auto i = right.iValue.cbegin(); i != right.iValue.cend(); ++i)
    {
        // Add in the tmp variables the product of a*b[i]
        tmp += (*i * *this);

        // Insert a 0 in [a] only if i't not the last loop
        if (i != right.iValue.cend() - 1)
            iValue.insert(iValue.cbegin(), 0);
    }

    // report the values and return the product
    *this = tmp.carry();
    return *this;
}

Uint Uint::operator+(const Uint &right) const
{
    Uint temp = *this;
    return temp += right;
}

Uint Uint::operator-(const Uint &right) const
{
    Uint temp = *this;
    return temp -= right;
}

std::ostream &operator<<(std::ostream &out, const Uint &u)
{
    for (auto i = u.iValue.crbegin(); i != u.iValue.crend(); ++i)
        out << *i;

    return out;
}

bool Uint::operator<(const Uint &right) const { return comp(*this, right) == -1; }
bool Uint::operator<=(const Uint &right) const { return comp(*this, right) != 1; }
bool Uint::operator>(const Uint &right) const { return comp(*this, right) == 1; }
bool Uint::operator>=(const Uint &right) const { return comp(*this, right) != -1; }
bool Uint::operator==(const Uint &right) const { return comp(*this, right) == 0; }
bool Uint::operator!=(const Uint &right) const { return comp(*this, right) != 0; }

Uint &Uint::operator-=(const Uint &right)
{
    Uint temp = right;
    if (iValue.size() < right.iValue.size())
    {
        std::cerr << "Cannot substract an Uint with a greater Uint" << std::endl;
        return *this;
    }

    temp.iValue.resize(uint32_t(iValue.size()), 0);

    for (size_t i = 0; i < temp.iValue.size(); i++)
    {
        if (iValue.at(i) < temp.iValue.at(i))
        {
            temp.iValue.at(i + 1)++;
            iValue.at(i) += 10;
        }
        iValue.at(i) -= temp.iValue.at(i);
    }
    return eraseZero();
}
using namespace std;

int main()
{

    // //-------------------------Opertaor overload tests--------------------------
    Uint test(11);
    Uint test2 = 2;
    Uint a(2);

    // // Product of 2 Uint
    // a = (test * test2);
    // cout << "11 * 10 : " << a << endl;

    // compond product of an Uint
    a = 1;
    a *= test2;
    cout << "1 *= 2 : " << a << endl;

    // // compond product of an uint32_t
    // a = Uint(201);
    // a *= 2;
    // cout << "201 * 2 : " << a << endl;

    // // product with uint32_t to the right
    // a = Uint(201);
    // a = test2 * 3;
    // cout << "10 * 3 : " << a << endl;

    // // product with uint32_t to the left
    // a = Uint(201);
    // a = 4 * test2;
    // cout << "4 * 10 : " << a << endl;

    // // Compound Addition of an Uint
    // a = Uint(201);
    // a += test2;
    // cout << "201 + 10 : " << a << endl;

    // // Compound sub of an Uint
    // a = Uint(201);
    // a -= test;
    // cout << "201 - 11 : " << a << endl;

    // // Addition of 2 Uint
    // a = Uint(201);
    // a = test + test2;
    // cout << "11 + 10 : " << a << endl;

    // // sub of 2 Uint
    // a = Uint(201);
    // a = test - test2;
    // cout << "11 - 10 : " << a << endl;

    // cout << boolalpha
    //      << "11 == 10? :" << (test == test2) << endl
    //      << "11 != 10? :" << (test != test2) << endl
    //      << "11 < 10? :" << (test < test2) << endl
    //      << "11 <= 10? :" << (test <= test2) << endl
    //      << "11 > 10? :" << (test > test2) << endl
    //      << "11 >= 10? :" << (test >= test2) << endl;

    // cout << boolalpha
    //      << "11 == 11? :" << (test == test) << endl
    //      << "11 != 11? :" << (test != test) << endl
    //      << "11 < 11? :" << (test < test) << endl
    //      << "11 <= 11? :" << (test <= test) << endl
    //      << "11 > 11? :" << (test > test) << endl
    //      << "11 >= 11? :" << (test >= test) << endl;

    // cout << boolalpha
    //      << "10 == 11? :" << (test2 == test) << endl
    //      << "10 != 11? :" << (test2 != test) << endl
    //      << "10 < 11? :" << (test2 < test) << endl
    //      << "10 <= 11? :" << (test2 <= test) << endl
    //      << "10 > 11? :" << (test2 > test) << endl
    //      << "10 >= 11? :" << (test2 >= test) << endl;

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
        cout << "fibonacci(" << i +1 << ") = " << fibo_m2 << endl;
        fibonacci = fibo_m1;
        fibo_m1 = fibo_m2;
        fibo_m2 = fibonacci - fibo_m2; // Vérification -
    }
}