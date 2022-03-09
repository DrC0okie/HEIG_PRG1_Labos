//File: 		VanHove_Labo2.cpp
//Author:		Timothée Van Hove
//Date:			22.09.2021
//Description:	Program that outputs the birth date relative to the age entered in input

#include <iostream>
#include <string>
#include <cstdio>		// Used to pause the console with getchar()

using namespace std;

const int CURRENTYEAR = 2021;

int GetBirthYear(int age, int currentYear)
{
	return currentYear - age;
}

void pause()
{
	cout << "Press ENTER to exit.";
	getchar();
	getchar();
}

int main()
{
	string name = "";
	int age = 0;
	cout << "Enter yout name" << endl;
	getline(cin, name); // getline() works only with string type and uses \n as default delimiter
	cout << "Enter yout age" << endl;
	cin >> age; 		// cin >> works with any types and uses any whitespace, \n or tabs as a delimiter
	cout << "Hello " << name << ", ";
	cout << "your age is " << age << " and you were born in " << GetBirthYear(age, CURRENTYEAR) << endl;
	pause();
	return EXIT_SUCCESS;
}
