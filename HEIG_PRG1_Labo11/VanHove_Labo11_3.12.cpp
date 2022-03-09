//File:           VanHove_Labo11_3.12.cpp
//Author:         Timothee Van Hove
//Date:           13.10.2021
//Description:    Program that calculate the mean value of 4 scores, and give an assessment

#include <iostream>
#include <iomanip>

using namespace std;

const double MIN = 4.0, AVERAGE = 4.5, GOOD = 5.0, VGOOD = 5.5;

const int SCORE_COUNT = 4.0, DECIMAL_PRECISION = 1;

int main()
{
    double result = 0.0;
    // User message
    cout << "Enter 4 scores between 1.0 and 6.0: ";

    // User input in a loop
    for (int i = 0; i < SCORE_COUNT; i++)
    {
        double score = 0.0;
        cin >> score;

        // Adds the entered score in the result variable
        result += score;
    }

    // Get the mean value of the 4 scores
    result /= SCORE_COUNT;

    // Output the suffix with the precision required
    cout << fixed << setprecision(DECIMAL_PRECISION) << "Mean = " << result;

    // Compare the values with the rating scale and give an assessment
    if (result < MIN)
        cout << " - Failed";

    else if (result <= AVERAGE)
        cout << " - Average";

    else if (result <= GOOD)
        cout << " - Good";

    else if (result <= VGOOD)
        cout << " - Very good!";

    else
        cout << " - Exceptionnal";

    return EXIT_SUCCESS;
}