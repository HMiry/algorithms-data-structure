#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100


static void mat_copy (int [N][N], int [N][N], int);

/* parameters:
 * mat[N][N]: input matrix
 * matSize: matrix size
 * r, c: current row and current column
 * visitedBest[N][N]: best patch matrix
 * visited[N][N]: visited matrix
 * pathSumCurrent: current sum
 * pathLenCurrent: current path length
 * pathLenMax: max path length
 * pathLenCurrent: current path length
 */
//find the biigest or max paths visited in a mat if you found duplicates try the shorter path  
void path(
    int mat[N][N], int matSize, int r, int c, int visitedBest[N][N],
    int visited[N][N], int *pathSumMax, int pathSumCurrent, int *pathLenMax,
    int pathLenCurrent) {
    int dx[8] = {-1, -1, 0, 0, +1, +1, +1, -1};
    int dy[8] = {-1, 0, -1, +1, -1, 0, +1, +1};
    int i, v1, v2;


    // We are outside the matrix ... just return
    if (r<0 || r>=matSize || c<0 || c>=matSize) {
        return;
    }

    // We are on an element already visited ... just return
    if (visited[r][c]>0) {
        return;
    }

    // Compute new path cost sum and length
    v1 = pathSumCurrent + mat[r][c];
    v2 = pathLenCurrent + 1;

    // If we are on an ending cell
    if ((r==matSize-1) && (c==matSize-1)) {
        // Eventually update best cost/length
        if ( (v1>*pathSumMax) || ((v1==*pathSumMax) && (v2>*pathLenMax)) ) {
        *pathSumMax = v1;
        *pathLenMax = v2;
        mat_copy(visitedBest, visited, matSize);
        visitedBest[r][c] = *pathLenMax;
        }
    return;
    }
        // Mark element as visited
    visited[r][c] = v2;

    // Recur on all adjacent elements
    for (i=0; i<8; i++) {
        path(mat, matSize, r+dx[i], c+dy[i], visitedBest, visited,
             pathSumMax, v1, pathLenMax, v2);
    }

    // Unmark (backtrack)
    visited[r][c] = 0;
    
    return;
}

/* 
 * Copy current into best solution
 */
static void mat_copy (int m1[N][N], int m2[N][N], int n) {
    int r, c;
    for (r=0; r<n; r++) {
        for (c=0; c<n; c++) {
            m1[r][c] = m2[r][c];
        }
    }
    return;
}
     


     


//commented version 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

/* Function to copy one matrix into another
 * Parameters:
 * m1: destination matrix
 * m2: source matrix
 * n: size of the matrices
 */
static void mat_copy(int m1[N][N], int m2[N][N], int n) {
    int r, c;
    for (r = 0; r < n; r++) {
        for (c = 0; c < n; c++) {
            m1[r][c] = m2[r][c];  // Copy each element
        }
    }
}

/* Recursive function to find the path with the maximum sum in a matrix.
 * If there are paths with equal sum, the shortest path is chosen.
 *
 * Parameters:
 * mat[N][N]: The input matrix
 * matSize: Size of the matrix
 * r, c: Current row and column in the matrix
 * visitedBest[N][N]: Matrix to store the best path
 * visited[N][N]: Matrix to keep track of visited cells in the current path
 * pathSumMax: Pointer to store the maximum path sum
 * pathSumCurrent: Current path sum
 * pathLenMax: Pointer to store the length of the maximum path
 * pathLenCurrent: Current path length
 */
void path(
    int mat[N][N], int matSize, int r, int c, int visitedBest[N][N],
    int visited[N][N], int *pathSumMax, int pathSumCurrent, int *pathLenMax,
    int pathLenCurrent) {

    // Direction vectors for 8 possible movements
    int dx[8] = {-1, -1, 0, 0, +1, +1, +1, -1};
    int dy[8] = {-1, 0, -1, +1, -1, 0, +1, +1};

    // Check for boundary conditions
    if (r < 0 || r >= matSize || c < 0 || c >= matSize) {
        return; // Return if outside matrix
    }

    // Check if current cell is already visited
    if (visited[r][c] > 0) {
        return; // Return if cell is visited
    }

    // Update current path sum and length
    int newPathSum = pathSumCurrent + mat[r][c];
    int newPathLength = pathLenCurrent + 1;

    // Check for the ending cell (bottom-right corner of the matrix)
    if (r == matSize - 1 && c == matSize - 1) {
        // Update the best path if current path is better
        if (newPathSum > *pathSumMax || (newPathSum == *pathSumMax && newPathLength < *pathLenMax)) {
            *pathSumMax = newPathSum;
            *pathLenMax = newPathLength;
            mat_copy(visitedBest, visited, matSize); // Copy current path as best path
            visitedBest[r][c] = newPathLength; // Mark ending cell in best path
        }
        return;
    }

    // Mark the current cell as visited
    visited[r][c] = newPathLength;

    // Recursive calls for all 8 adjacent cells
    for (int i = 0; i < 8; i++) {
        path(mat, matSize, r + dx[i], c + dy[i], visitedBest, visited,
             pathSumMax, newPathSum, pathLenMax, newPathLength);
    }

    // Unmark the current cell (backtracking)
    visited[r][c] = 0;

    return; // End of the function
}
