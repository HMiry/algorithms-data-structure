#include <stdio.h>
#include <stdlib.h>

int **malloc2d(int, int);
void free2d(int **, int);
int *file_read(char *, int *);
void matrix_write(int **, int);
static int matrix_check(int **, int *, int, int, int);
int matrix_swap(int **, int, int *, int, int, int);

int main(int argc, char *argv[]) {
    int n, N, k, found;
    int **mat, *sol;

    mat = file_read(argv[1], &n);
    found = 0;

    N = 2 * n;
    sol = (int *)calloc(N, sizeof(int));
    if (sol == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Initial Matrix:\n");
    matrix_write(mat, n);

    for (k = 1; k <= N && found == 0; k++) {
        if (matrix_swap(mat, N, sol, 0, k, 0)) {
            found = 1;
        }
    }

    if (found == 0) {
        fprintf(stdout, "No solution found.\n");
    }

    free(sol);
    free2d(mat, n);

    return 0;
}

int **file_read(char *name, int *n) {
    int i, j, **mat;
    FILE *fp;

    fp = fopen(name, "r");
    if (fp == NULL) {
        fprintf(stderr, "File open error.\n");
        exit(EXIT_FAILURE);
    }
    fscanf(fp, "%d", n);

    mat = malloc2d(*n, *n);
    for (i = 0; i < *n; i++) {
        for (j = 0; j < *n; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }

    fclose(fp);
    return mat;
}

void matrix_write(int **m, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fprintf(stdout, "%d ", m[i][j]);
        }
        fprintf(stdout, "\n");
    }
    return;
}

int **malloc2d(int r, int c) {
    int i;
    int **mat;

    mat = (int **)malloc(r * sizeof(int *));
    if (mat == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < r; i++) {
        mat[i] = (int *)malloc(c * sizeof(int));
        if (mat[i] == NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
    }
    return mat;
}

void free2d(int **mat, int r) {
    int i;
    for (i = 0; i < r; i++) {
        free(mat[i]);
    }
    free(mat);
    return;
}

int matrix_swap(int **mat, int N, int *sol, int pos, int k, int start) {
    int i, n;

    // ... Code for matrix_swap function is not shown completely ...

    n = N / 2;
    if (pos > k) {
        if (matrix_check(mat, sol, n, k)) {
            fprintf(stdout, "Solution:\n");
            for (i = 0; i < k; i++) {
                if (sol[i] < n) {
                    fprintf(stdout, "Row=%d ", sol[i]);
                } else {
                    fprintf(stdout, "Column=%d ", sol[i] - n);
                }
            }
            fprintf(stdout, "\n");
            return 1;
        } else {
            return 0;
        }
    }

    // ... Rest of the code for matrix_swap function is not shown ...

    for (i = start; i < N; i++) {
        sol[pos] = i;
        if (matrix_swap(mat, N, sol, pos + 1, k, i + 1)) {
            return 1;
        }
    }

    return 0;
}

static int matrix_check(int **mat, int *sol, int n, int k) {
    int i, j, ok, **flipMat;

    flipMat = malloc2d(n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            flipMat[i][j] = mat[i][j];
        }
    }

    for (i = 0; i < k; i++) {
        if (sol[i] < n) {
            for (j = 0; j < n; j++) {
                flipMat[sol[i]][j] = (flipMat[sol[i]][j] + 1) % 2;
            }
        } else {
            for (j = 0; j < n; j++) {
                flipMat[j][sol[i] - n] = (flipMat[j][sol[i] - n] + 1) % 2;
            }
        }
    }

    ok = 1;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            ok &= flipMat[i][j];
        }
    }

    free2d(flipMat, n);

    return ok;
}
