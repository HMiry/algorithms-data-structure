BFS(G, s): s is start vertex
    for each vertex v in V(G):
        v.color = WHITE
        v.dist = INFINITY
        v.pred = NULL

    queue_init(Q)
    s.color = GRAY
    s.dist = 0
    s.pred = NULL
    queue_enqueue(Q, s)

    while not queue_empty(Q):
        u = queue_dequeue(Q)
        for each v in Adj[u]:
            if v.color == WHITE:
                v.color = GRAY
                v.dist = u.dist + 1
                v.pred = u
                queue_enqueue(Q, v)
        u.color = BLACK



""G is the graph, and s is the start vertex.
    V(G) represents all vertices in the graph G.
    Adj[u] represents the adjacency list of vertex u.
    INFINITY is a constant representing an unbounded upper value for the distance.
    WHITE, GRAY, and BLACK are constants representing the state of each vertex (unvisited, discovered, and fully explored, respectively).
    dist (distance) holds the distance from the start vertex.
    pred (predecessor) points to the predecessor of the vertex in the BFS tree.
    queue_init, queue_enqueue, and queue_dequeue are operations to initialize, enqueue, and dequeue elements from a queue Q, respectively.""