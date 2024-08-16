#ifndef _GRAPH // Begin conditional compilation to avoid multiple inclusions
#define _GRAPH
#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE 100 // Define a constant for maximum line length in file operations
enum {WHITE, GREY, BLACK}; // Enumeration for vertex colors used in graph algorithms

typedef struct graph_s graph_t; // Forward declaration of graph structure
typedef struct vertex_s vertex_t; // Forward declaration of vertex structure
typedef struct edge_s edge_t; // Forward declaration of edge structure

/* graph wrapper */
struct graph_s {
  vertex_t *g; // Pointer to the list of vertices
  int nv; // Number of vertices in the graph
};

/* list (vertices) of lists (edges): edges */
struct edge_s {
  int weight; // Weight of the edge
  vertex_t *dst; // Destination vertex pointer
  edge_t *next; // Next edge in the list
};

/* list (vertices) of lists (edges): vertices */
struct vertex_s {
  int id; // Vertex identifier
  int color; // Color of the vertex, used in graph algorithms
  int dist; // Distance from the source vertex, used in shortest path algorithms
  int disc_time; // Discovery time, used in DFS
  int endp_time; // Finish time, used in DFS
  int scc; // Strongly connected component identifier
  vertex_t *pred; // Predecessor vertex in a path
  edge_t *head; // Head of the edge list
  vertex_t *next; // Next vertex in the list
};
#endif


graph_t* create_graph(int nv) {
    graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
    graph->g = (vertex_t*)malloc(nv * sizeof(vertex_t));
    graph->nv = nv;
    for (int i = 0; i < nv; i++) {
        graph->g[i].id = i;
        graph->g[i].color = WHITE;
        graph->g[i].dist = INT_MAX;
        graph->g[i].head = NULL;
        graph->g[i].next = (i + 1 < nv) ? &graph->g[i + 1] : NULL;
    }
    return graph;
}
void add_edge(graph_t* graph, int src, int dest, int weight) {
    edge_t* new_edge = (edge_t*)malloc(sizeof(edge_t));
    new_edge->weight = weight;
    new_edge->dst = &graph->g[dest];
    new_edge->next = graph->g[src].head;
    graph->g[src].head = new_edge;
}

void DFS_visit(vertex_t* vertex) {
    vertex->color = GREY;
    for (edge_t* e = vertex->head; e != NULL; e = e->next) {
        if (e->dst->color == WHITE) {
            DFS_visit(e->dst);
        }
    }
    vertex->color = BLACK;
}

void DFS(graph_t* graph) {
    for (int i = 0; i < graph->nv; i++) {
        if (graph->g[i].color == WHITE) {
            DFS_visit(&graph->g[i]);
        }
    }
}


void BFS(graph_t* graph, vertex_t* start_vertex) {
    for (int i = 0; i < graph->nv; i++) {
        graph->g[i].color = WHITE;
        graph->g[i].dist = INT_MAX;
        graph->g[i].pred = NULL;
    }
    start_vertex->color = GREY;
    start_vertex->dist = 0;
    start_vertex->pred = NULL;
    Queue q = create_queue();
    enqueue(q, start_vertex);
    while (!is_queue_empty(q)) {
        vertex_t* u = dequeue(q);
        for (edge_t* e = u->head; e != NULL; e = e->next) {
            vertex_t* v = e->dst;
            if (v->color == WHITE) {
                v->color = GREY;
                v->dist = u->dist + 1;
                v->pred = u;
                enqueue(q, v);
            }
        }
        u->color = BLACK;
    }
}
int** generate_adjacency_matrix(graph_t* graph) {
    int** matrix = (int**)malloc(graph->nv * sizeof(int*));
    for (int i = 0; i < graph->nv; i++) {
        matrix[i] = (int*)calloc(graph->nv, sizeof(int));
        for (edge_t* e = graph->g[i].head; e != NULL; e = e->next) {
            matrix[i][e->dst->id] = e->weight;
        }
    }
    return matrix;
}

