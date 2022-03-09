#include "Uint.hpp"
#include <iostream>

Uint::Uint(){}

Uint::Uint(std::string c)
{
    for (auto i = c.rbegin(); i != c.rend(); ++i)
    {
        if (isdigit(*i))
            iValue.push_back(uint32_t(*i) - GETNUM);
        
        else
            std::cerr << "Construction of Uint failed."
                      << "The string contained non digital characters"
                      << std::endl;
    }

    eraseZero();
}

Uint::Uint(uint64_t c) { *this = std::to_string(c); }

Uint &Uint::carry()
{
    for (size_t i = 0; i < iValue.size(); ++i)
    {
        // If this->iValue hasn't space to put the nth, push back
        if (i == iValue.size() - 1)
        {// Push back only if this->iValue[i] contains 2 digit number
            if (iValue.at(i) >= 10) 
                iValue.push_back(iValue.at(i) / 10);
        }
        else // Else just put the nth in this->iValue[i]
            iValue.at(i + 1) += iValue.at(i) / 10;

        // Only keep the digit part
        iValue.at(i) %= 10; 
    }

    return *this;
}

int Uint::comp(const Uint &left, const Uint &right) const
{
    // First, compare the size of internal values
    if (left.iValue.size() == right.iValue.size())
    {
        //Then, compare each element's values
        for (auto l = left.iValue.crbegin(), r = right.iValue.crbegin();
             l != left.iValue.crend(); ++l, ++r)
        {
            if (*l < *r)
                return -1;
            else if (*l > *r)
                return 1;
        }
        return 0;
    }
    else if (left.iValue.size() < right.iValue.size())
        return -1;

    return 1;
}

Uint &Uint::eraseZero()
{
    size_t cnt = 0;
    for (auto i = iValue.crbegin(); *i == 0; ++i)
        cnt++;
    // Delete the prefixed "0" of the number
    iValue.resize(iValue.size() - cnt);
    return *this;
}

Uint operator*(uint32_t left, const Uint &right)
{
    return right * left;
}

std::ostream &operator<<(std::ostream &out, const Uint &u)
{
    for (auto i = u.iValue.crbegin(); i != u.iValue.crend(); ++i)
        out << *i;

    return out;
}

Uint Uint::operator+(const Uint &right) const
{
    Uint temp = *this;
    return temp += right;
}

Uint Uint::operator-(const Uint &right) const
{
    Uint temp = *this;
    return temp -= right;
}

Uint Uint::operator*(const Uint &right) const
{
    Uint temp = *this;
    temp *= right;
    return temp;
}

Uint Uint::operator*(uint32_t right) const
{
    Uint temp = *this;
    temp *= right;
    return temp;
}

Uint Uint::operator++(int)
{// postfixed operator that use prefixed operator
    Uint temp = *this;
    ++(*this);
    return temp;
}

Uint &Uint::operator++()
{// Prefixed operator
    ++iValue.front();
    return carry();
}

Uint &Uint::operator+=(const Uint &right)
{
    // Resize this->iValue in case < right.iValue
    if (iValue.size() < right.iValue.size())
        iValue.resize(uint32_t(right.iValue.size()), 0);

    // sum each element of internal values
    for (size_t i = 0; i < right.iValue.size(); i++)
        iValue.at(i) += right.iValue.at(i);

    // split all the digits numbers in different indexes
    return carry();
}

Uint &Uint::operator-=(const Uint &right)
{
    Uint temp = right;
    if (iValue.size() < right.iValue.size())
    {
        // Error case -> cannot return negative value
        std::cerr << "Cannot substract an Uint with a greater Uint" << std::endl;
        return *this;
    }

    //Resize the temp variable in case this->iValue is larger
    temp.iValue.resize(uint32_t(iValue.size()), 0);

    //Columnar substration
    for (size_t i = 0; i < temp.iValue.size(); i++)
    {
        if (iValue.at(i) < temp.iValue.at(i))
        {// Increase the next column of temp
            temp.iValue.at(i + 1)++;

        //Add 10 to this to get a positive value
            iValue.at(i) += 10;
        }

        // Substract the column
        iValue.at(i) -= temp.iValue.at(i);
    }

    //Erase possible prefixed zeros
    return eraseZero();
}

Uint &Uint::operator*=(const Uint &right)
{
    Uint tmp = 0;
    for (auto i = right.iValue.cbegin(); i != right.iValue.cend(); ++i)
    {
        // Add in the tmp variable the product of this Uint and right[i]
        tmp += (*i * *this);

        // Insert a 0 in [a] only if i't not the last loop
        if (i != right.iValue.cend() - 1)
            iValue.insert(iValue.cbegin(), 0);
    }

    // report the values and return the product
    *this = tmp.carry();
    return *this;
}

Uint &Uint::operator*=(uint32_t right)
{
    // Multiply each index by right
    for (auto i = iValue.begin(); i != iValue.end(); ++i)
        *i *= right;

    // Report the multiple digits numbers
    return carry();
}

bool Uint::operator<(const Uint &right) const { return comp(*this, right) == -1; }

bool Uint::operator<=(const Uint &right) const { return comp(*this, right) != 1; }

bool Uint::operator>(const Uint &right) const { return comp(*this, right) == 1; }

bool Uint::operator>=(const Uint &right) const { return comp(*this, right) != -1; }

bool Uint::operator==(const Uint &right) const { return comp(*this, right) == 0; }

bool Uint::operator!=(const Uint &right) const { return comp(*this, right) != 0; }