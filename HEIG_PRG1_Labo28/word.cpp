#include <string>
#include "word.hpp"

Word::Word(const std::string &initWord, int initCount) : text(initWord), count(initCount) {}

std::string Word::getText() const
{
    return text;
}

void Word::setText(const std::string &setWord)
{
    text = setWord;
}

void Word::setCount(int setCount)
{
    count = setCount;
}

int Word::getCount() const
{
    return count;
}

bool Word::operator<(Word const &w) const
{
    // Sort lexicographically if counts are identical
    if (count == w.getCount())
        return text < w.getText();

    // Else sort by count
    return count > w.getCount();
}

bool Word::operator!=(Word const &w) const
{
    return text != w.getText();
}