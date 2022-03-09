// File:        VanHove_Labo19_5.9.cpp
// Author:      Timothee Van Hove
// Date:        10.11.2021
// Description: Exercise 5.9 "Suppression du ou des éléments centraux"
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>

using namespace std;

void display(const int array[], size_t size);
void deleteCenter(int array[], size_t &size);

int main()
{
    //Declaration of the test array
    int array1[5] = {1, 2, 3, 4, 5};
    int array2[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    // Get the size of the array
    size_t size1 = sizeof(array1) / sizeof(int);
    size_t size2 = sizeof(array2) / sizeof(int);

    cout << "Exercise 5.9 : Center deletion" << endl
         << "Test Arrays:" << endl;
    display(array1, size1);
    display(array2, size2);

    deleteCenter(array1, size1);
    deleteCenter(array2, size2);

    cout << "After deleting the center:" << endl;
    display(array1, size1);
    display(array2, size2);
}

/** @brief Deletes the center element of an array if odd, the 2 centers if even
 * @param array The array
 * @param size The size of the array*/
void deleteCenter(int array[], size_t &size)
{
    int ceilCenter = size / 2;
    if (size % 2 == 0)
    {
        for (size_t i = 0; i < ceilCenter; i++)
            array[ceilCenter - 1 + i] = array[ceilCenter + 1 + i];
        size -= 2;
    }
    else
    {
        for (size_t i = 0; i < ceilCenter; i++)
            array[ceilCenter + i] = array[ceilCenter + (i + 1)];
        size--;
    }
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