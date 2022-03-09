// File:        VanHove_Labo22_5.25.cpp
// Author:      Timothee Van Hove
// Date:        11.11.2021
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void display(const vector<int> &v);
bool areEqual(vector<int> &v1, vector<int> &v2);

const size_t SIZE1 = 4, SIZE2 = 5;

int main()
{
    vector<int> v1{1, 3, 5, 6};
    vector<int> v2{1, 3, 5, 6};
    cout << "Content of the vectors: " << endl;
    display(v1);
    display(v2);

    // User output
    if(areEqual(v1, v2))
        cout << "The vectors are equal";
    else 
        cout << "the vectors are not equal";    
}

/** @brief Concats v2 at the end of v1
 * @param v1 The first vector
 * @param v2 The second vector
 * @return The concatenated vector*/
bool areEqual(vector<int> &v1, vector<int> &v2)
{
    if(v1.size() > v2.size())
        v2.resize(v1.size());
    else if (v1.size() < v2.size())
        v1.resize(v2.size());

    return equal(v1.begin(), v1.end(), v2.begin());
}

/**  @brief displays the content of a vector
 *   @param v the vector*/
void display(const vector<int> &v)
{
    for (auto i = v.begin(); i != v.end(); i++)
        cout << "[" << *i << "] ";

    cout << endl;
}