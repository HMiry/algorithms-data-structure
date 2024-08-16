#include <stdio.h>
#include <stdlib.h>

// Assuming the necessary structures and their definitions are included here
typedef struct graph_s graph_t;
typedef struct vertex_s vertex_t;

enum { WHITE, GREY, BLACK };

// Function prototypes
void graph_dag(graph_t *g);
int graph_dag_r(graph_t *g, int i, int *post, int t, int *loop);

struct graph_s {
    vertex_t *g;
    int nv;
};

struct vertex_s {
    int id;
    int color;
    int *rowAdj;
    // ... other vertex properties as needed
};

void graph_dag(graph_t *g) {
    int i, *post, loop = 0, timer = 0;
    post = (int *)util_malloc(g->nv * sizeof(int));

    for (i = 0; i < g->nv; i++) {
        if (g->g[i].color == WHITE) {
            timer = graph_dag_r(g, i, post, timer, &loop);
        }
    }

    if (loop != 0) {
        fprintf(stdout, "Loop detected!\n");
    } else {
        fprintf(stdout, "Topological sort (direct):");
        for (i = g->nv - 1; i >= 0; i--) {
            fprintf(stdout, " %d", post[i]);
        }
        fprintf(stdout, "\n");
    }

    free(post);
}

int graph_dag_r(graph_t *g, int i, int *post, int t, int *loop) {
    int j;
    g->g[i].color = GREY;

    for (j = 0; j < g->nv; j++) {
        if (g->g[i].rowAdj[j] != 0) {
            if (g->g[j].color == GREY) {
                *loop = 1;
            }
            if (g->g[j].color == WHITE) {
                t = graph_dag_r(g, j, post, t, loop);
            }
        }
    }

    g->g[i].color = BLACK;
    post[t++] = i;
    return t;
}
