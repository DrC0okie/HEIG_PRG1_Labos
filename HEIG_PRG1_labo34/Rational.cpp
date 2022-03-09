// File:        Rational.cpp
// Author:      Timothee Van Hove
// Date:        28.01.2022
// Description: Implementation of the Rational class

#include <limits>
#include <algorithm>
#include "Rational.hpp"
#include "Helper.hpp"

const char SLASH = '/', SPACE = ' ', SIGN = '-';

/******************Local helper functions*********************/
/** @brief Unary function used as prediacte for algorithm.h functions
 * @param c The char to check
 * @return true if the char is ' ' */
bool isSpace(char c) { return c == SPACE; }

/******************Member & friend functions*******************/
Rational::Rational()
{
    numerator = 0;
    denominator = 1;
    isPositive = true;
}

Rational::Rational(const std::string &str)
{
    std::string tmp = str, numTmp, denTmp;

    // Remove all spaces
    tmp.erase(std::remove_if(tmp.begin(), tmp.end(), isSpace), tmp.end());

    // Find the / char
    size_t pos = tmp.find(SLASH);

    // Fatal error case. We don't try to correct it -> exception
    if (pos == 0)
        throw std::invalid_argument(
            details("No number found before fraction sign (/)",
            __LINE__, __PRETTY_FUNCTION__, __FILE__));

    // If no fraction sign found -> set denominator to 1
    if (pos == std::numeric_limits<size_t>::max())
    {
        numTmp = tmp;
        denTmp = "1";
    }
    // If no denominator found after fraction -> set denominator to 1
    else if (pos == tmp.length() - 1)
    {
        numTmp = tmp.substr(0, pos);
        denTmp = "1";
    }
    // Nominal case -> split the numerator and denominator part
    else
    {
        numTmp = tmp.substr(0, pos);
        denTmp = tmp.substr(pos + 1);
    }

    // Sign management
    bool numNeg = numTmp[0] == SIGN;
    bool denNeg = denTmp[0] == SIGN;
    isPositive = numNeg == denNeg;

    // Erase the sign char if present
    if (numNeg)
        numTmp.erase(0, 1);
    if (denNeg)
        denTmp.erase(0, 1);

    // Denominator = 0
    if (denTmp == "0")
        throw std::invalid_argument(
            details("The denominator can not be 0",
            __LINE__, __PRETTY_FUNCTION__, __FILE__));

    // Assignment of the internal Uint values
    numerator = numTmp;
    denominator = denTmp;

    // Simplify the fraction with GCD if possible
    *this = checkZeroSign(getIrreductible());
}

Rational::Rational(const int & num) : numerator(num)
{
    denominator = 1;
    isPositive = num >= 0? true : false;
}

Rational::Rational(const Uint &num, const Uint &den, bool isPositive)
{
    numerator = num;
    denominator = den;
    this->isPositive = isPositive;
}

Rational::Rational(int num, int den, bool isPositive)
{
    this->isPositive = (num < 0 && den < 0) || (num >= 0 && den >= 0);
    numerator = std::to_string(std::abs(num));
    denominator = std::to_string(std::abs(num));
}

int comp(const Rational &l, const Rational &r)
{   
    // (a/b) < (c/d) <==> (a * d) < (c * b)
    if (!l.isPositive && !r.isPositive)
        return cmp(r.numerator * l.denominator, l.numerator * r.denominator);
    else if (l.isPositive && !r.isPositive)
        return 1;
    else if (!l.isPositive && r.isPositive)
        return -1;
    else
        return cmp(l.numerator * r.denominator, r.numerator * l.denominator);
}

std::ostream &operator<<(std::ostream &os, const Rational &r)
{ 
    std::cout << (r.isPositive ? " " : "-") << r.numerator
              << SLASH << r.denominator;
    return os;
}

std::istream &operator>>(std::istream &is, Rational &r)
{
    // Uses the copy constructor to form the rational
    std::string tmp;
    is >> tmp;
    r = tmp;
    return is;
}

Rational Rational::operator-() const
{
    if (numerator == 0) 
        return *this;
    Rational tmp = *this; 
    tmp.isPositive = !tmp.isPositive; 
    return tmp;
}

Rational &Rational::operator+=(const Rational &right)
{
    // Cross product independent of the sign
    numerator *= right.denominator;
    Uint rNum = right.numerator * denominator;
    denominator *= right.denominator;

    // Case both rationals have the same sign
    if (isPositive == right.isPositive)
        numerator += rNum;

    // left numerator < right numerator
    else if(numerator < rNum)
    {
        numerator = rNum - numerator;
        isPositive = !isPositive;
    }

    // left numerator > right numerator
    else
        numerator -= rNum;

    return checkZeroSign(getIrreductible());
}

Rational &Rational::operator-=(const Rational &right)
{
    // Add the inverse right member
    Rational tmp = right;
    return *this += -tmp;
}

Rational &Rational::operator*=(const Rational &right)
{
    // Multiply each numerator and denominator
    denominator *= right.denominator;
    numerator *= right.numerator;
    getIrreductible();
    return manageSign(right);
}

Rational &Rational::operator/=(const Rational &right)
{
    // Throw an exception if the right rational = 0
    if(right.numerator.isZero())
        throw std::runtime_error(details("Division by 0",
                                    __LINE__, __PRETTY_FUNCTION__, __FILE__));
                                    
    // Multiply by the swapped right member
    denominator *= right.numerator;
    numerator *= right.denominator;
    getIrreductible();
    return manageSign(right);
}

Rational &Rational::getIrreductible()
{
    // Simplification of the fraction if possible
    Uint divizor = gcd(numerator, denominator);
    if (divizor != 1)
    {
        numerator /= divizor;
        denominator /= divizor;
    }
    return *this;
}

Rational &Rational::manageSign(const Rational &right)
{
    isPositive = isPositive == right.isPositive;
    return checkZeroSign(*this);
}

Rational &Rational::checkZeroSign(Rational &r)
{
    if (r.numerator.isZero())
        r.isPositive = true;
    return r;
}
