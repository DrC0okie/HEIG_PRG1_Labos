// File:        VanHove_Labo21_5.13.cpp
// Author:      Timothee Van Hove
// Date:        11.11.2021
// Description: Exercise 5.13 "Suppression des doublons"
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>

using namespace std;

void display(const int array[], size_t size);
void deleteDoppelganger(int array[], size_t &size);

int main()
{
    // Declaration of the test array
    int array1[4] = {1, 2, 3, 4};
    int array2[8] = {1, 2, 3, 2, 5, 2, 2, 8};

    // Get the size of the array
    size_t size1 = sizeof(array1) / sizeof(int);
    size_t size2 = sizeof(array2) / sizeof(int);

    // User message
    cout << "Exercise 5.13 : Deletion of doppelgangers" << endl
         << "Test Arrays before deletion :" << endl;
    display(array1, size1);
    display(array2, size2);

    deleteDoppelganger(array1, size1);
    deleteDoppelganger(array2, size2);

    cout << endl << "Result of the deletion :" << endl;
    display(array1, size1);
    display(array2, size2);
}

/** @brief Deletes a value from the array
 * @param array The array
 * @param size The size of the array
 * @param value The value to delete*/
void deleteDoppelganger(int array[], size_t &size)
{
    for (size_t i = 0; i < size; i++)
        for (size_t j = 1; j < size - i; j++)
            if (array[i] == array[i + j])
            {
                for (size_t k = 0; k < size - (i + j); k++)
                    array[i] = array[i + j + k];
                i--;
                size--;
            }
}

/**  @brief Display the content of an array
 * @param array The array
 * @param size The size of the array*/
void display(const int array[], size_t size)
{
    for (size_t i = 0; i < size; i++)
        cout << "[" << array[i] << "] ";

    cout << endl;
}