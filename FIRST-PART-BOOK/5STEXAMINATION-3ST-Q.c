#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define N 3

void file_read(FILE *, char ***, int *);
void play(FILE *, char **, int, char *, int);

int main(int argc, char *argv[]) {
    FILE *fpr, *fpw;
    int n;
    char **mat, *vet;

    fpr = fopen(argv[1], "r");
    fpw = fopen(argv[2], "w");
    if (fpr == NULL || fpw == NULL) {
        fprintf(stderr, "File open error.\n");
        exit(EXIT_FAILURE);
    }

    file_read(fpr, &mat, &n);

    vet = (char *) malloc(n * sizeof(char));
    if (vet == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    play(fpw, mat, n, vet, 0);

    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
    free(vet);

    fclose(fpr);
    fclose(fpw);

    return 0;
}

/*
 * Read input file into matrix mat
 */
void file_read(FILE *fp, char ***mat, int *n) {
    int i, j;
    char *tmp, s[MAX];

    if (fscanf(fp, "%d", n) == EOF) {
        fprintf(stderr, "File error.\n");
        return;
    }

    tmp = (char **) malloc(*n * sizeof(char *));
    if (tmp == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        return;
    }

    i = 0;
    while (fscanf(fp, "%s", s) != EOF && i < (*n)) {
        tmp[i] = (char *) malloc((strlen(s) + 1) * sizeof(char));
        if (tmp[i] == NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            return;
        }
        // For each row: First char = strlen
        tmp[i][0] = strlen(s);
        // For each row: Next chars = string chars
        for (j = 0; j < strlen(s); j++) {
            tmp[i][j + 1] = s[j];
        }
        i++;
    }
    // Copy local pointer to parameter
    *mat = tmp;
}

void play(FILE *fp, char **mat, int n, char *vet, int level) {
    int i;

    // Termination condition
    if (level == n) {
        for (i = 0; i < n; i++) {
            fprintf(fp, "%c", vet[i]);
        }
        fprintf(fp, "\n");
        return;
    }

    // At recursion level select a character from string level
    for (i = 0; i < (int)mat[level][0]; i++) {
        vet[level] = mat[level][i + 1];
        play(fp, mat, n, vet, level + 1);
    }

    return;
}
