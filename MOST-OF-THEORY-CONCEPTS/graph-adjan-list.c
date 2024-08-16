#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Include for defining INT_MAX

#define MAX_LINE 100 // Maximum line length for reading from files
#define WHITE 0      // Color definition for unvisited vertices

// Structure definitions for graph components
typedef struct edge_s {
    int weight;           // Weight of the edge
    struct vertex_s *dst; // Destination vertex
    struct edge_s *next;  // Next edge in the list
} edge_t;

typedef struct vertex_s {
    int id;                // Vertex identifier
    int color;             // Color (visit status)
    int dist;              // Distance from source
    int disc_time;         // Discovery time in DFS
    int endp_time;         // Finish time in DFS
    int scc;               // SCC identifier
    struct vertex_s *pred; // Predecessor in a path
    edge_t *head;          // Head of edge list
    struct vertex_s *next; // Next vertex in the list
} vertex_t;

typedef struct graph_s {
    vertex_t *vertices; // List of vertices
    int nv;             // Number of vertices
} graph_t;

// Function prototypes
static vertex_t *new_node(int id);
static void new_edge(graph_t *g, int i, int j, int weight);
graph_t *graph_load(const char *filename);
void graph_attribute_init(graph_t *g);
vertex_t *graph_find(graph_t *g, int id);
void graph_dispose(graph_t *g);

// Create a new graph vertex
static vertex_t *new_node(int id) {
    vertex_t *v = malloc(sizeof(vertex_t));
    if (v == NULL) {
        perror("Failed to allocate memory for vertex");
        exit(EXIT_FAILURE);
    }
    v->id = id;
    v->color = WHITE;
    v->dist = INT_MAX;
    v->disc_time = -1;
    v->endp_time = -1;
    v->scc = -1;
    v->pred = NULL;
    v->head = NULL;
    v->next = NULL;
    return v;
}

// Add a new edge to the graph
static void new_edge(graph_t *g, int i, int j, int weight) {
    vertex_t *src = graph_find(g, i);
    vertex_t *dst = graph_find(g, j);
    edge_t *e = malloc(sizeof(edge_t));
    if (e == NULL) {
        perror("Failed to allocate memory for edge");
        exit(EXIT_FAILURE);
    }
    e->dst = dst;
    e->weight = weight;
    e->next = src->head;
    src->head = e;
}

// Load a graph from a file
graph_t *graph_load(const char *filename) {
    graph_t *g = malloc(sizeof(graph_t));
    if (g == NULL) {
        perror("Failed to allocate memory for graph");
        exit(EXIT_FAILURE);
    }
    char line[MAX_LINE];
    int i, j, weight, dir;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        free(g);
        exit(EXIT_FAILURE);
    }
    if (!fgets(line, MAX_LINE, fp) || sscanf(line, "%d%d", &g->nv, &dir) != 2) {
        sscanf(line, "%d", &g->nv); // Default to directed graph if not specified
        dir = 1;
    }
    g->vertices = NULL;
    for (i = 0; i < g->nv; i++) {
        vertex_t *newVertex = new_node(i);
        newVertex->next = g->vertices;
        g->vertices = newVertex;
    }
    while (fgets(line, MAX_LINE, fp)) {
        if (sscanf(line, "%d%d%d", &i, &j, &weight) == 3) {
            new_edge(g, i, j, weight);
            if (dir == 0) new_edge(g, j, i, weight); // For undirected graphs
        }
    }
    fclose(fp);
    return g;
}

// Reinitialize graph attributes (useful for algorithms that modify these properties)
void graph_attribute_init(graph_t *g) {
    for (vertex_t *v = g->vertices; v != NULL; v = v->next) {
        v->color = WHITE;
        v->dist = INT_MAX;
        v->disc_time = -1;
        v->endp_time = -1;
        v->pred = NULL;
        v->scc = -1;
    }
}

// Find a vertex by its ID
vertex_t *graph_find(graph_t *g, int id) {
    for (vertex_t *v = g->vertices; v != NULL; v = v->next) {
        if (v->id == id) return v;
    }
    return NULL;
}

// Dispose of the graph and free its memory
void graph_dispose(graph_t *g) {
    while (g->vertices != NULL) {
        vertex_t *v = g->vertices;
        g->vertices = v->next;
        while (v->head != NULL) {
            edge_t *e = v->head;
            v->head = e->next;
            free(e);
        }
        free(v);
    }
    free(g);
}
