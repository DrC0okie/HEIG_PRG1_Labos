// File:        Rational.hpp
// Author:      Timothee Van Hove
// Date:        28.01.2022
// Description: Rational class header

#ifndef RATIONAL_HPP
#define RATIONAL_HPP
#include <iostream>
#include <string>
#include "Uint.hpp"

class Rational{
public:
    /** @brief Default constructor*/
    Rational();

    /** @brief String copy constructor
     * @param num The number from which construct the rational */
    Rational(const std::string &str);

    /** @brief int copy constructor
     * @param num The number from which construct the rational */
    Rational(const int &num);

    /** @brief Uint constructor*/
    Rational(const Uint &num, const Uint &den = 1, bool isPositive = true);

    /** @brief Int constructor*/
    Rational(int num, int den, bool isPositive);

    /** @brief Compares if the left Rational is <, >, or ==
     * @param left The left Rational
     * @param right The right Rational
     * @return 1 if left < right, -1 if left > right and 0 if left == right */
    friend int comp(const Rational &l, const Rational &r);

    /** @brief Overload of the << operator for the Rational class
     * @param os The output stream (left member)
     * @param r The Rational value (right member)
     * @return The output stream containing the Rational value */
    friend std::ostream &operator<<(std::ostream &os, const Rational &r);

    /** @brief Overload of the >> operator for the Rational class
     * @param is The input stream (left member)
     * @param r The Rational value (right member)
     * @return The input stream containing the Rational value */
    friend std::istream &operator>>(std::istream &is, Rational &r);

    /** @brief Overload of the + operator for the Rational class
     * @param l The left member of the addition
     * @param r The right member of the addition
     * @return The result of the addition */
    friend Rational operator+(Rational l, const Rational &r) { return l += r; }

    /** @brief Overload of the - operator for the Rational class
     * @param l The left member of the substraction
     * @param r The right member of the subtraction
     * @return The difference of the subtraction */
    friend Rational operator-(Rational l, const Rational &r) { return l -= r; }

    /** @brief Overload of the * operator for the Rational class
     * @param l The left member of the multiplication
     * @param r The right member of the multiplication
     * @return The product of the multiplication */
    friend Rational operator*(Rational l, const Rational &r) { return l *= r; }

    /** @brief Overload of the / operator for the Rational class
     * @param l The left member of the division (dividend)
     * @param r The right member of the division (divizor)
     * @return The quotient of the division */
    friend Rational operator/(Rational l, const Rational &r) { return l /= r; }

    /** @brief Overload of the unary - operator for the Rational class
     * @return Rational with opposite sign */
    Rational operator-() const;

    /** @brief Overload of the += operator for the Rational class
     * @param right The right member to add (Rational)
     * @return The Rational object after the addition */
    Rational &operator+=(const Rational &right);

    /** @brief Overload of the -= operator for the Rational class
     * @param right The right member to subtract (Rational)
     * @return The Rational object after the subtraction */
    Rational &operator-=(const Rational &right);

    /** @brief Overload of the *= operator for the Rational class
     * @param right The right member to multiply (Rational)
     * @return The Rational object after the multiplication */
    Rational &operator*=(const Rational &right);

    /** @brief Overload of the /= operator for the Rational class
     * @param right The right member (divizor) (Rational)
     * @return The Rational object after the division */
    Rational &operator/=(const Rational &right);

    /** @brief Overload of the < operator for the Rational class
     * @param r The right member to compare with
     * @return true if  (left member) < (right member), false if not */
    bool operator<(const Rational &r) const { return comp(*this, r) == -1; }

    /** @brief Overload of the <= operator for the Rational class
     * @param r The right member to compare with
     * @return true if  (left member) <= (right member), false if not */
    bool operator<=(const Rational &r) const { return comp(*this, r) != 1; }

    /** @brief Overload of the > operator for the Rational class
     * @param r The right member to compare with
     * @return true if  (left member) > (right member), false if not */
    bool operator>(const Rational &r) const { return comp(*this, r) == 1; }

    /** @brief Overload of the >= operator for the Rational class
     * @param r The right member to compare with
     * @return true if  (left member) >= (right member), false if not */
    bool operator>=(const Rational &r) const { return comp(*this, r) != -1; }

    /** @brief Overload of the == operator for the Rational class
     * @param r The right member to compare with
     * @return true if  (left member) == (right member), false if not */
    bool operator==(const Rational &r) const { return comp(*this, r) == 0; }

    /** @brief Overload of the != operator for the Rational class
     * @param r The right member to compare with
     * @return true if  (left member) != (right member), false if not */
    bool operator!=(const Rational &r) const { return comp(*this, r) != 0; }

    /** @brief Generic overload of the != operator for the Rational class
     * @param r The right member to compare with
     * @return true if  (left member) != (right member), false if not */
    template<typename T>
    bool operator!=(const T &r) const { return comp(*this, Rational(r)) != 0; }

private:
    // Internal values that reprensent a rational number
    Uint numerator, denominator;
    bool isPositive;

    /** @brief Compares if the left Rational is <, >, or ==
     * @return 1 if left < right, -1 if left > right and 0 if left == right */
    Rational &getIrreductible();

    /** @brief Manage the sign of the left Rational for multiplication and division
     * @param right The left Rational to manage
     * @return The Rational with correct sign*/
    Rational &manageSign(const Rational &right);

    /** @brief If the numerator =  sets the sign to positive
     * @param r The rational to check
     * @return Rational& the checked rational  */
    Rational &checkZeroSign(Rational &r);
};
#endif