// File:        VanHove_Labo19_5.8.cpp
// Author:      Timothee Van Hove
// Date:        10.11.2021
// Description: Exercise 5.8 "Décalage à droite cyclique des éléments"
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>

using namespace std;

void display(const int array[], size_t size);
void rightShift(int array[], size_t size);

int main()
{
    //Declaration of the test array
    int array[5] = {1, 2, 3, 4, 5};

    // Get the size of the array
    size_t size = sizeof(array) / sizeof(int);

    cout << "Exercise 5.8 : right offset" << endl << "Test Array:";
    display(array, size);

    rightShift(array, size);

    cout << "Right offset: ";
    display(array, size);
}

/**
 * @brief Shifts the values in the array to the right
 * @param array The array
 * @param size The size of the array*/
void rightShift(int array[], size_t size)
{
    int tmp = array[size - 1];
    for (size_t i = 0; i < size; i++)
        array[size - i] = array[size - (i + 1)];
    
    array[0] = tmp;
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