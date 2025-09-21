#include <iostream>  // Include standard input/output library
using namespace std;

// Global variables for the game board and players
char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};  // The game board
char currentMarker;  // Current player's marker (X or O)
int currentPlayer;   // Current player (1 or 2)

// Function to draw the current state of the board
void drawBoard() {
    cout << "\n";  // Add a blank line for better readability
    for (int i = 0; i < 3; i++) {  // Loop through rows
        for (int j = 0; j < 3; j++) {  // Loop through columns
            cout << " " << board[i][j] << " ";  // Print the slot value
            if (j < 2) cout << "|";  // Add a vertical separator between columns
        }
        cout << "\n";  // End the row
        if (i < 2) cout << "---|---|---\n";  // Add a horizontal separator between rows
    }
    cout << "\n";  // Add a blank line after the board
}

// Function to place a marker on the board
bool placeMarker(int slot) {
    // Convert slot number to row and column
    int row = (slot - 1) / 3;  // Row index (0-2)
    int col = (slot - 1) % 3;  // Column index (0-2)

    // Check if the slot is already taken
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentMarker;  // Place the current player's marker
        return true;  // Indicate success
    }
    return false;  // Indicate failure (slot already taken)
}

// Function to check if there is a winner
int checkWinner() {
    // Check rows for a win
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) 
            return currentPlayer;  // Return the current player (0,1)as the winner
    }

    // Check columns for a win
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) 
            return currentPlayer;  // Return the current player(0,1) as the winner
    }

    // Check diagonals for a win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) 
        return currentPlayer;  // Return the current player(0,1) as the winner
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) 
        return currentPlayer;  // Return the current player(0,1) as the winner

    return 0;  // No winner yet
}

// Function to switch the current player and their marker
void swapPlayerAndMarker() {
    if (currentMarker == 'X') {  // If the current marker is X
        currentMarker = 'O';  // Change to O
        currentPlayer = 2;  // Switch to player 2
    } else {  // If the current marker is O
        currentMarker = 'X';  // Change to X
        currentPlayer = 1;  // Switch to player 1
    }
}

// Main game function
void game() {
    // Prompt player 1 to choose a marker
    cout << "Welcome to Tic Cross Game!\n";
    cout << "Player 1, choose your marker (X or O): ";
    cin >> currentMarker;

    // Set the first player based on their marker choice
    currentPlayer = (currentMarker == 'X') ? 1 : 2;

    drawBoard();  // Display the initial board

    int winner = 0;  // Variable to store the winner (0 means no winner yet)
    int slot;  // Variable to store the slot chosen by the player

    // Loop for up to 9 turns (maximum moves in Tic Tac Toe)
    for (int i = 0; i < 9 && winner == 0; i++) {
        // Ask the current player to choose a slot
        cout << "Player " << currentPlayer << ", enter your slot (1-9): ";
        cin >> slot;

        // Validate the slot and attempt to place the marker
        if (slot < 1 || slot > 9 || !placeMarker(slot)) {
            cout << "Invalid slot! Try again.\n";
            i--;  // Decrement the turn counter to allow retry
            continue;  // Skip to the next iteration
        }

        drawBoard();  // Display the updated board
        winner = checkWinner();  // Check for a winner

        if (winner == 0) swapPlayerAndMarker();  // Switch turns if no winner yet
    }

    // Display the result
    if (winner != 0) {
        cout << "Congratulations! Player " << winner << " wins!\n";
    } else {
        cout << "It's a tie!\n";  // All slots are filled with no winner
    }
}

// Main function
int main() {
    game();  // Start the game
    return 0;  // Exit the program
}