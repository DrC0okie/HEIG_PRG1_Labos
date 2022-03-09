// File:        VanHove_Labo20.cpp
// Author:      Timothee Van Hove
// Date:        15.11.2021
// Description:
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <cmath>

using namespace std;

int getNumberOfDigits(int number);
void displayFromEnd(const int array[], size_t size, size_t capacity);
void getFactorialFromArray(int array[], size_t size, int number);
void fillArray(int array[], size_t &size, int number);

int main()
{

    cout << "Please enter a number > 0 : ";
    int number;
    while (!(cin >> number) && number > 0)
    {
        cout << "Please enter a number > 0. Retry : ";
    }

    int factorialArray[500];
    factorialArray[499] = 1;
    size_t size = sizeof(factorialArray) / sizeof(int);

    fillArray(factorialArray, size, number);

    displayFromEnd(factorialArray, size, 500);
}

void getFactorialFromArray(int array[], size_t size, int number)
{
    for (size_t i = 0; i < number; i++)
    {

        for (int j = size - 1; j > 0; j--)
        {
            number = array[j] * i;
            if(getNumberOfDigits(number) > 1)
                fillArray(array, size, number)
        }
    }
}

int getNumberOfDigits(int number)
{
    int cnt = 0;
    while (number != 0)
    {
        number /= 10;
        cnt++;
    }
    return cnt;
}

void fillArray(int array[], size_t &size, int number)
{
    int quantity = getNumberOfDigits(number);
    int test = 0, test0 = 0;
    for (int i = quantity; i > 0; i--)
    {
        test0 = int(pow(10, i - 1));
        test = number / test0 % 10;
        array[(size + 1) - i] = test;
    }

    size = quantity;
}

/**  @brief Display the content of an array
 * @param array The array
 * @param size The size of the array*/
void displayFromEnd(const int array[], size_t size, size_t capacity)
{
    for (size_t i = size; i > 0; i--)
        cout << "[" << array[(capacity + 1) - i] << "] ";

    cout << endl;
}