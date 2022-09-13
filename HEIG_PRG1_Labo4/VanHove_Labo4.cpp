//File: 		        VanHove_Labo4.cpp
//Author:		        Timothee Van Hove
//Date:			        28.09.2021
//Description:	        Program that outputs the size (in bits) of a data type, and its min and max value
//[Compiler][options]:  [g++][-Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic -std=c++20]

#include <iostream>
#include <limits>
#include <string>

using namespace std;
using nl_uChar = numeric_limits<unsigned char>;
using nl_char = numeric_limits<char>;
using nl_uShort = numeric_limits<unsigned short>;
using nl_short = numeric_limits<short>;
using nl_uInt = numeric_limits<unsigned>;
using nl_int = numeric_limits<int>;
using nl_uLong = numeric_limits<unsigned long>;
using nl_long = numeric_limits<long>;
using nl_uLlong = numeric_limits<unsigned long long>;
using nl_llong = numeric_limits<long long>;
using nl_float = numeric_limits<float>;
using nl_double = numeric_limits<double>;
using nl_lDouble = numeric_limits<long double>;
const string SEPARATOR = " .. ";

//Output every datatype size in bits and min .. max values with numeric_limits class
int main()
{
    cout << "unsigned char " << " (" << nl_uChar::digits << " bits) "
         << (int)nl_uChar::min() << SEPARATOR << (int)nl_uChar::max() << endl;

    cout << "char " << " (" << nl_char::digits + 1 << " bits) "
         << (int)nl_char::min() << SEPARATOR << (int)nl_char::max() << endl;

    cout << "unsigned short " << " (" << nl_uShort::digits << " bits) "
         << nl_uShort::min() << SEPARATOR << nl_uShort::max() << endl;

    cout << "short " << " (" << nl_short::digits + 1 << " bits) "
         << nl_short::min() << SEPARATOR << nl_short::max() << endl;

    cout << "unsigned int " << " (" << nl_uInt::digits << " bits) "
         << nl_uInt::min() << SEPARATOR << nl_uInt::max() << endl;

    cout << "int " << " (" << nl_int::digits + 1 << " bits) "
         << nl_int::min() << SEPARATOR << nl_int::max() << endl;

    cout << "unsigned long " << " (" << nl_uLong::digits << " bits) "
         << nl_uLong::min() << SEPARATOR << nl_uLong::max() << endl;

    cout << "long "  << " (" << nl_long::digits + 1 << " bits) "
         << nl_long::min() << SEPARATOR << nl_long::max() << endl;

    cout << "unsigned long long " << " (" << nl_uLlong::digits << " bits) "
         << nl_uLlong::min() << SEPARATOR << nl_uLlong::max() << endl;

    cout << "long long " << " (" << nl_llong::digits + 1 << " bits) "
         << nl_llong::min() << SEPARATOR << nl_llong::max() << endl;

	// numeric_limits<float>::bits returns 24, but it is only the mantissa size
	// To get the actual size in bits, we have to use sizeof
    cout << "float " << " (" << sizeof(float) * CHAR_BIT << " bits) "
         << nl_float::min() << SEPARATOR << nl_float::max() << endl;

	// Mantissa + exp + sign bit
    cout << "double " << " (" << sizeof(double) * CHAR_BIT << " bits) "
         << nl_double::min() << SEPARATOR << nl_double::max() << endl;

	// Mantissa + exp + sign bit
    cout << "long double " << " (" << sizeof(long double) * CHAR_BIT << " bits) "
         << nl_lDouble::min() << SEPARATOR << nl_lDouble::max() << endl;

    return EXIT_SUCCESS;
}