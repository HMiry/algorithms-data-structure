/* Version 1 */
//what we are doing in this code is that we find the local max 
// how we do that is that we have currnent mat and inner mat the inner
// mat is the neighbours of the original mat and if we find the neighbour
//that is greater than the mat we underestand that this point is not max 
void matrix_max_ver1(int **mat, int r, int c) {
    int r1, r2, c1, c2, stop;

    for (r1=0; r1<r; r1++) {
        for (c1=0; c1<c; c1++) {
            stop=0;
            for (r2=r1-1; r2<=r1+1 && !stop; r2++) {
                for (c2=c1-1; c2<=c1+1 && !stop; c2++) {
                    if ((r2!=r1 || c2!=c1) && r2>=0 && r2<r &&
                     c2>=0 && c2<c && mat[r1][c1]<=mat[r2][c2]) {
                        stop = 1;
                    }
                }
            }
            if (stop==0) {
                fprintf(stdout, "Local Max; row=%d column=%d\n", r1, c1);
            }
        }
    }
    return;
}
