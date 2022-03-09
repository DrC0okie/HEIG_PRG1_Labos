//File:           VanHove_Labo11_3.11.cpp
//Author:         Timothee Van Hove
//Date:           13.10.2021
//Description:    Program that determines if the entered value is a multiple of 3, 5, both or none

#include <iostream>

using namespace std;

const int MOD_3 = 3, MOD_5 = 5;

int main()
{
   int number = 0;
   cout << "Please enter a positive number" << endl;
   cin >> number;

   // Get the result of the modulo
   bool multiple3 = !(number % MOD_3);
   bool multiple5 = !(number % MOD_5);

   // Prefix of the user output message
   cout << number;

   // Test if the value is a multiple of 3, 5 or not
   if (multiple3 && multiple5)
      cout << " is a multiple of 3 and 5";

   else if (multiple3)
      cout << " is a multiple of 3";

   else if (multiple5)
      cout << " is a multiple of 5";

   else
      cout << " is not a multiple of 3 nor 5";

   return EXIT_SUCCESS;
}
