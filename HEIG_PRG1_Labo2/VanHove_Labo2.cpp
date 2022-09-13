//File: 		VanHove_Labo2.cpp
//Author:		Timothée Van Hove
//Date:			22.09.2021
//Description:	Program that outputs the birth date relative to the age entered in input

#include <iostream>
#include <string>

using namespace std;

const int CURRENTYEAR = 2021;

int getBirthYear(int age, int currentYear)
{
	return currentYear - age;
}

int main()
{
	string name;
	int age;
	
	cout << "Enter yout name" << endl;
	 // getline() works only with string type and uses \n as default delimiter
	getline(cin, name);
	
	cout << "Enter yout age" << endl;
	// cin >> works with any types and uses any whitespace, \n or tabs as a delimiter
	cin >> age; 		
	
	cout << "Hello " << name << ", ";
	cout << "your age is " << age << " and you were born in " << getBirthYear(age, CURRENTYEAR) << endl;
	
	return EXIT_SUCCESS;
}
