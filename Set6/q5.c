//N queens using backtracking
#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int n;
int board[MAX];

int isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col)
            return 0;

        if (abs(board[i] - col) == abs(i - row))
            return 0;
    }

    return 1;
}

void solve(int row) {
    if (row == n) {
        for (int i = 0; i < n; i++)
            printf("%d ", board[i] + 1);
        printf("\n");
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            board[row] = col;
            solve(row + 1);
        }
    }
}

int main() {
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
        return 0;

    solve(0);

    return 0;
}