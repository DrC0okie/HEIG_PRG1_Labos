// File:        VanHove_Labo22_5.24.cpp
// Author:      Timothee Van Hove
// Date:        11.11.2021
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void display(const vector<int> &v);
vector<int> areEqual(const vector<int> &v1, const vector<int> &v2);

const size_t SIZE1 = 4, SIZE2 = 5;

int main()
{
    vector<int> v1{1, 3, 5, 6};
    vector<int> v2{2, 4, 6, 8};
    cout << "Content of the vectors: " << endl;
    display(v1);
    display(v2);

    cout << endl << "Concatenated vectors: ";
    // user output
    display(areEqual(v1, v2));
}

/** @brief Concats v2 at the end of v1
 * @param v1 The first vector
 * @param v2 The second vector
 * @return The concatenated vector*/
vector<int> areEqual(const vector<int> &v1, const vector<int> &v2)
{
    vector<int> tmp = v1;
    tmp.resize(v1.size() + v2.size());
    copy(v2.begin(), v2.end(), copy(v1.begin(), v1.end(), tmp.begin()));
    return tmp;
}

/**  @brief displays the content of a vector
 *   @param v the vector*/
void display(const vector<int> &v)
{
    for (size_t i = 0; i < v.size(); i++)
        cout << "[" << v.at(i) << "] ";

    cout << endl;
}