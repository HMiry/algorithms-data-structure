#include <stdio.h>
#include <stdlib.h>

// Assuming necessary structures and their definitions are included here
typedef struct graph_s graph_t;
typedef struct vertex_s vertex_t;

enum { WHITE, GREY, BLACK };

// Function prototypes
graph_t *graph_load(char *filename);
int graph_scc(graph_t *g);
graph_t *graph_transpose(graph_t *g);
int graph_scc_r(graph_t *g, int i, int *post, int id, int t);
void graph_dispose(graph_t *g);

struct graph_s {
    vertex_t *g;
    int nv;
};

struct vertex_s {
    int id;
    int color;
    int scc;
    int *rowAdj;
    // ... other vertex properties as needed
};

int graph_scc(graph_t *g) {
    graph_t *h;
    int i, id = 0, timer = 0;
    int *post, *tmp;

    h = graph_transpose(g);
    post = (int *)util_malloc(g->nv * sizeof(int));

    for (i = 0; i < h->nv; i++) {
        if (h->g[i].color == WHITE) {
            timer = graph_scc_r(h, i, post, id, timer);
        }
    }

    graph_dispose(h);
    id = timer = 0;
    tmp = (int *)util_malloc(g->nv * sizeof(int));

    for (i = g->nv - 1; i >= 0; i--) {
        if (g->g[post[i]].color == WHITE) {
            timer = graph_scc_r(g, post[i], tmp, id, timer);
            id++;
        }
    }

    free(post);
    free(tmp);
    return id;
}

int graph_scc_r(graph_t *g, int i, int *post, int id, int t) {
    int j;
    g->g[i].color = GREY;
    g->g[i].scc = id;

    for (j = 0; j < g->nv; j++) {
        if (g->g[i].rowAdj[j] != 0 && g->g[j].color == WHITE) {
            t = graph_scc_r(g, j, post, id, t);
        }
    }

    g->g[i].color = BLACK;
    post[t++] = i;
    return t;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    graph_t *g = graph_load(argv[1]);
    int sccs = graph_scc(g);

    fprintf(stdout, "Number of SCCs: %d\n", sccs);
    for (int j = 0; j < sccs; j++) {
        fprintf(stdout, "SCC%d:", j);
        for (int i = 0; i < g->nv; i++) {
            if (g->g[i].scc == j) {
                fprintf(stdout, " %d", i);
            }
        }
        fprintf(stdout, "\n");
    }

    graph_dispose(g);
    return 0;
}
