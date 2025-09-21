#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
using namespace std;

int main() {
    srand(time(0)); // Seed the random number generator

    int userChoice;

    cout << "Choose: 0 for Rock, 1 for Paper, 2 for Scissors: ";
    cin >> userChoice;

    int computerChoice = rand() % 3; // Generates 0, 1, or 2

    cout << "User chose: " << userChoice << endl;
    cout << "Computer chose: " << computerChoice << endl;

    if (userChoice == computerChoice) {
        cout << "It's a tie!" << endl;
    } else if ((userChoice == 0 && computerChoice == 2) || // Rock beats Scissors
               (userChoice == 1 && computerChoice == 0) || // Paper beats Rock
               (userChoice == 2 && computerChoice == 1)) { // Scissors beat Paper
        cout << "You win!" << endl;
    } else {
        cout << "Computer wins!" << endl;
    }
}