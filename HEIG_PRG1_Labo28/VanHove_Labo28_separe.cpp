// File:        VanHove_Labo28_separe.cpp
// Author:      Timothee Van Hove
// Date:        10.12.2021
// Description: Reads "Les misérables" and outputs statistics in special order
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include "word.hpp"

using namespace std;

/** @brief Parses a string, separates it's words and put them in a vector
 * @details Does not take the punctuation, spaces and non-printable char
 * @param text String that contains the words to separate
 * @return The vector filled by separated words */
vector<Word> separateWords(string &text);

/** @brief Counts occurences of a Word in a vector<Word> and erase them
 * @details Sort the vector by count and lexicograpgically
 * @param v The vector to be counted
 * @return vector<Word> without any occurences*/
vector<Word> countWordOccurences(vector<Word> &v);

/** @brief Outputs a formatted vector<Words> in the std:cout stream
 * @param w The vector*/
void outputText(const vector<Word> &w);

/** @brief Compares 2 words to be sorted by occurence and lexicographically
 * @details Used as predicate for the sort function
 * @param w1 The first word
 * @param w2 The second word
 * @return true if w1 < w2 in terms of predicate */
bool compareOccurences(const Word &a, const Word &b);

int main()
{
    string text;

    // Reads the input stream
    getline(cin, text, '\0');

    // Separate all words and put it in a vector
    vector<Word> words = separateWords(text);

    // Count occurences, delete them, sort the vector by count and outputs it
    outputText(countWordOccurences(words));
}

void outputText(const vector<Word> &w)
{
    for (auto i = w.begin(); i != w.end(); ++i)
    {
        cout << (*i).getText() << " : " << (*i).getCount() << endl;
    }
}

vector<Word> countWordOccurences(vector<Word> &w)
{
    // Sort the vector lexicographically
    sort(w.begin(), w.end());

    vector<Word> sortedVector;
    int cnt = 1;
    for (auto i = w.begin(); i != w.end(); ++i)
    {
        // Check if the next word is different (last word)
        if (*i != *(i + 1))
        {
            // put the count in the last Word object
            (*i).setCount(cnt);

            // Push it back in the sorted vector
            sortedVector.push_back(*i);

            // Reset the count
            cnt = 1;
        }
        else
            cnt++;
    }
    // Sort the vector by count and lexicographically
    sort(sortedVector.begin(), sortedVector.end());
    return sortedVector;
}

vector<Word> separateWords(string &text)
{
    vector<Word> words;
    string word;
    for (auto i = text.begin(); i != text.end(); ++i)
    {
        // Push special characters with a length of 2 bytes
        if (*i == '\xC3' || *i == '\xC5' || *i == '\xC2')
        {
            word.push_back(*i);
            word.push_back(*(i + 1));
            ++i;
        }
        // Ignore special char with a length of 3 bytes
        else if (*i == '\xE2')
        {
            i += 2;

            // If a word was previously composed, push it
            if (word != "")
                words.emplace_back(Word(word));

            word.clear();
        }
        // Push all normal letters / digits
        else if (isalnum(*i))
        {
            word.push_back(*i);
        }
        // All other characters are ignored
        else
        {
            if (word != "")
            {
                words.emplace_back(Word(word));
                word.clear();
            }
        }
    }
    return words;
}