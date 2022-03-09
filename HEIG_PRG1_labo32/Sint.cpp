// File:        Sint.hpp
// Author:      Timothee Van Hove
// Date:        15.01.2022
// Description: Implementation of the Sint class

#include <iostream>
#include "Sint.hpp"

Sint::Sint(const std::string &str)
{
    std::string tmp = str;
    if (tmp.front() == '-')
    {
        isPositive = false;
        tmp.erase(size_t(0), size_t(1));
    }
    else
        isPositive = true;
    iValue = tmp;
}

Sint::Sint(int64_t number)
{
    number >= 0 ? iValue = uint64_t(number) : iValue = uint64_t(-number);
    isPositive = number >= 0;
}

int Sint::cmp(const Sint &left, const Sint &right) const
{
    if (!left.isPositive && !right.isPositive)
        return left.iValue.cmp(right.iValue, left.iValue);
    else if (left.isPositive && !right.isPositive)
        return 1;
    else if (!left.isPositive && right.isPositive)
        return -1;
    else
        return left.iValue.cmp(left.iValue, right.iValue);
}

Sint &Sint::manageSign(Sint &a, const Sint &b)
{
    // The sign will be positive if both signs are identical
    a.isPositive = !(a.isPositive ^ b.isPositive);
    return checkZeroSign(a);
}

Sint &Sint::checkZeroSign(Sint &s)
{
    if (s.iValue.isZero())
        s.isPositive = true;
    return s;
}

std::ostream &operator<<(std::ostream &os, const Sint &s)
{
    if (!s.isPositive)
        os << '-';
    os << s.iValue;
    return os;
}

std::istream &operator>>(std::istream &is, Sint &s)
{
    std::string buffer;
    if (is >> buffer) // Use the string constructor
        s = buffer;
    else // Set the error state flags
        is.clear(std::ios::badbit | is.rdstate());
    return is;
}

Sint &Sint::operator+=(const Sint &right)
{
    // Case both numbers are positive, just add the internal values
    if (isPositive == right.isPositive)
        iValue += right.iValue;
    // Case left > right, substract the right value
    else if (iValue > right.iValue)
        iValue -= right.iValue;
    else // If ABS(left) < abs(right), substract right by left
    {
        iValue = right.iValue - iValue;
        isPositive = !isPositive;
    }
    return checkZeroSign(*this);
}

Sint &Sint::operator-=(const Sint &right)
{
    Sint tmp = right;
    return *this += -tmp;
}

Sint &Sint::operator*=(const Sint &right)
{
    iValue *= right.iValue;
    return manageSign(*this, right);
}

Sint &Sint::operator/=(const Sint &right)
{
    iValue /= right.iValue;
    return manageSign(*this, right);
}

Sint &Sint::operator%=(const Sint &right)
{
    iValue %= right.iValue;
    return checkZeroSign(*this);
}

Sint::operator int64_t() const
{
    uint64_t tmp = uint64_t(iValue);
    if (!isPositive)
        tmp = -tmp;
    return int64_t(tmp);
}