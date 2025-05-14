#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int board[MAX];  // board[i] stores column position of queen in row i
int solutionCount = 0;  

// Check if placing queen at (row, col) is safe
int isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return 0; // Not safe
    }
    return 1; // Safe
}

// Print the current board configuration
void printSolution(int n) {
    solutionCount++;
    printf("Solution %d:\n", solutionCount);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

// Solve N-Queens using backtrackings
void solveNQueens(int row, int n) {
    if (row == n) {
        printSolution(n);  // Valid solution found
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            board[row] = col;         // Place queen
            solveNQueens(row + 1, n); // Recurse for next row
            // No need to undo assignment, as it'll be overwritten
        }
    }
}

int main() {
    int n;
    printf("Enter the value of N (chessboard size): ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid input. Please enter N between 1 and %d.\n", MAX);
        return 1;
    }

    solveNQueens(0, n);

    if (solutionCount == 0)
        printf("No solution exists for N = %d\n", n);
    else
        printf("Total solutions found: %d\n", solutionCount);

    return 0;
}