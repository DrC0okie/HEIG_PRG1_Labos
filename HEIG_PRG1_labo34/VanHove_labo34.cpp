// File:        VanHove_Labo34.cpp
// Author:      Timothee Van Hove
// Date:        28.01.2022
// Description: Resolve linear equations system with generic functions and rational integers
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

// Notes:       The pivot algorithm and functions in this file does not belong to me.
//              I deleted the functions entreeUtilisateur and TailleMatrice because there 
//              is no need of them. They are called 1x each, and there is no code duplication
//              I modified other functions to be generic, and make them more robust to user inputs.

#include <iostream>
#include <vector>
#include <limits>
#include "Rational.hpp"

using namespace std;

template <typename T> void printRow(const vector<T> &ligne);
template <typename T> void printMatrix(const vector<vector<T>> &t);
template <typename T> void pivot(vector<vector<T>> &v, size_t row,
                                size_t column, int rowCount, int columnCount);
int main(void)
{
    try
    {
        Rational r(-4, 4, true);
        cout << r << endl;
        // User input
        cout << "Equation system size : ";
        int input;
        while (!(cin >> input) || input < 1)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong input. Please enter an integer > 0" << endl
                << "Equation system size : ";
        }

        int columnCount = input + 1;
        int rowCount = input;
        vector<vector<Rational>> v(rowCount, vector<Rational>(columnCount));

        // Input of the element of the equation system
        for (size_t i = 0; i < rowCount; i++)
            for (size_t j = 0; j < columnCount; j++)
            {
                cout << "Enter the element at row " << i
                     << " and column " << j << endl;
                cin >> v.at(i).at(j);
            }

        while(true)
        {
            printMatrix(v);
            cout << "Enter row and column of the pivot, any non-digit to exit"
                 << endl;
            size_t i, j;

            if(!(cin >> i >> j))
                return EXIT_SUCCESS;
                
            if (i < rowCount and j < columnCount and v.at(i).at(j) != 0.0)
                pivot(v, i, j, rowCount, columnCount);
            else
                cout << "invalid pivot" << endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << endl << "The program will call exit()";
        EXIT_FAILURE;
    }
    catch(...)
    {
        std::cerr << "Unmanaged exception thrown" << endl 
                  << "The program will call exit()";
        EXIT_FAILURE;
    }
}


template <typename T> void printRow(const vector<T> &ligne)
{
    for (size_t j = 0; j < ligne.size(); j++)
        cout << scientific << ligne.at(j) << " ";
    cout << endl;
}

template <typename T> void printMatrix(const vector<vector<T>> &t)
{
    cout << "----------------------" << endl;
    for (size_t i = 0; i < t.size(); i++)
        printRow(t.at(i));
    cout << endl;
}

template <typename T> void pivot(vector<vector<T>> &v, size_t row,
                                 size_t column, int rowCount, int columnCount)
{
    for (size_t i = 0; i < rowCount; i++)
        if (i != row)
            for (size_t j = 0; j < columnCount; j++)
                if (j != column)
                    v.at(i).at(j) = v.at(i).at(j) - v.at(i).at(column) * v.at(row).at(j) / v.at(row).at(column);

    for (size_t i = 0; i < rowCount; i++)
        if (i != row)
            v.at(i).at(column) = -v.at(i).at(column) / v.at(row).at(column);

    for (size_t j = 0; j < columnCount; j++)
        if (j != column)
            v.at(row).at(j) = v.at(row).at(j) / v.at(row).at(column);

    v.at(row).at(column) = 1.0 / v.at(row).at(column);
}

void matrixSize(int &columnCount, int &lineCount, int value)
{
    columnCount = value + 1;
    lineCount = value;
}