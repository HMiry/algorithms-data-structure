#include <stdio.h>
#include <string.h>

// Version 1
int mat_search_ver1(char **mat, int R, int C, char *str) {
    int r, c, l, i, found, count;

    l = strlen(str);
    count = 0;
    for (r=0; r<R; r++) {
        for (c=0; c<C; c++) {
            /* Horizontal search */
            for (found = 1, i=0; i<l && found==1; i++) {
                if ((c+i) >= C || mat[r][c+i] != str[i]) {
                    found = 0;
                }
            }
            if (found == 1) {
                /* Debug printing
                fprintf(stdout, "Found H at %d %d\n", r, c);
                */
                count++;
            }
            /* Vertical search */
            for (found = 1, i=0; i<l && found==1; i++) {
                if ((r+i) >= R || mat[r+i][c] != str[i]) {
                    found = 0;
                }
            }
            if (found == 1) {
                /* Debug printing
                fprintf(stdout, "Found V at %d %d\n", r, c);
                */
                count++;
            }
        }
    }
    return count;
}
// Version 2
int mat_search_ver2(char **mat, int R, int C, char *str) {
    int r, c, i, j, l, found, count;
    int offset[2][2] = {{0,1}, {1,0}};

    l = strlen(str);
    count = 0;
    for (r=0; r<R; r++) {
        for (c=0; c<C; c++) {
            for (j=0; j<2; j++) {
                for (found = 1, i=0; i<l && found==1; i++) {
                    if (((r+i*offset[j][0])>=R || (c+i*offset[j][1])>=C) ||
                        mat[r+i*offset[j][0]][c+i*offset[j][1]] != str[i]) {
                        found = 0;
                    }
                }
                if (found == 1) {
                    /* Debug printing
                    fprintf(stdout, "Found H at %d %d\n", r, c);
                    */
                    count++;
                }
            }
        }
    }
    return count;
}

//commented version


#include <stdio.h>
#include <string.h>

// Version 1 of the matrix search function
int mat_search_ver1(char **mat, int R, int C, char *str) {
    // Declaration of variables
    int r, c, l, i, found, count;

    l = strlen(str); // Get the length of the string to be searched
    count = 0; // Initialize count of found strings to 0
    // Iterate over each row of the matrix
    for (r=0; r<R; r++) {
        // Iterate over each column of the matrix
        for (c=0; c<C; c++) {
            /* Horizontal search */
            // Assume the string is found until proven otherwise
            for (found = 1, i=0; i<l && found==1; i++) {
                // If out of bounds or character does not match, not found
                if ((c+i) >= C || mat[r][c+i] != str[i]) {
                    found = 0; // Set found to false
                }
            }
            // If found after horizontal search, increment count
            if (found == 1) {
                /* Debug printing
                fprintf(stdout, "Found H at %d %d\n", r, c);
                */
                count++;
            }
            /* Vertical search */
            // Reset found for vertical search
            for (found = 1, i=0; i<l && found==1; i++) {
                // If out of bounds or character does not match, not found
                if ((r+i) >= R || mat[r+i][c] != str[i]) {
                    found = 0; // Set found to false
                }
            }
            // If found after vertical search, increment count
            if (found == 1) {
                /* Debug printing
                fprintf(stdout, "Found V at %d %d\n", r, c);
                */
                count++;
            }
        }
    }
    return count; // Return the total count of found strings
}

// Version 2 of the matrix search function
int mat_search_ver2(char **mat, int R, int C, char *str) {
    // Declaration of variables
    int r, c, i, j, l, found, count;
    // Offsets to check for horizontal and vertical patterns
    int offset[2][2] = {{0,1}, {1,0}};

    l = strlen(str); // Get the length of the string to be searched
    count = 0; // Initialize count of found strings to 0
    // Iterate over each row of the matrix
    for (r=0; r<R; r++) {
        // Iterate over each column of the matrix
        for (c=0; c<C; c++) {
            // Check both horizontal and vertical directions
            for (j=0; j<2; j++) {
                // Assume the string is found until proven otherwise
                for (found = 1, i=0; i<l && found==1; i++) {
                    // Check if current position + offset is out of bounds or character does not match
                    if (((r+i*offset[j][0])>=R || (c+i*offset[j][1])>=C) ||
                        mat[r+i*offset[j][0]][c+i*offset[j][1]] != str[i]) {
                        found = 0; // Set found to false
                    }
                }
                // If found, increment count
                if (found == 1) {
                    /* Debug printing
                    fprintf(stdout, "Found H at %d %d\n", r, c);
                    */
                    count++;
                }
            }
        }
    }
    return count; // Return the total count of found strings
}
