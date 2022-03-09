// File:        VanHove_Labo19_5.12.cpp
// Author:      Timothee Van Hove
// Date:        10.11.2021
// Description: Exercise 5.12 "Suppression(s) d'une valeur donnée"
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>

using namespace std;

void display(const int array[], size_t size);
void deleteDouble(int array[], size_t &size, int value);

int main()
{
    //Declaration of the test array
    int array1[4] = {1, 2, 3, 4};
    int array2[8] = {1, 2, 3, 2, 5, 2, 2, 8};
    int value;

    // Get the size of the array
    size_t size1 = sizeof(array1) / sizeof(int);
    size_t size2 = sizeof(array2) / sizeof(int);

    cout << "Exercise 5.12 : Deletion of a value" << endl
         << "Test Arrays:" << endl;
    display(array1, size1);
    display(array2, size2);

    //User message for selection of the value to delete
    cout << "Please enter a value you want to remove frome the array : ";
    cin >> value;

    deleteDouble(array1, size1, value);
    deleteDouble(array2, size2, value);

    cout << "Result of the deletion :" << endl;
    display(array1, size1);
    display(array2, size2);
}

/** @brief Deletes a value from the array
 * @param array The array
 * @param size The size of the array
 * @param value The value to delete*/
void deleteDouble(int array[], size_t &size, int value)
{
    for (size_t i = 0; i < size; i++)
        if (array[i] == value)
        {
            // Shift the elements to the left
            for (size_t j = 0; j < size - i; j++)
                array[i + j] = array[i + j + 1];

            i--;    // Decrement i to retest the position with ne new value
            size--; //Decrement the size of the array
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