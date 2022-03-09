// File:        Uint.hpp
// Author:      Timothee Van Hove
// Date:        15.01.2022
// Description: Header of the Uint class

#ifndef UINT_HPP
#define UINT_HPP

#include <vector>
#include <string>

const uint32_t GETNUM = 48, BASE = 10;

class Uint
{
private:
    /** @brief The internal value used to reprensent a number*/
    std::vector<uint32_t> iValue;

    /** @brief Distributes each digit of a number in iValue to the next cells
     *  @return The distrubuted Uint */
    Uint &carry();

    /** @brief Compares if the left Uint is <, >, or ==
     * @param left The left Uint
     * @param right The right Uint
     * @return 1 if left < right, -1 if left > right and 0 if left == right */
    int cmp(const Uint &left, const Uint &right) const;

    /** @brief Erases the prefixed "0" of the internal value (iValue) */
    Uint& eraseZero();

    /** @brief Checks if the Uint is zero and trhow an exception
     * @details Used for the division and modulo 
     * @param number The number to check*/
    void checkZero(const Uint& number) const;

    /** @brief Checks if the uint64_t is zero and trhow an exception
     * @details Used for the division and modulo
     * @param number The number to check*/
    void checkZero(uint32_t number) const;

    /** @brief Gets the quotient and the remainder of a division
     * @param dividend The divident (left member)
     * @param divizor The divizor (right member)
     * @param rem Used as output for the remainder of the division
     * @return Uint The integer quotient of the division */
    Uint divAndRem(const Uint &dividend, const Uint &divizor, Uint &rem);

public:
    /** @brief Empty constructor */
    Uint(){}

    /** @brief String constructor
     * @param str The string used for the construction */
    Uint(const std::string &str);

    /** @brief uint64_t constructor
     * @param u The uint64_t used for the construction */
    Uint(uint64_t number) { *this = std::to_string(number); }

    /** @brief Tells if the Uint is zero or not
     * @return true if the Uint == 0, flse if not*/
    bool isZero() const { return (getSize() == 1 && iValue.front() == 0); }

    /** @brief Indicates if the Uint is even
     * @return true if the Uint is even, false if not */
    bool isEven() const { return (iValue.front() % 2) == 0; }

    /** @brief Get the number of digits of the Uint
     * @return the number of digits of the Uint */
    size_t getSize() const { return iValue.size(); }

    /** @brief Declare Sint as a friend classe, so it can access private data */
    friend class Sint;
    
    /** @brief Modular exponentiation
     * @details The base is a long long type to avoid overflows
     * @param base The base
     * @param exp  The exponent
     * @param mod The modulus
     * @return The result of modular exponentiation */
    friend Uint mod_pow(Uint base, Uint exp, const Uint &mod);

    /** @brief Overload of the << operator for the Uint class
     * @param os The output stream (left member)
     * @param u The Uint value (right member)
     * @return The output stream containing the Uint value */
    friend std::ostream &operator<<(std::ostream &os, const Uint &u);

    /** @brief Overload of the >> operator for the Uint class
     * @param is The input stream (left member)
     * @param u The Uint value (right member)
     * @return The input stream containing the Uint value */
    friend std::istream &operator>>(std::istream &is, Uint &u);

    /** @brief Overload of the + operator for the Uint class
     * @param left  The left member of the addition
     * @param right The right member of the addition
     * @return The result of the addition */
    friend Uint operator+(Uint left, const Uint &right){return left += right;}

    /** @brief Overload of the - operator for the Uint class
     * @param left The left member of the substraction
     * @param right The right member of the subtraction
     * @return The difference of the subtration */
    friend Uint operator-(Uint left, const Uint &right){return left -= right;}

    /** @brief Overload of the * operator for the Uint class
     * @param left The left member of the multiplication
     * @param right The right member of the multiplication
     * @return The product of the multiplication */
    friend Uint operator*(Uint left, const Uint &right){return left *= right;}

    /** @brief Overload of the * operator for the Uint class
     * @param left The left member of the multiplication
     * @param right The right member of the multiplication
     * @return The product of the multiplication */
    friend Uint operator*(uint32_t left, const Uint &right){return right * left;}

    /** @brief Overload of the * operator for the Uint class
     * @param left The left member of the multiplication
     * @param right The right member of the multiplication
     * @return The product of the multiplication */
    friend Uint operator*(Uint left, const uint32_t right){return left *= right;}

    /** @brief Overload of the / operator for the Uint class
     * @param left The left member of the division (dividend)
     * @param right The right member of the division (divizor)
     * @return The quotient of the division */
    friend Uint operator/(Uint left, const Uint &right){return left /= right;}

    /** @brief Overload of the / operator for the Uint class
     * @param left The left member of the division (dividend)
     * @param right The right member of the division (divizor)
     * @return The quotient of the division */
    friend Uint operator/(Uint left, const uint32_t right){return left /= right;}

    /** @brief Overload of the % operator for the Uint class
     * @param left The left member of the modulus (remainder)
     * @param right The right member of the modulus (divizor)
     * @return The result of the modulus */
    friend Uint operator%(Uint left, const Uint &right){return left %= right;}

    /** @brief Overload of the % operator for the Uint class
     * @param left The left member of the modulus (remainder)
     * @param right The right member of the modulus (divizor)
     * @return The result of the modulus */
    friend Uint operator%(Uint left, const uint32_t right){return left %= right;}

    /** @brief Overload of the prefixed ++ operator for the Uint class
     * @return The Uint object before the increment */
    Uint operator++(int);

    /** @brief Overload of the postfixed ++ operator for the Uint class
     * @return The incremented Uint object */
    Uint &operator++();

    /** @brief Overload of the prefixed -- operator for the Uint class
     * @return The Uint object before the decrement */
    Uint operator--(int);

    /** @brief Overload of the postfixed -- operator for the Uint class
     * @return The decremented Uint object */
    Uint &operator--();

    /** @brief Overload of the += operator for the Uint class
     * @param right The right member to add (Uint)
     * @return The Uint object after the addition */
    Uint &operator+=(const Uint &right);

    /** @brief Overload of the -= operator for the Uint class
     * @param right The right member to subtract (Uint)
     * @return The Uint object after the subtraction */
    Uint &operator-=(const Uint &right);

    /** @brief Overload of the *= operator for the Uint class
     * @param right The right member to multiply (Uint)
     * @return The Uint object after the multiplication */
    Uint &operator*=(const Uint &right);

    /** @brief Overload of the *= operator for the Uint class
     * @param right The right member to multiply (uint32_t)
     * @return The Uint object after the multiplication */
    Uint &operator*=(uint32_t right);

    /** @brief Overload of the /= operator for the Uint class
     * @param right The right member (divizor) (Uint)
     * @return The Uint object after the division */
    Uint &operator/=(const Uint &right);

    /** @brief Overload of the /= operator for the Uint class
     * @param right The right member (divizor) (uint32_t)
     * @return The Uint object after the division */
    Uint &operator/=(uint32_t right);

    /** @brief Overload of the %= operator for the Uint class
     * @param right The right member (divizor) (Uint)
     * @return The Uint object after the modulus */
    Uint &operator%=(const Uint &right);

    /** @brief Overload of the %= operator for the Uint class
     * @param right The right member (divizor) (uint32_t)
     * @return The Uint object after the modulus */
    Uint &operator%=(uint32_t right);

    /** @brief Overload of the < operator for the Uint class
     * @param right The right member to compare with
     * @return true if  (left member) < (right member), false if not */
    bool operator<(const Uint &right) const {return cmp(*this, right) == -1;}

    /** @brief Overload of the <= operator for the Uint class
     * @param right The right member to compare with
     * @return true if  (left member) <= (right member), false if not */
    bool operator<=(const Uint &right) const {return cmp(*this, right) != 1;}

    /** @brief Overload of the > operator for the Uint class
     * @param right The right member to compare with
     * @return true if  (left member) > (right member), false if not */
    bool operator>(const Uint &right) const {return cmp(*this, right) == 1;}

    /** @brief Overload of the >= operator for the Uint class
     * @param right The right member to compare with
     * @return true if  (left member) >= (right member), false if not */
    bool operator>=(const Uint &right) const {return cmp(*this, right) != -1;}

    /** @brief Overload of the == operator for the Uint class
     * @param right The right member to compare with
     * @return true if  (left member) == (right member), false if not */
    bool operator==(const Uint &right) const {return cmp(*this, right) == 0;}

    /** @brief Overload of the != operator for the Uint class
     * @param right The right member to compare with
     * @return true if  (left member) != (right member), false if not */
    bool operator!=(const Uint &right) const {return cmp(*this, right) != 0;}

    /** @brief Overload of the cast operator (uint64_t cast)
     * @return the cast Uint to uint64_t */
    explicit operator uint64_t() const;
};

#endif