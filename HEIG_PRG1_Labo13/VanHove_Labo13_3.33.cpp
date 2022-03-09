// File:        VanHove_Labo13_3.33.cpp
// Author:      Timothee Van Hove
// Date:        18.10.2021
// Description: Program that simulate the Monty Hall problem (3-doors game)
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <random>

using namespace std;

int DOOR_COUNT = 3, MIN_RANGE = 1;
char KEEP = 'k';

// The simulation of the 3-doors game
int main()
{
    int firstSelection = 0;
    cout << "Please select a door (1, 2, or 3)";
    cin >> firstSelection;

    // Obtain a random number from hardware
    random_device rd;

    // Seed the generator
    mt19937 gen(rd());

    // Define the range
    uniform_int_distribution<int> distr(MIN_RANGE, DOOR_COUNT);

    // Generate random Winning door
    int prizeDoor = distr(gen);

    int openedDoor = 0;

    do // The presenter opens a door randomly (if the prize is behind the chosen door)
        openedDoor = distr(gen);
    while (openedDoor == firstSelection || openedDoor == prizeDoor);

    // The presenter cannot open the prize door
    if (prizeDoor == openedDoor)
        openedDoor = prizeDoor % DOOR_COUNT + 1;

    // The door the user can change with for the second selection
    int secondSelection = openedDoor % DOOR_COUNT + 1;

    // So the modulo must not return the same door as the first choice
    if (firstSelection == secondSelection)
        secondSelection = firstSelection % DOOR_COUNT + 1;

    // User message with the offer to change the door
    cout << "You have chosen the door #" << firstSelection << "." << endl;
    cout << "The presenter opens the door #" << openedDoor << ". A goat is shown." << endl;
    cout << "Type k to keep your choice, c to change for the door #" << secondSelection << endl;
    char choice = 0;
    cin >> choice;

    if (choice == KEEP)
        secondSelection = firstSelection;

    if (secondSelection == prizeDoor)
        cout << "You won the prize!";
    else
        cout << "You loose!";

    return 1;
}

// // The Program that calculates the probability of winning if you change the initial door
// int main()
// {
//     int winCount = 0, loseCount = 0;

//     // Obtain a random number from hardware
//     random_device rd;

//     // Seed the generator
//     mt19937 gen(rd());

//     // Define the range
//     uniform_int_distribution<int> distr(MIN_RANGE, DOOR_COUNT);

//     // Simulation for 1'000'000 times if the player change his choice after the door has been opened
//     for (size_t i = 0; i < 1'000'000; i++)
//     {
//         // Generate random selected door
//         int firstSelection = distr(gen);

//         // Generate random Winning door
//         int prizeDoor = distr(gen);

//         int openedDoor = 0;

//         do // The presenter opens a door randomly (if the prize is behind the chosen door)
//             openedDoor = distr(gen);
//         while (openedDoor == firstSelection || openedDoor == prizeDoor);

//         // The player changes the door selection
//         int secondSelection = openedDoor % DOOR_COUNT + 1;

//         // The modulo must not return the same door as the first choice
//         if (firstSelection == secondSelection)
//             secondSelection = firstSelection % DOOR_COUNT + 1;

//         // The player wins if the last selected door is the winning door defined in the beginning
//         if (secondSelection == prizeDoor)
//             winCount++; // The player has won, increase the win counter
//         else
//             loseCount++; // The player has lost, increase the lose counter
//     }

//     // Get the probability
//     double winChances = winCount / 10'000.0;

//     // User message with results
//     cout << "The winning probability is " << winChances << "% if the user changes his choice";
//     return 1;
// }
