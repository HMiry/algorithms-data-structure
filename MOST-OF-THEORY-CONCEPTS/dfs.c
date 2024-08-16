#include <stdio.h>
#include <stdlib.h>

// Enum for vertex colors used in DFS
enum { WHITE, GREY, BLACK };

// Edge structure
typedef struct edge_s {
    int weight; // Weight of the edge, if needed
    struct vertex_s *dst; // Destination vertex pointer
    struct edge_s *next; // Next edge in the list for adjacency list representation
} edge_t;

// Vertex structure
typedef struct vertex_s {
    int id; // Vertex identifier
    int color; // Color of the vertex, used in DFS
    int dist; // Distance from source, used in shortest path algorithms
    int disc_time; // Discovery time in DFS
    int endp_time; // Finish time in DFS
    struct vertex_s *pred; // Predecessor in DFS path
    edge_t *head; // Head of the adjacency list of edges
    struct vertex_s *next; // Next vertex in the global list of vertices
} vertex_t;

// Graph structure
typedef struct graph_s {
    vertex_t *g; // Pointer to the list of vertices
    int nv; // Number of vertices
} graph_t;
// Depth-First Search (DFS) function initiates DFS traversal from a given source vertex.
void graph_dfs(graph_t *g, vertex_t *src) {
    int currTime = 0; // Current time counter for discovery and finish times
    vertex_t *tmp, *tmp2;

    // Print the initial list of edges to be explored
    printf("List of edges:\n");
    // Start DFS from the source vertex, recursively visiting vertices
    currTime = graph_dfs_r(g, src, currTime);

    // Continue DFS for any unvisited vertices to ensure all components are explored
    for (tmp = g->g; tmp != NULL; tmp = tmp->next) {
        if (tmp->color == WHITE) {
            currTime = graph_dfs_r(g, tmp, currTime);
        }
    }

    // After DFS, print the vertices and their discovery/finish times
    printf("List of vertices:\n");
    for (tmp = g->g; tmp != NULL; tmp = tmp->next) {
        tmp2 = tmp->pred; // Predecessor vertex
        printf("%2d: %2d/%2d (%d)\n",
               tmp->id, tmp->disc_time, tmp->endp_time,
               (tmp2 != NULL) ? tmp2->id : -1); // Print vertex info
    }
}

// Recursive DFS function explores the graph in depth-first order.
int graph_dfs_r(graph_t *g, vertex_t *n, int currTime) {
    edge_t *e;
    vertex_t *t;

    n->color = GREY; // Mark vertex as being visited
    n->disc_time = ++currTime; // Update discovery time

    // Explore all adjacent vertices
    for (e = n->head; e != NULL; e = e->next) {
        t = e->dst; // Destination vertex of the current edge

        // Check the color of the destination vertex to decide action
        switch (t->color) {
        case WHITE: // Tree edge
            printf("%d -> %d : T\n", n->id, t->id);
            t->pred = n; // Set predecessor
            currTime = graph_dfs_r(g, t, currTime); // Recursive DFS visit
            break;
        case GREY: // Back edge
            printf("%d -> %d : B\n", n->id, t->id);
            break;
        case BLACK: // Forward or cross edge
            if (n->disc_time < t->disc_time) {
                printf("%d -> %d : F\n", n->id, t->id);
            } else {
                printf("%d -> %d : C\n", n->id, t->id);
            }
            break;
        }
    }

    n->color = BLACK; // Mark vertex as fully explored
    n->endp_time = ++currTime; // Update finish time

    return currTime; // Return the current time
}

// Assume implementations for graph_load, graph_attribute_init, graph_find, and graph_dispose are provided

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]); // Check for command line argument
        return 1;
    }

    graph_t *g = graph_load(argv[1]); // Load graph from file
    int i;
    vertex_t *src;

    // Prompt user for initial vertex for DFS
    printf("Initial vertex? ");
    scanf("%d", &i);
    src = graph_find(g, i); // Find the vertex in the graph

    graph_attribute_init(g); // Initialize vertex attributes
    graph_dfs(g, src); // Perform DFS starting from the chosen vertex
    graph_dispose(g); // Clean up and free graph resources

    return 0;
}








//WITH THE ADJ MAT WAY 



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100 // Assuming a maximum of 100 vertices for simplicity

enum { WHITE, GREY, BLACK };

typedef struct vertex_s {
    int id;         
    int color;      
    int dist;       
    int disc_time;  
    int endp_time;  
    int pred;       
    int scc;        
    // Other vertex properties can be added as needed
} vertex_t;

typedef struct graph_s {
    int **adjMatrix; // Adjacency matrix to represent edges
    vertex_t *vertices; // Array of vertices
    int nv; // Number of vertices
} graph_t;

// DFS function adapted for the new graph structure
void graph_dfs(graph_t *g, int startIndex) {
    static int time = 0; // Static variable for time tracking
    vertex_t *v = &g->vertices[startIndex];

    time++; // Increment discovery time
    v->disc_time = time;
    v->color = GREY;

    // Iterate over adjacency row
    for (int i = 0; i < g->nv; i++) {
        if (v->rowAdj[i] != 0 && g->vertices[i].color == WHITE) { // Check for edge and unvisited vertex
            g->vertices[i].pred = startIndex;
            graph_dfs(g, i);
        }
    }

    v->color = BLACK;
    time++; // Increment finish time
    v->endp_time = time;
}
// Function to initialize the graph attributes before DFS
void graph_attribute_init(graph_t *g) {
    for (int i = 0; i < g->nv; i++) {
        g->vertices[i].color = WHITE;
        g->vertices[i].pred = -1;
        g->vertices[i].disc_time = 0;
        g->vertices[i].endp_time = 0;
    }
}

// Main function for demonstration purposes
int main() {
    // Assume graph_load, graph_attribute_init, and graph_dispose are implemented

    // Example usage
    graph_t *graph = graph_load("graph.txt"); // Load graph from file
    graph_attribute_init(graph); // Initialize attributes

    // Perform DFS starting from vertex 0 (or any other vertex)
    graph_dfs(graph, 0);

    // Print the vertices after DFS
    for (int i = 0; i < graph->nv; i++) {
        printf("Vertex %d: Discovery Time: %d, Finish Time: %d\n",
               i, graph->vertices[i].disc_time, graph->vertices[i].endp_time);
    }

    // Clean up and free memory
    graph_dispose(graph);
    
    return 0;
}

// Definitions of graph_load, graph_dispose, and other utility functions would go here
