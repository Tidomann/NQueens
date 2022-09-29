//
// main.cpp
//
// Created by Jordan Tiedemann on 2022-09-28
//
//

#include <iostream>
#include <vector>
#include <limits>

using std::cout;
using std::cin;
using std::string;
using std::vector;

int getN();
string chessNotation(int row, int col);
bool checkSolution(bool board[14][14], int size);
int placeQueens(bool board[14][14], int size);
bool moveQueen(bool board[14][14], int size);

int main() {
    //Generate Statically Sized Array of Size 14x14
    bool board[14][14];
    //Initialize All array positions to false
    for(int i = 0; i < 14; ++i){
        for(int j = 0; j < 14; ++j){
            board[i][j] = false;
        }
    }

    int size = getN();

    int solutions = placeQueens(board, size);
    cout << "Total Solutions Found for " << size << "x" << size << " board: " << solutions << '\n';

    return 0;
}



//
// function:    getN()
//
// This function prompts the user for a numeric value
// Validates that the input entered is an integer variable and is strictly greater than 0 and less than 14
// Otherwise clear the error state and flush the input data to re-prompt the user
//
int getN() {
    unsigned short int N;			// Declare N
    // Prompt user for N value until valid
    do {
        cout << "Enter a number N between 1 and 14: ";
        if (!(cin >> N)) { // If input from console fails
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // Ignore all characters entered, new line
        }
    } while (N < 1 || N > 14); // Only exit loop when valid input is given
    return N;

}

//
// Function:    chessNotation()
//
// This function will take in two integers representing array positions on a 2d integer array board
// and return the position in chess notation. The function only works on chess boards where the number of
// columns does not exceed a single letter character. E.g. after column Z, the function will not accept
// a board with column AA
//
string chessNotation(int row, int col){
    //
    if(col > 25){
        return "Error: Column Past Z";
    }
    char letter = (char)65+col;
    string result;
    result.push_back(letter);
    result = result + std::to_string(row+1);
    return result;
}

//
// Function:    checkPosition()
//
// This function will test the board to ensure the positions of the queens are valid.
// Each vector stores values corresponding to see if the row/col/diagonals are occupied.
// We use the unique property that diagonals of the board have a relationship between the sum and difference of
// the array indexes
//
bool checkSolution(bool board[14][14], int size){
    vector<int> rowCheck;
    vector<int> colCheck;
    vector<int> backSlashDiagonal;
    vector<int> forwardSlashDiagonal;

    int queensFound = 0;

    // Iterate through the board to find each queen
    for(int row = 0; row < size; ++row){
        for(int col = 0; col < size; ++col){

            // Test If a Queen is at the location
            if(board[row][col]){
                ++queensFound;

                // Once we find a queen, check if there already exists a queen in the row, column, or diagonals
                for(int rowCompare : rowCheck) {
                    if (row == rowCompare)
                        return false;
                }
                for(int colCompare : colCheck) {
                    if (col == colCompare)
                        return false;
                }
                for(int diagCompare : backSlashDiagonal) {
                    if ((row + col) == diagCompare)
                        return false;
                }
                for(int diagCompare : forwardSlashDiagonal) {
                    if ((row - col) == diagCompare)
                        return false;
                }

                // Queen position is valid. We must mark the row, column, and diagonals as occupied.
                rowCheck.push_back(row);
                colCheck.push_back(col);
                backSlashDiagonal.push_back(row+col);
                forwardSlashDiagonal.push_back(row-col);
            }
        }
    }
    // We have iterated through the entire board, and all queens found have valid positions
    // Will return true if we have found the correct number of valid queens
    return queensFound == size;
}

//
// Function:    placeQueen()
// This function places a queen in the NxN Board (a 2D array), and iterates through all possibilities
// Because a valid solution must have a queen in every row, we can start with a queen populating the entire
// first column. We can then move the queen in the first row until every position has been tried. When every position
// has been tested,
int placeQueens(bool board[14][14], int size) {
    int solutions = 0;
    // Place the queens along the first column
    for(int row = 0; row < size; ++row){
        board[row][0] = true;
    }
    //Continue moving queens row by row to test all column iterations until the queens can no longer be moved
    do{
        if(checkSolution(board, size)){
            ++solutions;
            cout << "Solution #" << solutions << ": ( ";
            for(int row = 0; row < size; ++row){
                for(int col = 0; col < size; ++ col){
                    if(board[row][col]){
                        cout << chessNotation(row, col) << " ";
                    }
                }
            }
            cout << ")\n";
        }
    }while(moveQueen(board, size));
    // Return the total number of solutions

    return solutions;
}

//
// Function:    moveQueen()
// This function returns true if it is able to move a queen down a column.
// By iterating through the board it can meet a return condition early if it is able to move a queen down the column
// If a queen reaches the final column of the chess board, and we can still test another row, we reset the queen in that
// row and all previous rows back to the initial column and iterate to the next row.
// This process is repeated until a queen can be moved and we return true,
// or we iterate to the final row and all queens were found to be in the final column.
bool moveQueen(bool board[14][14], int size){
    for(int row = 0; row < size; ++row){
        for(int col = 0; col < size; ++ col){

            if(board[row][col]){ // A queen occupies the location

                if(col+1 < size){ // The queen can move right to a new column
                    board[row][col] = false; // Pick up the queen
                    board[row][col+1] = true; // Place the queen in the new column
                    return true;
                }
                else{ // The found queen is at the end of column
                    if(row+1 < size){ // Test to see if we can search the next row

                        // If a new row can be tested, reset this row back to the starting column
                        // and allow the function to iterate to the next row to see if a queen can be moved
                        board[row][col] = false;
                        board[row][0] = true;

                    }
                } //end else

            }//end if queen occupies location

        }//column for loop
    }//row for loop
    return false; // Iterated through the entire board and all queens were in the final column
}
