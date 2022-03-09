#ifndef UINT_HPP
#define UINT_HPP

#include<vector>
#include<string>

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
    int comp(const Uint &left, const Uint &right) const;

    /** @brief Erases the prefixed "0" of the internal value (iValue) */
    void eraseZero();

    /** @brief Gets the quotient and the remainder of a division
     * @param dividend The divident (left member)
     * @param divizor The divizor (right member)
     * @param rem Used as output for the remainder of the division
     * @return Uint The integer quotient of the division */
    Uint divAndRem(const Uint &dividend, const Uint &divizor, Uint &rem);

public:

    /** @brief Empty constructor */
    Uint();

    /** @brief String constructor
     * @param s The string used for the construction */
    Uint(const std::string &s);

    /** @brief uint64_t constructor
     * @param u The uint64_t used for the construction */
    Uint(uint64_t u);

    /** @brief Indicates if the Uint is even 
     * @return true if the Uint is even, false if not */
    bool isEven() const;

    /** @brief Get the number of digits of the Uint 
     * @return the number of digits of the Uint */
    uint32_t getSize() const;

    /** @brief Overload of the * operator for the Uint class 
     * @param left The left member of the multiplication
     * @param right The right member of the multiplication
     * @return The product of the multiplication */
    friend Uint operator*(uint32_t left, const Uint &right);

    /** @brief Overload of the << operator for the Uint class 
     * @param out The output stream (left member)
     * @param u The Uint value (right member)
     * @return The output stream containing the Uint value */
    friend std::ostream &operator<<(std::ostream &out, const Uint &u);

    /** @brief Overload of the + operator for the Uint class 
     * @param right The right member of the addition (Uint)
     * @return The result of the addition */
    Uint operator+(const Uint &right) const;

    /** @brief Overload of the - operator for the Uint class 
     * @param right The right member of the subtraction (Uint)
     * @return The difference of the subtration */
    Uint operator-(const Uint &right) const;

    /** @brief Overload of the * operator for the Uint class 
     * @param right The right member of the multiplication (Uint)
     * @return The product of the multiplication */
    Uint operator*(const Uint &right) const;

    /** @brief Overload of the * operator for the Uint class 
     * @param right The right member of the multiplication (uint32_t)
     * @return The product of the multiplication */
    Uint operator*(uint32_t right) const;

    /** @brief Overload of the / operator for the Uint class 
     * @param right The right member of the division (Uint)
     * @return The quotient of the division */
    Uint operator/(const Uint &right) const;

    /** @brief Overload of the / operator for the Uint class 
     * @param right The right member of the division (uint32_t)
     * @return The quotient of the division */
    Uint operator/(uint32_t right) const;

    /** @brief Overload of the % operator for the Uint class 
     * @param right The right member of the modulus (Uint)
     * @return The result of the modulus */
    Uint operator%(const Uint &right) const;

    /** @brief Overload of the % operator for the Uint class 
     * @param right The right member of the modulus (uint32_t)
     * @return The result of the modulus */
    Uint operator%(uint32_t right) const;

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
    bool operator<(const Uint &right) const;

    /** @brief Overload of the <= operator for the Uint class
     * @param right The right member to compare with
     * @return true if  (left member) <= (right member), false if not */
    bool operator<=(const Uint &right) const;

    /** @brief Overload of the > operator for the Uint class
     * @param right The right member to compare with
     * @return true if  (left member) > (right member), false if not */
    bool operator>(const Uint &right) const;

    /** @brief Overload of the >= operator for the Uint class
     * @param right The right member to compare with
     * @return true if  (left member) >= (right member), false if not */
    bool operator>=(const Uint &right) const;

    /** @brief Overload of the == operator for the Uint class
     * @param right The right member to compare with
     * @return true if  (left member) == (right member), false if not */
    bool operator==(const Uint &right) const;

    /** @brief Overload of the != operator for the Uint class
     * @param right The right member to compare with
     * @return true if  (left member) != (right member), false if not */
    bool operator!=(const Uint &right) const;
};

#endif