//File: 		        VanHove_Labo4.cpp
//Author:		        Timothee Van Hove
//Date:			        28.09.2021
//Description:	        Program that outputs the size (in bits) of a data type, and its min and max value
//[Compiler][options]:  [g++][-Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic -std=c++20]

#include <iostream>
#include <numeric>
#include <string>

using namespace std;

const string SEPARATOR = " .. "; //Separator between min and max values

//Output every datatype size in bits and min .. max values with numeric_limits class
int main()
{
    
    cout << "Unsigned char "
         << " (" << std::numeric_limits<unsigned char>::digits << " bits) "
         << (int)std::numeric_limits<unsigned char>::min()
         << SEPARATOR
         << (int)std::numeric_limits<unsigned char>::max() << endl;

    cout << "Char "
         << " (" << std::numeric_limits<char>::digits + 1 << " bits) "
         << (int)std::numeric_limits<char>::min()
         << SEPARATOR
         << (int)std::numeric_limits<char>::max() << endl;

    cout << "Unsigned short "
         << " (" << numeric_limits<unsigned short>::digits << " bits) "
         << numeric_limits<unsigned short>::min()
         << SEPARATOR
         << numeric_limits<unsigned short>::max() << endl;

    cout << "Short "
         << " (" << numeric_limits<short>::digits + 1 << " bits) "
         << std::numeric_limits<short>::min()
         << SEPARATOR
         << std::numeric_limits<short>::max() << endl;

    cout << "Unsigned int "
         << " (" << numeric_limits<unsigned int>::digits << " bits) "
         << std::numeric_limits<unsigned int>::min()
         << SEPARATOR
         << std::numeric_limits<unsigned int>::max() << endl;

    cout << "Int "
         << " (" << numeric_limits<int>::digits + 1 << " bits) "
         << std::numeric_limits<int>::min()
         << SEPARATOR
         << std::numeric_limits<int>::max() << endl;

    cout << "Unsigned long "
         << " (" << numeric_limits<unsigned long>::digits << " bits) "
         << std::numeric_limits<unsigned long>::min()
         << SEPARATOR
         << std::numeric_limits<unsigned long>::max() << endl;

    cout << "Long "
         << " (" << numeric_limits<long>::digits + 1 << " bits) "
         << std::numeric_limits<long>::min()
         << SEPARATOR
         << std::numeric_limits<long>::max() << endl;

    cout << "Unsigned long long "
         << " (" << numeric_limits<unsigned long long>::digits << " bits) "
         << std::numeric_limits<unsigned long long>::min()
         << SEPARATOR
         << std::numeric_limits<unsigned long long>::max() << endl;

    cout << "Long long "
         << " (" << numeric_limits<long long>::digits + 1 << " bits) "
         << std::numeric_limits<long long>::min()
         << SEPARATOR
         << std::numeric_limits<long long>::max() << endl;

    cout << "Float "
         << " (" << numeric_limits<float>::digits << " bits) "
         << std::numeric_limits<float>::min()
         << SEPARATOR
         << std::numeric_limits<float>::max() << endl;

    cout << "Double "
         << " (" << numeric_limits<double>::digits << " bits) "
         << std::numeric_limits<double>::min()
         << SEPARATOR
         << std::numeric_limits<double>::max() << endl;

    cout << "Long double "
         << " (" << numeric_limits<long double>::digits << " bits) "
         << std::numeric_limits<long double>::min()
         << SEPARATOR
         << std::numeric_limits<long double>::max() << endl;

    cout << "Hit enter to exit..." << endl;
    getchar();

    return EXIT_SUCCESS;
}