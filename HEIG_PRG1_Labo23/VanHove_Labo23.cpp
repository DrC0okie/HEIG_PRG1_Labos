// File:        VanHove_Labo23.cpp
// Author:      Timothee Van Hove
// Date:        23.11.2021
// Description: Program that multiplies 2 arbitrary large numbers (columnar)
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <vector>

using namespace std;
using long_int = vector<int>;

void displayArray(const vector<int> &v);
long_int &operator+=(long_int &a, const long_int &b);
long_int operator+(long_int a, const long_int &b);
long_int &operator*=(long_int &a, int b);
long_int &operator*=(long_int &a, const long_int &b);
long_int operator*(long_int a, int b);
long_int operator*(long_int &a, const long_int &b);
long_int &operator++(long_int &a);
long_int &report(long_int &a);

int main()
{
    long_int number1;
    long_int number2;
    int num1, num2;
    cout << "Please enter the numbers to multiply : ";
    cin >> num1 >> num2;

    number1.push_back(num1);
    number1 = report(number1);
    number2.push_back(num2);
    number2 = report(number2);

    displayArray(number1);
    displayArray(number2);

    displayArray(number1 * number2);
}

/** @brief Expand multiple digits numbers flat in a vector
 * @param a The vector
 * @return the expended vector*/
long_int &report(long_int &a)
{
    for (size_t j = 0; j < a.size(); j++)
    {
        // If a hasn't space to put the nth, push back
        if (j == a.size() - 1)
        {
            if (a.at(j) >= 10) // Push back only if a[j] contains 2 digit number
                a.push_back(a.at(j) / 10);
        }
        else // Else just put the nth in it
            a.at(j + 1) += a.at(j) / 10;

        a.at(j) %= 10; // Only keep the digit part
    }
    return a;
}

/** @brief += overload for 2 vectors
 * @param a vector a
 * @param b vector b
 * @return a += b*/
long_int &operator+=(long_int &a, const long_int &b)
{
    for (size_t i = a.size(); i < b.size(); i++)
        a.push_back(0); // Increase the size of a if a<b

    for (size_t i = 0; i < b.size(); i++)
        a.at(i) += b.at(i); // Add each term of a and b

    // split all the 2 digits numbers in different indexes
    return report(a);
}

/** @brief + overload for 2 vectors
 * @param a vector a
 * @param b vector b
 * @return a + b */
long_int operator+(long_int a, const long_int &b)
{
    return a += b;
}

/** @brief *= overload for a vector and a integer
 * @param a the vector
 * @param b the integer
 * @return a *= b */
long_int &operator*=(long_int &a, int b)
{
    // Multiply each index by b
    for (size_t i = 0; i < a.size(); ++i)
        a.at(i) *= b;

    // Report the multiple digits numbers
    return report(a);
}

/** @brief * overload for a vector and an integer
 * @param a the vector
 * @param b the integer
 * @return a * b */
long_int operator*(long_int a, int b)
{
    return a *= b;
}

/** @brief multiplication overload for 2 vectors
 * @param a the first vector
 * @param b  the second vector
 * @return the product of multiplication*/
long_int &operator*=(long_int &a, const long_int &b)
{
    long_int tmp;

    for (auto i = b.begin(); i != b.end(); ++i)
    {
        // Add in the tmp variables the product of a*b[i]
        tmp += (a * *i);

        // Insert a 0 in [a] only if i't not the last loop
        if (i != b.end() - 1)
            a.insert(a.begin(), 0);
    }

    // report the values and return the product
    a = report(tmp);
    return a;
}

long_int operator*(long_int &a, const long_int &b)
{
    return a *= b;
}

long_int &operator++(long_int &a)
{
    a.at(0)++;
    return report(a);
}

/** @brief Displays a vector from back() to front()
 * @param v the vector to display*/
void displayArray(const vector<int> &v)
{
    cout << "[";
    for (auto i = v.rbegin(); i != v.rend(); ++i)
    {
        if (*i != v.back())
            cout << "|";
        cout << *i;
    }
    cout << "]" << endl;
}
