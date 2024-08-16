#ifndef _IMPL3
#define _IMPL3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (30+1)

typedef struct product_s {
    char name[MAX];
    int price;
    struct product_s *next;
} product_t;

typedef struct producer_s {
    char name[MAX];
    product_t *products;
    struct producer_s *next;
} producer_t;

#endif
// 



static void seekh(product_t *, char *, char *);

/*
 * Vertical recursion:
 * p = main list pointer; prn = producer name; ptn = product name
 */
void seekv(producer_t *pr, char *prn,char *ptn){
    if (pr == NULL) {
        return;
    }
    if (strcmp(pr->name, prn) > 0) {
        return;
    }
    if (strcmp(pr->name, prn) < 0) {
    seekv(pr->next, prn, ptn);
    return;
    }

    if (strcmp(pr->name, prn) == 0) {
        seekh(pr->products, prn, ptn);
        return;
    }

fprintf(stderr, "seekV error!\n");
exit(EXIT_FAILURE);


//  * Horizontal recursion:
//  * pt = secondary list pointer; prn = producer name
}

static void seekh(product_t *pt, char *prn, char *ptn) {
    if (pt == NULL) {
        return;
    }

    if (strcmp(pt->name, ptn) > 0) {
        return;
    }

    if (strcmp(pt->name, ptn) < 0) {
        seekh(pt->next, prn, ptn);
        return;
    }

    if (strcmp(pt->name, ptn) == 0) {
        fprintf(stdout, "Producer=%s Product=%s Price=%d\n", prn, ptn, pt->price);
        return;
    }

    fprintf(stderr, "seekH error.\n");
    return;
}
