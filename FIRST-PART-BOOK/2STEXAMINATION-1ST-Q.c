#include <stdio.h>
#include <stdlib.h>

/* Version 1 */
void rotate_ver1(int *vet, int n, int p) {
    int *aux, d, i, j;

    d = (p > 0) ? p : -p;
    d = d % n ? d % n : d;
    aux = malloc(d * sizeof(int));
    if (aux == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    if (p > 0) {
        /* Right rotation */
        for (i=n-d, j=0; i<n; i++, j++) {
            aux[j] = vet[i];
        }
        for (i=n-1; i>=d; i--) {
            vet[i] = vet[i-d];
        }
        for (i=0; i<d; i++) {
            vet[i] = aux[i];
        }
    } else {
        /* Left rotation */
        for (i=0; i<d; i++) {
            aux[i] = vet[i];
        }
        for (i=0; i<n-d; i++) {
            vet[i] = vet[i+d];
        }
        for (i=n-d, j=0; i<n; i++, j++) {
            vet[i] = aux[j];
        }
    }
    free(aux);
    return;
}
/* Version 2 */
void rotate_ver2(int *vet, int n, int p) {
    int *aux, i, j;

    aux = malloc(n * sizeof(int));
    if (aux == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    for (i=0; i<n; i++) {
        aux[i] = vet[i];
    }
    for (i=0; i<n; i++) {
        j = i + p;
        if (j < 0) {
            j = j + n;
        }
        vet[j % n] = aux[i];
    }

    free(aux);
    return;
}
