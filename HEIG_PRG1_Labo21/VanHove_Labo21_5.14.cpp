// File:        VanHove_Labo21_5.14.cpp
// Author:      Timothee Van Hove
// Date:        10.11.2021
// Description: Exercise 5.14 "Egalité entre 2 tableaux"
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <iomanip>

using namespace std;

void displayFromEnd(const int array[], size_t size);
bool compareArrays(const int array1[], const int array2[], size_t size1, size_t size2);

int main()
{
    // Declaration of the test array
    int array1[4] = {1, 2, 3, 4};
    int array2[8] = {1, 2, 3, 4, 2, 1, 2, 1};

    // Get the size of the array
    size_t size1 = sizeof(array1) / sizeof(int);
    size_t size2 = sizeof(array2) / sizeof(int);

    // User message
    cout << "Exercise 5.14 : Arrays equality" << endl
         << "Test Arrays:" << endl;
    displayFromEnd(array1, size1);
    displayFromEnd(array2, size2);

    bool result = false;

    // The array comparison must be: size array compared < size array src 
    if(size1 < size2)
         result = compareArrays(array2, array1, size2, size1);
    else  result = compareArrays(array1, array2, size1, size2);

    if (result)
        cout << "They are the same";
    else
        cout << "They are different";
}

/** @brief Compare 2 arrays and outputs true if they are identical
 * @details size & array1 must be >= size and array 2
 * @param array1 The src array
 * @param array2 The array that will be compared
 * @param size1 The size of the array1
 * @param size2 The size of the array2
 * @return true if arrays are identical, false if not
 */
bool compareArrays(const int array1[], const int array2[], size_t size1, size_t size2)
{
    for (size_t i = 0; i < size1; i++)
    {
        bool valueInArray = false;

        for (size_t j = 0; j < size2; j++)
            if (array1[i] == array2[j])
                valueInArray = true;

        if (!valueInArray)
            return false;
    }
    return true;
}


/**  @brief Display the content of an array
 * @param array The array
 * @param size The size of the array*/
void displayFromEnd(const int array[], size_t size)
{
    for (size_t i = 0; i < size; i++)
        cout << "[" << array[i] << "] ";

    cout << endl;
}