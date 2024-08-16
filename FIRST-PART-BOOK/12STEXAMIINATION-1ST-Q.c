int sum_mat(int **mat, int r, int c, int n) {
    int r1, r2, c1, c2, sum, largest;

    largest = -1;
    for (r1=0; r1<=(r-n); r1++) {
        for (c1=0; c1<=(c-n); c1++) {
            sum = 0;
            for (r2=0; r2<n; r2++) {
                for (c2=0; c2<n; c2++) {
                    sum += mat[r1+r2][c1+c2];
                }
            }
            if (largest==-1 || (sum>largest)) {
                largest = sum;
            }
        }
    }

    return largest;
}
