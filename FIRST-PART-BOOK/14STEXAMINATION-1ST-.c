// Version 1
void subMat_copy_ver1(
    int **m1, int r1, int c1, int **m2, int r2, int c2, int x, int y
) {
    int i, j;

    // If the specified region is out of bounds, return without doing anything.
    if (x>r1 || y>c1 || x<0 || y<0)
        return;

    // Loop through each element in the specified region of matrix m2.
    for (i=0; i<r2 && i<(r1-x); i++) {
        for (j=0; j<c2 && j<(c1-y); j++) {
            // Copy each element from m2 to the corresponding location in m1.
            m1[x+i][y+j] = m2[i][j];
        }
    }

    // No value is returned because this is a void function.
    return;
}

// Version 2
void subMat_copy_ver2(
    int **m1, int r1, int c1, int **m2, int r2, int c2, int x, int y
) {
    int i1, j1, i2, j2;

    // Loop through each element in the specified region of matrix m2.
    for (i1=x, i2=0; i1<r1 && i2<r2; i1++, i2++) {
        for (j1=y, j2=0; j1<c1 && j2<c2; j1++, j2++) {
            // Copy each element from m2 to the corresponding location in m1.
            m1[i1][j1] = m2[i2][j2];
        }
    }

    // No value is returned because this is a void function.
    return;
}
