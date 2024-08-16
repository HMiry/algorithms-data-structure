sssp_Dijkstra(G, w, s):
    initialize_single_source(G, s)
    S = {}
    Q = V(G)

    while Q is not empty:
        u = extract_min(Q)
        S = S U {u}

        for each vertex v in the adjacency list of u:
            relax(u, v, w)



            
    G is the graph, w is the weight function for the edges, and s is the source vertex.
    V(G) represents all vertices in the graph G.
    initialize_single_source(G, s) initializes the distances from the source s to all vertices in the graph to infinity
     (except for the source vertex, which is set to zero).
    extract_min(Q) removes and returns the vertex with the smallest distance from the source vertex s in the priority 
    queue Q.
    relax(u, v, w) checks if the shortest path to v is via u and updates v's 
    distance and predecessor accordingly.

Dijkstra's algorithm maintains a set S of vertices whose final shortest-path weights 
from the source have already been determined. The algorithm repeatedly selects the vertex u 
in the vertex set Q with the minimum shortest-path estimate, adds u to S, and relaxes all edges leaving u
. In the relaxation step, if the current distance to a vertex v is greater than the distance to u plus the
 edge weight from u to v, it updates the distance to v.

This pseudocode assumes that the graph G is represented in a way that allows
 efficient access to the adjacency list of each vertex and that the priority queue
  Q is implemented efficiently, typically using a min-heap.





  #include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
};

struct vertex_s {
    int id;
    int ne; // Number of edges
    int color;
    int dist;
    int scc;
    int disc_time;
    int endp_time;
    int pred;
    edge_t *edges;
};

graph_t *graph_load(char *filename);
void sssp_dijkstra(graph_t *g, int i);
int graph_min(graph_t *g);
void graph_dispose(graph_t *g);

void sssp_dijkstra(graph_t *g, int src) {
    int j, k;

    // Initialize distances
    for (int i = 0; i < g->nv; i++) {
        g->g[i].dist = INT_MAX;
        g->g[i].pred = -1;
        g->g[i].color = WHITE;
    }

    // Set source vertex distance to 0
    g->g[src].dist = 0;

    int u = src;
    while (u >= 0) {
        g->g[u].color = GREY;
        for (k = 0; k < g->g[u].ne; k++) {
            j = g->g[u].edges[k].dst;
            if (g->g[j].color == WHITE) {
                if (g->g[u].dist + g->g[u].edges[k].weight < g->g[j].dist) {
                    g->g[j].dist = g->g[u].dist + g->g[u].edges[k].weight;
                    g->g[j].pred = u;
                }
            }
        }
        g->g[u].color = BLACK;
        u = graph_min(g);
    }
}

int graph_min(graph_t *g) {
    int i, pos = -1, min = INT_MAX;
    for (i = 0; i < g->nv; i++) {
        if (g->g[i].color == WHITE && g->g[i].dist < min) {
            min = g->g[i].dist;
            pos = i;
        }
    }
    return pos;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    graph_t *g = graph_load(argv[1]);
    int i;
    fprintf(stdout, "Initial vertex? ");
    scanf("%d", &i);

    sssp_dijkstra(g, i);

    fprintf(stdout, "Weights starting from vertex %d\n", i);
    for (i = 0; i < g->nv; i++) {
        if (g->g[i].dist != INT_MAX) {
            fprintf(stdout, "Node %d: %d (%d)\n", i, g->g[i].dist, g->g[i].pred);
        }
    }

    graph_dispose(g);
    return 0;
}
