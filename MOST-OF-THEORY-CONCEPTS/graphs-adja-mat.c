#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Include for defining INT_MAX

#define MAX_LINE 100 // Define maximum line length for reading from files

enum { WHITE, GREY, BLACK }; // Enumeration for vertex colors, used in graph algorithms

// Define a structure for a vertex in the graph
typedef struct vertex_s {
    int id;         // Unique identifier for the vertex
    int color;      // Color of the vertex, used for marking visitation status
    int dist;       // Distance from a source vertex, used in shortest path algorithms
    int disc_time;  // Discovery time, used in DFS
    int endp_time;  // Finish time, used in DFS
    int pred;       // Predecessor vertex in a path
    int scc;        // Strongly connected component identifier
    int *rowAdj;    // Adjacency row, represents edges to other vertices with weights
} vertex_t;

// Define a structure for the graph
typedef struct graph_s {
    vertex_t *g; // Pointer to an array of vertices
    int nv;      // Number of vertices in the graph
} graph_t;

// Function to load a graph from a file
graph_t *graph_load(char *filename) {
    graph_t *g;
    char line[MAX_LINE];
    int i, j, weight, dir;
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    } 

    g = (graph_t *)malloc(sizeof(graph_t));
    if (g == NULL) {
        perror("Memory allocation failed for graph");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fgets(line, MAX_LINE, fp);
    if (sscanf(line, "%d%d", &g->nv, &dir) != 2) {
        sscanf(line, "%d", &g->nv);
        dir = 1; // Default to directed graph if directionality is not specified
    }

    g->g = (vertex_t *)malloc(g->nv * sizeof(vertex_t));
    if (g->g == NULL) {
        perror("Memory allocation failed for vertices");
        fclose(fp);
        free(g);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < g->nv; i++) {
        g->g[i].id = i;
        g->g[i].color = WHITE;
        g->g[i].dist = INT_MAX;
        g->g[i].pred = -1;
        g->g[i].scc = -1;
        g->g[i].disc_time = -1;
        g->g[i].endp_time = -1;
        g->g[i].rowAdj = (int *)calloc(g->nv, sizeof(int));
        if (g->g[i].rowAdj == NULL) {
            perror("Memory allocation failed for adjacency row");
            // Properly handle partial allocation failure by cleaning up previously allocated memory
            while (--i >= 0) free(g->g[i].rowAdj);
            free(g->g);
            fclose(fp);
            free(g);
            exit(EXIT_FAILURE);
        }
    }

    while (fgets(line, MAX_LINE, fp) != NULL) {
        if (sscanf(line, "%d%d%d", &i, &j, &weight) != 3) {
            sscanf(line, "%d%d", &i, &j);
            weight = 1;
        }
        g->g[i].rowAdj[j] = weight;
        if (dir == 0) {
            g->g[j].rowAdj[i] = weight;
        }
    }

    fclose(fp);
    return g;
}

void graph_attribute_init(graph_t *g) {
    int i;
    for (i = 0; i < g->nv; i++) {
        g->g[i].color = WHITE;
        g->g[i].dist = INT_MAX;
        g->g[i].disc_time = -1;
        g->g[i].endp_time = -1;
        g->g[i].pred = -1;
        g->g[i].scc = -1;
    }
}

int graph_find(graph_t *g, int id) {
    for (int i = 0; i < g->nv; i++) {
        if (g->g[i].id == id) {
            return i;
        }
    }
    return -1;
}

void graph_dispose(graph_t *g) {
    for (int i = 0; i < g->nv; i++) {
        free(g->g[i].rowAdj);
    }
    free(g->g);
    free(g);
}



// Function to add a vertex to the graph
void graph_add_vertex(graph_t *g) {
    int new_nv = g->nv + 1; // New number of vertices
    g->g = (vertex_t *)realloc(g->g, new_nv * sizeof(vertex_t));
    
    if (g->g == NULL) {
        perror("Memory reallocation failed for vertices");
        exit(EXIT_FAILURE);
    }
    
    // Initialize the new vertex
    vertex_t *new_vertex = &g->g[g->nv];
    new_vertex->id = g->nv;
    new_vertex->color = WHITE;
    new_vertex->dist = INT_MAX;
    new_vertex->pred = -1;
    new_vertex->scc = -1;
    new_vertex->disc_time = -1;
    new_vertex->endp_time = -1;
    new_vertex->rowAdj = (int *)calloc(new_nv, sizeof(int));
    
    if (new_vertex->rowAdj == NULL) {
        perror("Memory allocation failed for adjacency row");
        exit(EXIT_FAILURE);
    }
    
    // Update the adjacency rows of all other vertices
    for (int i = 0; i < g->nv; i++) {
        g->g[i].rowAdj = (int *)realloc(g->g[i].rowAdj, new_nv * sizeof(int));
        
        if (g->g[i].rowAdj == NULL) {
            perror("Memory reallocation failed for adjacency row");
            exit(EXIT_FAILURE);
        }
        
        // Initialize the new cell to 0
        g->g[i].rowAdj[g->nv] = 0;
    }

    // Increment the number of vertices
    g->nv = new_nv;
}

// Function to add an edge to the graph
void graph_add_edge(graph_t *g, int src_id, int dest_id, int weight) {
    // Check if the vertex ids are within the bounds of the array
    if (src_id < 0 || src_id >= g->nv || dest_id < 0 || dest_id >= g->nv) {
        fprintf(stderr, "Vertex ID out of bounds.\n");
        return;
    }

    // Add the edge with the specified weight
    g->g[src_id].rowAdj[dest_id] = weight;
}

// Example of usage:
// graph_t *g = graph_load("graph.txt");
// graph_add_vertex(g); // Add a new vertex
// graph_add_edge(g, 0, g->nv - 1, 5); // Assuming 0 is a valid src_id and we want to connect to the new vertex with weight 5
