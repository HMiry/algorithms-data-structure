#ifndef _IMPL2
#define _IMPL2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

typedef struct node_s {
    int key;
    struct node_s *right;
    struct node_s *left;
    
}node_t;
#endif

/* File impl2.c */

// #include "impl2.h"

// in computer the way that we check two things are identical is that we check wether they are empty or not 
// and after we checked we recursively do it for the left and right child and if they are identical we get 1 :)
int tree_isomorphism (node_t *t1, node_t *t2) {
    if (t1==NULL && t2==NULL){
        return (1);
    }
    if (t1==NULL && t2!=NULL){
        return (0);
    }
    if (t1!=NULL && t2==NULL){
        return (0);
    }
    if (t1->key!=t2->key){
        return (0);
    }
    if (tree_isomorphism(t1->left, t2->left) == 0) {
        return (0);
    }
    if (tree_isomorphism(t1->right, t2->right) == 0) {
        return (0);
    }
    return (1);
}
