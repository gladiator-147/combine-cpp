#include <iostream>
#include <vector>
using namespace std;

// Function to check if a queen can be placed at position (row, col)
bool isSafe(int row, int col, vector<vector<int>>& board, int N) {
    // Check the column
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1)
            return false;
    }

    // Check the left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1)
            return false;
    }

    // Check the right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}

// Backtracking function to solve the N-Queens problem
bool solveNQueens(vector<vector<int>>& board, int row, int N) {
    // If all queens are placed, return true
    if (row >= N)
        return true;

    // Try placing a queen in all columns one by one
    for (int col = 0; col < N; col++) {
        // Check if the queen can be placed safely
        if (isSafe(row, col, board, N)) {
            board[row][col] = 1; // Place the queen
            // Recur to place the next queen
            if (solveNQueens(board, row + 1, N))
                return true;
            // If placing queen in (row, col) doesn't work, backtrack
            board[row][col] = 0;
        }
    }

    return false; // If the queen cannot be placed in any column
}

// Function to print the chessboard
void printBoard(vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] == 1 ? "Q " : ". ");
        }
        cout << endl;
    }
}

// Main function to solve the N-Queens problem
int main() {
    int N = 4; // Number of queens
    vector<vector<int>> board(N, vector<int>(N, 0)); // Initialize an empty chessboard

    if (solveNQueens(board, 0, N)) {
        cout << "Solution found: \n";
        printBoard(board, N);
    } else {
        cout << "No solution exists!" << endl;
    }

    return 0;
}
