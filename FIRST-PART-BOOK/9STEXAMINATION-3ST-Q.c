#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int string_split_r(char *str, int n, int *length, int *result, int ind, int len);

void string_split(char *str, int n, int *length) {
    int i;
    int *result;

    result = (int *)malloc((strlen(str) + 1) * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < strlen(str); ++i) {
        result[i] = 0;
    }

    string_split_r(str, n, length, result, 0, 0);
    free(result);

    return;
}

int string_split_r(char *str, int n, int *length, int *result, int ind, int len) {
    int i, j, k;

    // Termination with no solution
    if (len > strlen(str)) {
        return (0);
    }

    // Termination with a solution
    if (len == strlen(str)) {
        for (i = 0; i < ind; i++) {
            for (j = 0; j < result[i]; j++) {
                fprintf(stdout, "%c", str[k++]);
            }
            fprintf(stdout, " ");
        }
        fprintf(stdout, "\n");
        return (1);
    }
    // Try to use all possible sub-string lengths
for (i = 0; i < n; i++) {
    result[ind] = length[i];
    
    #if 1
    /* Enable the following line to have ALL solutions */
    string_split_r(str, n, length, result, ind+1, len+length[i]);
    #else
    /* Enable the following 2 lines to have only ONE solution */
    if (string_split_r(str, n, length, result, ind+1, len+length[i]))
        return (1);
    #endif
}

return (0);

}
