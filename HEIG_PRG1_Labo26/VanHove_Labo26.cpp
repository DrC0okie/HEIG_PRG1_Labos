// File:        VanHove_Labo26.cpp
// Author:      Timothee Van Hove
// Date:        03.12.2021
// Description: Reads a text file in redirected std cin and outputs text statistics
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

using namespace std;

/**  @brief Parses a string, separates it's words and put them in a vector
 * @details Does not take the punctuation, spaces and non-printable char
 * @param text String that contains the words to separate
 * @return The vector filled by separated words */
vector<string> separateWords(string &text);

/** @brief Displays the statistics of the words in the std out stream
 * @param v The vector that contains all the words*/
void displayStatistics(vector<string> &v);

int main()
{
    string text;

    getline(cin, text, '\0');
    vector<string> words = separateWords(text);
    displayStatistics(words);
}

void displayStatistics(vector<string> &v)
{
    sort(v.begin(),v.end());
    int count = 1, mostRec = 0;
    string mostRecStr;

    // First, sort the vector
    

    //Then only display unique words
    for (auto i = v.begin(); i != v.end(); ++i)
    {
        if (*i == *(i + 1) && ((i + 1) - v.begin()) < v.size())
            count++;
        else
        {
            cout << *i << " : " << count << endl;
            count = 1;
        }
        if(mostRec < count)
        {
            mostRec = count;
            mostRecStr = *i + " : " + to_string(mostRec);
        }
    }
    cout << "Most recurrent word : " << mostRecStr << endl;
    cout << "Number of words : " << v.size();

}

vector<string> separateWords(string &text)
{
    vector<string> words;
    string word;
    for (auto i = text.begin(); i != text.end(); ++i)
    {
        //Special char with a length of 2 bytes
        if (*i == '\xC3' || *i == '\xC5' || *i == '\xC2')
        {
            word.push_back(*i);
            word.push_back(*(i + 1));
            ++i;
        }
        //Special char with a length of 3 bytes
        else if (*i == '\xE2')
        {
            i += 2;
            if (word != "")
                words.push_back(word);

            word.clear();
        }
        // Nominal case (normal letter / digit)
        else if (isalnum(*i))
        {
            word.push_back(*i);
        }
        // Do not put other char in the vector
        else
        {
            if (word != "")
            {
                words.push_back(word);
                word.clear();
            }
        }
    }

    return words;
}