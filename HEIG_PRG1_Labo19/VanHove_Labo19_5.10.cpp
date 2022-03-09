// File:        VanHove_Labo19_5.10.cpp
// Author:      Timothee Van Hove
// Date:        10.11.2021
// Description: Exercise 5.10 "Eléments strictement croissants ou pas ?"
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <iomanip>

using namespace std;

void display(const int array[], size_t size);
bool isIncreasingOrder(const int array[], size_t size);

int main()
{
    //Declaration of the test array
    int array1[5] = {1, 2, 3, 4, 5};
    int array2[8] = {1, 2, 3, 4, 5, 6, 7, 2};

    // Get the size of the array
    size_t size1 = sizeof(array1) / sizeof(int);
    size_t size2 = sizeof(array2) / sizeof(int);

    cout << "Exercise 5.10 : Increasing elements" << endl
         << "Test Arrays:" << endl;
    display(array1, size1);
    display(array2, size2);

    bool result1 = isIncreasingOrder(array1, size1);
    bool result2 = isIncreasingOrder(array2, size2);

    cout << "Result of the increasing elements :" << endl
         << "Array 1 : " << boolalpha << result1 << endl
         << "Array 2 : " << boolalpha << result2;
}

/** @brief Indicates if the elements of the array are in increasing order
 * @param array The array
 * @param size The size of the array*/
bool isIncreasingOrder(const int array[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (array[i] > array[i + 1])
            return false;
    }
    return true;
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