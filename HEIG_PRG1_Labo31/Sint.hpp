// File:        Sint.hpp
// Author:      Timothee Van Hove
// Date:        15.01.2022
// Description: Header of the Sint class

#ifndef SINT_HPP
#define SINT_HPP

#include "Uint.hpp"

class Sint
{
private:
    Uint iValue;
    bool isPositive;

    /** @brief Compares if the left Sint is <, >, or ==
     * @param left The left Sint
     * @param right The right Sint
     * @return 1 if left < right, -1 if left > right and 0 if left == right */
    int cmp(const Sint &left, const Sint &right) const;

    /** @brief Manage the sign of the left Sint for multiplication and division
     * @param a The left Sint to manage
     * @param b The right Sint
     * @return The Sint with correct sign*/
    Sint &manageSign(Sint &a, const Sint &b);

    /** @brief delete the sign if zero
     * @param s the Sint to check */
    Sint &checkZeroSign(Sint &s);

public:
    /** @brief Empty constructor */
    Sint(){}

    /** @brief Constructor with a Uint
     *  @param u The Uint used to construct the Sint */
    Sint(const Uint& u) {iValue = u; isPositive = true;}

    /** @brief String constructor
     * @param str The string used for the construction */
    Sint(const std::string &str);

    /** @brief int64_t constructor
     * @param number The int64_t used for the construction */
    Sint(int64_t number);

    /** @brief Returns the absolute value of an Sint
     * @return the absolute value as Uint */
    Uint abs() const { return iValue;}

    /** @brief Overload of the unary - operator for the Sint class
     * @return Sint with opposite sign */
    Sint &operator-(){isPositive = !isPositive;return *this;}

    /** @brief Overload of the << operator for the Sint class
     * @param os The output stream (left member)
     * @param s The Sint value (right member)
     * @return The output stream containing the Sint value */
    friend std::ostream &operator<<(std::ostream &os, const Sint &s);

    /** @brief Overload of the >> operator for the Sint class
     * @param is The input stream (left member)
     * @param s The Sint value (right member)
     * @return The input stream containing the Sint value */
    friend std::istream &operator>>(std::istream &is, Sint &s);

    /** @brief Overload of the + operator for the Sint class
     * @param left The left member of the addition
     * @param right The right member of the addition
     * @return The result of the addition */
    friend Sint operator+(Sint left, const Sint &right){return left += right;}

    /** @brief Overload of the - operator for the Sint class
     * @param left The left member of the subtraction
     * @param right The right member of the subtraction
     * @return The difference of the subtration */
    friend Sint operator-(Sint left, const Sint &right){return left -= right;}

    /** @brief Overload of the * operator for the Sint class
     * @param left The left member of the multiplication
     * @param right The right member of the multiplication
     * @return The product of the multiplication */
    friend Sint operator*(Sint left, const Sint &right){return left *= right;}

    /** @brief Overload of the / operator for the Sint class
     * @param left The left member of the division (dividend)
     * @param right The right member of the division (divizor)
     * @return The quotient of the division */
    friend Sint operator/(Sint left, const Sint &right){return left /= right;}

    /** @brief Overload of the % operator for the Sint class
     * @param left The left member of the modulus (remainder)
     * @param right The right member of the modulus (divizor)
     * @return The result of the modulus */
    friend Sint operator%(Sint left, const Sint &right){return left %= right;}

    /** @brief Overload of the += operator for the Sint class
     * @param right The right member to add (Sint)
     * @return The Sint object after the addition */
    Sint &operator+=(const Sint &right);

    /** @brief Overload of the -= operator for the Sint class
     * @param right The right member to subtract (Sint)
     * @return The Sint object after the subtraction */
    Sint &operator-=(const Sint &right);

    /** @brief Overload of the *= operator for the Sint class
     * @param right The right member to multiply (Sint)
     * @return The Sint object after the multiplication */
    Sint &operator*=(const Sint &right);

    /** @brief Overload of the /= operator for the Sint class
     * @param right The right member (divizor) (Sint)
     * @return The Sint object after the division */
    Sint &operator/=(const Sint &right);

    /** @brief Overload of the %= operator for the Sint class
     * @param right The right member (divizor) (Sint)
     * @return The Sint object after the modulus */
    Sint &operator%=(const Sint &right);

    /** @brief Overload of the < operator for the Sint class
     * @param right The right member to compare with
     * @return true if  (left member) < (right member), false if not */
    bool operator<(const Sint &right) const { return cmp(*this, right) == -1; }

    /** @brief Overload of the <= operator for the Sint class
     * @param right The right member to compare with
     * @return true if  (left member) <= (right member), false if not */
    bool operator<=(const Sint &right) const { return cmp(*this, right) != 1; }

    /** @brief Overload of the > operator for the Sint class
     * @param right The right member to compare with
     * @return true if  (left member) > (right member), false if not */
    bool operator>(const Sint &right) const { return cmp(*this, right) == 1; }

    /** @brief Overload of the >= operator for the Sint class
     * @param right The right member to compare with
     * @return true if  (left member) >= (right member), false if not */
    bool operator>=(const Sint &right) const { return cmp(*this, right) != -1; }

    /** @brief Overload of the == operator for the Sint class
     * @param right The right member to compare with
     * @return true if  (left member) == (right member), false if not */
    bool operator==(const Sint &right) const { return cmp(*this, right) == 0; }

    /** @brief Overload of the != operator for the Sint class
     * @param right The right member to compare with
     * @return true if  (left member) != (right member), false if not */
    bool operator!=(const Sint &right) const { return cmp(*this, right) != 0; }

    /** @brief Overload of the cast operator (int64_t cast)
     * @return the cast Sint to int64_t */
    explicit operator int64_t() const;
};
#endif