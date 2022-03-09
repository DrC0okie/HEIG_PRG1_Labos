// File:        VanHove_Labo19_5.11.cpp
// Author:      Timothee Van Hove
// Date:        10.11.2021
// Description: Exercise 5.11 "Somme alternée"
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>

using namespace std;

void display(const int array[], size_t size);
int alternatingSum(const int array[], size_t size);

int main()
{
    //Declaration of the test array
    int array1[4] = {1, 2, 3, 4};
    int array2[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    // Get the size of the array
    size_t size1 = sizeof(array1) / sizeof(int);
    size_t size2 = sizeof(array2) / sizeof(int);

    cout << "Exercise 5.11 : Alternating sum" << endl
         << "Test Arrays:" << endl;
    display(array1, size1);
    display(array2, size2);

    int result1 = alternatingSum(array1, size1);
    int result2 = alternatingSum(array2, size2);

    cout << "Result of the alterating sum :" << endl
         << "Array 1 : " <<  result1 << endl
         << "Array 2 : " <<  result2;
}

/** @brief Calculates the alternating sum of an array ([i]+[-j]+[k]+[-l]...)
 * @param array The array
 * @param size The size of the array*/
int alternatingSum(const int array[], size_t size)
{
    int sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (i % 2 == 0)
            sum += array[i];
        else
            sum -= array[i];
    }
    return sum;
}

/**  @brief Display the content of an array
 * @param array The array
 * @param size The size of the array*/
void display(const int array[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (array[i] != 0)
            cout << "[" << array[i] << "] ";
        else
            cout << "[]";
    }
    cout << endl;
}