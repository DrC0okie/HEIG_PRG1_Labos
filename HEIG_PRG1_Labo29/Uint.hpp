#ifndef UINT_HPP
#define UINT_HPP

#include<vector>
#include<string>

const uint32_t GETNUM = 48;

class Uint
{
private:
    std::vector<uint32_t> iValue;
    Uint &carry();
    int comp(const Uint &left, const Uint &right) const;
    Uint &eraseZero();

public:
    Uint();
    Uint(std::string s);
    Uint(uint64_t);

    friend Uint operator*(uint32_t left, const Uint &right);
    friend std::ostream &operator<<(std::ostream &out, const Uint &u);

    Uint operator+(const Uint &right) const;
    Uint operator-(const Uint &right) const;
    Uint operator*(const Uint &right) const;
    Uint operator*(uint32_t right) const;
    Uint operator++(int);
    Uint &operator++();
    Uint &operator+=(const Uint &right);
    Uint &operator-=(const Uint &right);
    Uint &operator*=(const Uint &right);
    Uint &operator*=(uint32_t right);

    bool operator<(const Uint &right) const;
    bool operator<=(const Uint &right) const;
    bool operator>(const Uint &right) const;
    bool operator>=(const Uint &right) const;
    bool operator==(const Uint &right) const;
    bool operator!=(const Uint &right) const;
};

#endif