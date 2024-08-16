#include <stdio.h>
#include <stdlib.h>
#include <string.h>/* Version 2 */
#define SIZE 10



int area_ver2(FILE *fp) {
    /* Define and initialize mat */
    int mat[SIZE][SIZE] = {{0}};
    int tot = 0;
    int x1, y1, x2, y2, r, c;

    /* Read file */
    while (fscanf(fp, "%d %d %d %d", &x1, &y1, &x2, &y2) == 4) {
        if (x1<0 || x1>SIZE || y1<0 || y1>SIZE ||
            x2<0 || x2>SIZE || y2<0 || y2>SIZE) {
            fprintf(stderr,
                    "Skipping rectangle out of bound (%d,%d,%d,%d).\n",
                    x1, y1, x2, y2);
            continue;
        }

        /* Count and mark cells */
        for (r=y1; r<y2; r++) {
            for (c=x1; c<x2; c++) {
                if (mat[r][c] == 0) {
                    tot++;
                    mat[r][c] = 1;
                }
            }
        }
    }

    return tot;
}
