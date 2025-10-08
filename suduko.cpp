#include <iostream>
using namespace std;

#define N 9  // Sudoku size

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

// Check if it is safe to put num in grid[row][col]
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check row
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num)
            return false;
    }

    // Check column
    for (int x = 0; x < N; x++) {
        if (grid[x][col] == num)
            return false;
    }

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Recursive function to solve Sudoku
bool solveSudoku(int grid[N][N], int row, int col) {
    // If we reached the end of the grid, puzzle solved
    if (row == N - 1 && col == N)
        return true;

    // Move to next row if at end of column
    if (col == N) {
        row++;
        col = 0;
    }

    // Skip already filled cells
    if (grid[row][col] != 0)
        return solveSudoku(grid, row, col + 1);

    // Try digits 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively proceed
            if (solveSudoku(grid, row, col + 1)){
                return true;
            }
        }

        // Backtrack
        grid[row][col] = 0;
    }

    // Trigger backtracking
    return false;
}

int main() {
    // 0 represents empty cells
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Original Sudoku:\n";
    printGrid(grid);

    if (solveSudoku(grid, 0, 0)) {
        cout << "\nSolved Sudoku:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
