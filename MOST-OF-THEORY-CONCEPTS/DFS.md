DFS(G):
    for each vertex v in V(G):
        v.color = WHITE
        v.dtime = INFINITY
        v.endtime = INFINITY
        v.pred = NULL

    time = 0

    for each vertex v in V(G):
        if v.color == WHITE:
            DFS_r(G, v)

DFS_r(G, u):
    time = time + 1
    u.dtime = time
    u.color = GRAY

    for each v in Adj[u]:
        if v.color == WHITE:
            v.pred = u
            DFS_r(G, v)

    u.color = BLACK
    time = time + 1
    u.endtime = time


""    G is the graph.
    V(G) represents all vertices in the graph G.
    Adj[u] represents the adjacency list of vertex u.
    INFINITY is a constant representing an unbounded upper value for the discovery and finishing times.
    WHITE, GRAY, and BLACK are constants representing the state of each vertex (unvisited, discovered, and fully explored, respectively).
    dtime and endtime represent the discovery time and finishing time of each vertex, respectively.
    pred (predecessor) points to the predecessor of the vertex in the DFS tree.
    DFS_r is the recursive function of the DFS algorithm.

The main DFS function initializes all vertices as unvisited (WHITE) and with infinite discovery and finishing times
. It then iterates over all vertices, calling DFS_r for each unvisited vertex. The recursive DFS_r function updates the discovery time
 and color of each vertex, explores adjacent unvisited vertices, and finally sets the vertex color to BLACK and updates the finishing time. 
 The time variable is used to track the ""