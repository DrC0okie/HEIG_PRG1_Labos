// File:        Uint.cpp
// Author:      Timothee Van Hove
// Date:        15.01.2022
// Description: Implementation of the Uint class

#include <sstream>
#include <iostream>
#include "Uint.hpp"

Uint::Uint(const std::string &str)
{
    // put each char of the string into the iValue vector
    for (auto i = str.crbegin(); i != str.crend(); ++i)
    {
        if (isdigit(*i))
            iValue.push_back(uint32_t(*i) - GETNUM);

        else // Throw an exception if the char is not a digit
            throw std::invalid_argument(
                "Construction error : the string is not a valid number");
    }
    // Erase the possible prefixed 0
    eraseZero();
}

Uint &Uint::carry()
{
    for (size_t i = 0; i < iValue.size(); ++i)
    {
        // If this->iValue hasn't space to put the nth, push back
        if (i == iValue.size() - 1)
        { // Push back only if this->iValue[i] contains 2 digit number
            if (iValue.at(i) >= BASE)
                iValue.push_back(iValue.at(i) / BASE);
        }
        else // Else just put the nth in this->iValue[i]
            iValue.at(i + 1) += iValue.at(i) / BASE;

        // Only keep the digit part
        iValue.at(i) %= BASE;
    }
    return *this;
}

int Uint::cmp(const Uint &left, const Uint &right) const
{
    // First, compare the size of internal values
    if (left.iValue.size() == right.iValue.size())
    {
        // Then, compare each element's values
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

Uint& Uint::eraseZero()
{
    while (iValue.size() > 1 && *(iValue.end() - 1) == 0)
        iValue.erase((iValue.end() - 1));
    return *this;
}

void Uint::checkZero(const Uint& number) const
{
    if (number.isZero())
        throw std::runtime_error("Division by 0");
}

void Uint::checkZero(uint32_t number) const
{
    if (number == 0)
        throw std::runtime_error("Division by 0");
}

Uint Uint::divAndRem(const Uint &dividend, const Uint &divizor, Uint &rem)
{
    Uint pTemp(1), divizorTemp = divizor, quotient(0);

    while (divizorTemp <= dividend)
    {
        pTemp *= 2;
        divizorTemp *= 2;
    }

    rem = dividend;

    while (rem >= divizor)
    {
        divizorTemp /= 2;
        pTemp /= 2;

        if (rem >= divizorTemp)
        {
            quotient += pTemp;
            rem -= divizorTemp;
        }
    }
    return quotient;
}

Uint mod_pow(Uint base, Uint exp, const Uint &mod)
{
    Uint result = 1;

    while (exp > 0)
    {
        if (exp.isEven())
        { // Exponent is even
            base = base * base % mod;
            exp /= 2;
        }
        else
        { // Exponent is odd
            result = result * base % mod;
            --exp;
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const Uint &u)
{
    // Put all the elements of iValue into the output stream
    for (auto i = u.iValue.crbegin(); i != u.iValue.crend(); ++i)
        os << *i;

    return os;
}

std::istream &operator>>(std::istream &is, Uint &u)
{
    std::string buffer;
    if (is >> buffer) // put the istream in the Uint
        u = buffer;
    else // Set the error state flags
        is.clear(std::ios::badbit | is.rdstate());

    return is;
}

Uint Uint::operator++(int)
{ // Postfixed
    Uint tmp = *this;
    ++(*this);

    // Return the previous value
    return tmp;
}

Uint &Uint::operator++()
{ // Prefixed
    // Only increment the last digit
    ++iValue.front();

    // If the last number is 10, carry it's digits
    if (iValue.front() > 9)
        carry();
    return *this;
}

Uint Uint::operator--(int)
{
    Uint tmp = *this;
    --(*this);

    // return the previous value
    return tmp;
}

Uint &Uint::operator--()
{
    // Simple case : increase the front
    if (iValue.front() > 1)
        --iValue.front();
    else
    { // else use the slow operation -=
        *this -= 1;
        return carry();
    }
    return *this;
}

Uint &Uint::operator+=(const Uint &right)
{
    // Resize this->iValue in case < right.iValue
    if (iValue.size() < right.iValue.size())
        iValue.resize(uint32_t(right.iValue.size()), 0);

    // sum each element of internal values
    for (size_t i = 0; i < right.iValue.size(); ++i)
        iValue.at(i) += right.iValue.at(i);

    // carry the multiple-digits numbers in different indexes
    return carry();
}

Uint &Uint::operator-=(const Uint &right)
{
    Uint tmp = right;

    // Verification that the right member is strictly lower
    if (*this < right)
        throw std::runtime_error("Cannot substract an Uint with a greater Uint");

    // Resize the tmp variable in case this->iValue is larger
    if (iValue.size() > tmp.iValue.size())
        tmp.iValue.resize(uint32_t(iValue.size()), 0);

    // Columnar substration
    for (size_t i = 0; i < iValue.size(); ++i)
    {
        if (iValue.at(i) < tmp.iValue.at(i))
        { // Increase the next column of tmp
            tmp.iValue.at(i + 1)++;

            // Add 10 to this to get a positive value
            iValue.at(i) += BASE;
        }
        // Substract the column
        iValue.at(i) -= tmp.iValue.at(i);
    }
    // Erase possible prefixed zeros
    return eraseZero();
}

Uint &Uint::operator*=(const Uint &right)
{
    // Use a temporary value to work on it
    Uint tmp = 0;

    // Iterates on each members of the right value
    for (size_t i = 0; i != right.iValue.size(); i++)
    {
        // Adds in tmp the result of the multiplication of right and left
        tmp += right.iValue.at(i) * *this;

        // If the size of the right value is too small, insert
        if (i != right.iValue.size() - 1)
            iValue.insert(iValue.cbegin(), 0);
    }

    *this = tmp;
    return eraseZero();
}

Uint &Uint::operator*=(uint32_t right)
{
    // Multiply each index by right
    for (uint32_t i = 0; i < iValue.size(); ++i)
        iValue.at(i) *= right;

    // Report the multiple digits numbers
    return carry();
}

Uint &Uint::operator/=(const Uint &right)
{
    checkZero(right);
    Uint rem;
    *this = divAndRem(*this, right, rem);
    return *this;
}

Uint &Uint::operator/=(uint32_t right)
{
    checkZero(right);

    // Iterates iValues until the index before the last
    for (size_t i = iValue.size() - 1; i > 0; i--)
    {
        // For each index, add the tenth part of the number to the next digit
        iValue.at(i - 1) += (iValue.at(i) % right) * BASE;

        // Then divide by right to get the digit part
        iValue.at(i) /= right;
    }
    // Finally divide the first digit with the right number
    iValue.at(0) /= right;

    return eraseZero();
}

Uint &Uint::operator%=(const Uint &right)
{
    checkZero(right);
    divAndRem(*this, right, *this);
    return *this;
}

Uint &Uint::operator%=(uint32_t right)
{
    checkZero(right);
    // Quick way to get the mod with a uint32_t without divAndRem()
    return *this -= (*this / right) * right;
}

Uint::operator uint64_t() const
{
    try
    {
        std::stringstream convert;
        convert << *this;
        return std::stoull(convert.str());
    }
    catch (const std::exception &e)
    {
        std::cerr 
            << e.what() << ": Number too large to be cast to uint64_t" << '\n';
        return 0;
    }
}