// File:        VanHove_Labo22_5.26.cpp
// Author:      Timothee Van Hove
// Date:        11.11.2021
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

void display(const vector<int> &v);
int isOdd(int num);

int main()
{
    const size_t arraySize = 5;
    int array[] = {3, 2, -5, 2, 4};
    vector<int> v;
    v.resize(arraySize);
    copy(array, array + 5, v.begin());
    cout << "Le vecteur initial: ";
    display(v);
    auto i = min_element(v.begin(), v.end());
    cout << "La plus petite valeur de v : " << *i << endl;
    i = max_element(v.begin(), v.end());
    cout << "La plus grand valeur de v : " << *i << endl;
    cout << "La somme des éléments de v : " << accumulate(v.begin(), v.end(), 0) << endl;
    cout << "Occurences de la valeur 2 : " << count(v.begin(), v.end(), 2) << endl;
    cout << "Nbr de valeurs impaires dans v : " << count_if(v.begin(), v.end(), isOdd) << endl;
    sort(v.begin(), v.end());
    cout << "Le vecteur trié croissant : ";
    display(v);
    sort(v.rbegin(), v.rend());
    cout << "Le vecteur trié décroissant : ";
    display(v);
}

/**  @brief displays the content of a vector
 *   @param v the vector*/
void display(const vector<int> &v)
{
    cout << "[";
    for (auto i = v.begin(); i != v.end(); i++)
    {
        cout << *i;
        if (i == v.end() - 1)
            cout << "]";
        else
            cout << ", ";
    }
    cout << endl;
}

int isOdd(int num) { return num % 2; }