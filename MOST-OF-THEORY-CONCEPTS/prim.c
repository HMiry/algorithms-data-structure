mst_Prim(G, w, source):
    for each v in V(G):
        v.key = INFINITY
        v.pred = NULL

    source.key = 0
    Q = V(G)

    while Q is not empty:
        u = extract_min(Q)
        for each v in adjacency list of u:
            if v is in Q and w(u, v) < v.key:
                v.pred = u
                v.key = w(u, v)



    G is the graph.
    w represents the weight of the edges.
    source is the starting vertex.
    V(G) is the set of vertices in the graph G.
    INFINITY is a constant representing a very high value.
    v.key stores the minimum weight of any edge connecting v to a vertex in the MST.
    v.pred is the predecessor of v in the MST.
    Q is a priority queue that contains all vertices of G not yet included in the MST.
    extract_min(Q) removes and returns the vertex with the smallest key value from Q.

The algorithm initializes all vertices with a key value of infinity and no predecessor. 
The key value of the source vertex is set to 0. It then repeatedly extracts the vertex u with 
the smallest key value from Q and relaxes all edges (u, v) such that v is still in Q. If a better
 (lower weight) edge to v is found, v s key and predecessor are updated.

This process builds the MST by connecting vertices with the lowest weight edges, ensuring no cycles are formed.




#include <stdio.h>
#include <stdlib.h>

// Assuming necessary structures and their definitions are included here
typedef struct graph_s graph_t;
typedef struct vertex_s vertex_t;
typedef struct edge_s edge_t;

struct graph_s {
    vertex_t *g;
    int nv;
};

struct edge_s {
    int weight;
    int dst;
    edge_t *next;
};

struct vertex_s {
    int id;
    int color;
    int dist;
    int disc_time;
    int endp_time;
    int pred;
    int scc;
    edge_t *head;
};

graph_t *graph_load(char *filename);
void graph_dispose(graph_t *g);
int mst_prim(graph_t *g);

int mst_prim(graph_t *g) {
    int i, j, min, weight = 0;
    int *fringe;
    edge_t *e;

    fringe = (int *)util_malloc(g->nv * sizeof(int));
    for (i = 0; i < g->nv; i++) {
        fringe[i] = -1;
        g->g[i].dist = INT_MAX;
        g->g[i].pred = -1;
    }

    fprintf(stdout, "List of edges making an MST:\n");
    min = 0;  // Starting vertex
    g->g[min].dist = 0;

    while (min != -1) {
        i = min;
        weight += g->g[i].dist;
        if (g->g[i].dist != 0) {
            printf("Edge %d-%d (w=%d)\n", fringe[i], i, g->g[i].dist);
        }

        min = -1;
        e = g->g[i].head;
        while (e != NULL) {
            j = e->dst;
            if (fringe[j] == -1 && e->weight < g->g[j].dist) {
                g->g[j].dist = e->weight;
                fringe[j] = i;
            }
            e = e->next;
        }

        for (j = 0; j < g->nv; j++) {
            if (fringe[j] == -1 && (min == -1 || g->g[j].dist < g->g[min].dist)) {
                min = j;
            }
        }
    }

    free(fringe);
    return weight;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    graph_t *g = graph_load(argv[1]);
    int weight = mst_prim(g);

    fprintf(stdout, "Total tree weight: %d\n", weight);
    graph_dispose(g);
    return 0;
}
