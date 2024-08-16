#include <stdio.h>

void chess(int **mat, int n, int m) {
    int r, c, rr, cc;
    int sum, max, rBest, cBest;
    
    max = rBest = cBest = (-1);
    for (r=0; r<n; r++) {
        for (c=0; c<m; c++) {
            if (mat[r][c] == 0) {
                sum = 0;
                // Move up-left
                for (rr=r, cc=c; rr>=0 && cc>=0; rr--, cc--) {
                    sum += mat[rr][cc];
                }
                // Move up-right
                for (rr=r, cc=c; rr>=0 && cc<n; rr--, cc++) {
                    sum += mat[rr][cc];
                }
                // Move down-left
                for (rr=r, cc=c; rr<n && cc>=0; rr++, cc--) {
                    sum += mat[rr][cc];
                }
                // Move down-right
                for (rr=r, cc=c; rr<n && cc<n; rr++, cc++) {
                    sum += mat[rr][cc];
                }
                // Update max and its coordinates
                if (sum>max) {
                    max = sum;
                    rBest = r;
                    cBest = c;
                }
            }
        }
    }
    
    fprintf(stdout, "Bishop coordinates (%d, %d) sum (%d)\n", rBest, cBest, max);
}


// this is for the knight if you want, you love me i know :)
#include <stdio.h>

#define N 8 // Change N to your desired chessboard size

void knight(int mat[N][N], int *r, int *c) {
    int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    int maxSum = -1;
    *r = -1;
    *c = -1;

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (mat[row][col] == 0) {
                int sum = 0;
                for (int move = 0; move < 8; move++) {
                    int newRow = row + dr[move];
                    int newCol = col + dc[move];
                    if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < N) {
                        sum += mat[newRow][newCol];
                    }
                }
                if (sum > maxSum) {
                    maxSum = sum;
                    *r = row;
                    *c = col;
                }
            }
        }
    }
}

int main() {
    int mat[N][N] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int r, c;
    knight(mat, &r, &c);

    printf("Knight coordinates (%d, %d) with the highest total value of %d in a single move.\n", r, c, mat[r][c]);

    return 0;
}
