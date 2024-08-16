#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Version 1 */
void duplicate_erase_ver1(char *str) {
    int i, j, k;
    for (i = 0; str[i] != '\0'; i++) {
        for (j = i + 1; str[j] != '\0'; j++) {
            if (str[i] == str[j]) {
                for (k = j; str[k] != '\0'; k++) {
                    str[k] = str[k + 1];
                }
                j--; // Decrement j to check the new character at this position
            }
        }
    }
}

/* Version 2 */
void duplicate_erase_ver2(char *str) {
    int l, i, j;
    int *v;
    l = strlen(str);
    v = malloc(l * sizeof(int));
    if (v == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < l; i++) {
        v[i] = 0;
    }
    for (i = 0; i < l - 1; i++) {
        if (v[i] == 0) {
            for (j = i + 1; j < l; j++) {
                if (str[i] == str[j]) {
                    v[j] = 1;
                }
            }
        }
    }
    for (j = i = 0; i < l; i++) {
        if (v[i] == 0) {
            str[j] = str[i];
            j++;
        }
    }

    str[j] = '\0'; // Null-terminate the modified string
    free(v); // Free the allocated memory
    return;
}
