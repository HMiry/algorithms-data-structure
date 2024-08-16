#include <stdlib.h>
#include <stdio.h>

#define SIZE 10
#define EMPTY 0
#define FULL 1
#define NS 4
#define NB 5

void switchAndBulb_ver1(int [][NB], int, int, int *, int *, int, int);
int switchAndBulb_ver2(int [][NB], int, int, int *, int, int, int);
static int check(int [][NB], int, int, int, int []);

int main(int argc, char *argv[]) {
    int nBest = NS+1;
    int mat[NS][NB] = {{1, 1, 1, 0, 1},
                       {1, 0, 1, 1, 0},
                       {0, 1, 1, 1, 0},
                       {1, 0, 0, 0, 1}};
    int switchBest[NS] = {0, 0, 0, 0};
    int switchCurrent[NS] = {0, 0, 0, 0};
    int i, k, found;

    // Version 1
    fprintf(stdout, "Version 1: ");
    switchAndBulb_ver1(mat, NS, NB, &nBest, switchBest, switchCurrent, 0);
    if (nBest == NS) {
        fprintf(stdout, "No solution found.\n");
    } else {
        fprintf(stdout, "Solution found; ");
        fprintf(stdout, "%d Switches on -> ", nBest);
        for (i=0; i<NS; i++) {
            if (switchBest[i]) {
                fprintf(stdout, "%d ", i);
            }
        }
        fprintf(stdout, "\n");
    }

    // Version 2
    fprintf(stdout, "Version 2: ");
    found = 0;
    for (k=1; k<=NS && found==0; k++) {
        if (switchAndBulb_ver2(mat, NS, NB, switchCurrent, 0, k, 0) == 1) {
            found = 1;
        }
    }

    if (found==0) {
        fprintf(stdout, "No solution found.\n");
    }

    return 1;
}

/* Version 1
 * Powerset generated with arrangements with repetitions
 */
void switchAndBulb_ver1(int mat[][NB], int ns, int nb, int *nBest, int switchBest[NS], int switchCurrent[NS], int level) {
    int i, j, c, n, flag;

    // Termination
    if (level >= ns) {
        flag = 1;
        for (i=0; i<nb && flag == 1; i++) {
            c = 0;
            for (j=0; j<ns; j++) {
                if (switchCurrent[j] == 1) {
                    c = c + mat[j][i];
                }
            }
            if ((c & 2) == 0) {
                flag = 0;
            }
        }
        if (flag == 1) {
            n = 0;
            for (j=0; j<ns; j++) {
                n = n + switchCurrent[j];
            }
            if (n < *nBest) {
                *nBest = n;
                for (i=0; i<ns; i++) {
                    switchBest[i] = switchCurrent[i];
                }
            }
        }
        return;
    }
    // Set All Switches
    switchCurrent[level] = 0;
    switchAndBulb_ver1(mat, ns, nb, nBest, switchBest, switchCurrent, level+1);
    switchCurrent[level] = 1;
    switchAndBulb_ver1(mat, ns, nb, nBest, switchBest, switchCurrent, level+1);
}

/*
 * Version 2
 * Powerset generated with simple n-choose-k combinations
 */
int switchAndBulb_ver2(int mat[NS][NB], int ns, int nb, int switchCurrent[NS], int level, int k, int start) {
    int i;

    // Termination
    if (level >= k) {
        if (check(mat, ns, nb, k, switchCurrent) == 1) {
            fprintf(stdout, "Solution found; ");
            fprintf(stdout, "%d Switches on -> ", k);
            for (i=0; i<k; i++) {
                fprintf(stdout, "%d ", switchCurrent[i]);
            }
            fprintf(stdout, "\n");
            return 1;
        } else {
            return 0;
        }
    }

    // Set All Switches
    for (i=start; i<ns; i++) {
        switchCurrent[level] = i;
        if (switchAndBulb_ver2(mat, NS, NB, switchCurrent, level+1, k, i+1) == 1) {
            return 1;
        }
    }

    return 0;
}

static int check(int mat[NS][NB], int n, int m, int k, int switchCurrent[NS]) {
    int i, j, ok = 1, *bulbs;

    bulbs = calloc(m, sizeof(int));
    if (bulbs == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    for (i=0; i<k; i++) {
        for (j=0; j<m; j++) {
            bulbs[j] += mat[switchCurrent[i]][j];
        }
    }
    for (i=0; i<m; i++) {
        bulbs[i] = bulbs[i] % 2;
    }

    for (i=0; i<m; i++) {
        ok &= bulbs[i];
    }

    free(bulbs);
    return ok;
}
