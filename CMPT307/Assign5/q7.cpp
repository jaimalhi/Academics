//* g++ -o x q7.cpp

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>
using namespace std;

//* =================== PART 1: Find MST using Adjecency List & Matrix ===============================
// Write two programs for Prim's minimum spanning tree algorithm discussed in class, 
// one implements the algorithm with the input graph G represented by adjacent list
// and the other implements the algorithm with G represented by adjacent matrix

typedef pair<int, int> pii; // Define a pair of integers as pii for convenience

class Graph {
private:
    int V; // Number of vertices in the graph
    vector<pii> *adj; // Adjacency list 
    vector<vector<int>> matrix; // Adjacency matrix
public:
    Graph(int V) : V(V), adj(new vector<pii>[V]), matrix(V, vector<int>(V, INT_MAX)) {}

    ~Graph() {
        delete[] adj; // Free the allocated memory for the adjacency list
    }
    
    void add_edge(int u, int v, int w) {
        // Add an edge from u to v with weight w
        adj[u].push_back({w, v});
        // Add an edge from v to u with weight w, since the graph is undirected
        adj[v].push_back({w, u}); 
        matrix[u][v] = w;
        matrix[v][u] = w;
    }

    // Prim's algorithm implementations
    vector<pii> primMSTList();
    void primMSTMatrix();
};

// Prim's algorithm using adjacency list
vector<pii> Graph::primMSTList() {
    // Priority queue to select the edge with the smallest weight
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    int start = 0; // Starting vertex for Prim's algorithm
    vector<bool> visited(V, false); // Vector to track visited vertices
    vector<pii> minSpanTree; // Vector to store the MST
    vector<int> parent(V, -1); // Vector to store the parent of each vertex
    vector<int> key(V, INT_MAX); // Vector to store the key values of each vertex

    // Start with the first vertex
    pq.push(make_pair(0, start));
    key[start] = 0;

    // While there are vertices to be processed
    while (!pq.empty()) {
        // Select the edge with the smallest weight
        int u = pq.top().second;
        pq.pop();

        // If the vertex has already been visited, skip it
        if (visited[u]) continue;

        // Mark the vertex as visited
        visited[u] = true;
        // If the vertex is not the start vertex, add it to the MST
        if (u != start) {
            minSpanTree.push_back({parent[u], u});
        }

        // For each neighbor of the current vertex
        for (auto &edge : adj[u]) {
            int v = edge.second; // The neighbor
            int weight = edge.first; // The weight of the edge to the neighbor

            // If the neighbor has not been visited and the weight of the edge is less than the key value of the neighbor
            if (!visited[v] && key[v] > weight) {
                // Update the parent and key value of the neighbor
                parent[v] = u;
                key[v] = weight;
                // Add the neighbor to the priority queue
                pq.push({key[v], v});
            }
        }
    }
    // Return the MST
    return minSpanTree;
}

// Prim's algorithm using adjacency matrix
void Graph::primMSTMatrix() {
    vector<int> parent(V, -1);
    vector<int> key(V, INT_MAX);
    vector<bool> mstSet(V, false);

    key[0] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;

        // Find the vertex with minimum key value from the set of vertices not yet included in MST
        for (int v = 0; v < V; v++)
            if (!mstSet[v] && (u == -1 || key[v] < key[u]))
                u = v;

        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (matrix[u][v] && !mstSet[v] && matrix[u][v] < key[v]) {
                parent[v] = u, key[v] = matrix[u][v];
            }
        }
    }

    // std::cout << "Edges in the MST by adjacency matrix:" << endl;
    // for (int i = 1; i < V; i++)
    //     std::cout << parent[i] << " - " << i << " \t" << matrix[i][parent[i]] << endl;
}

void part1Main() {
    int Vertices = 9;
    Graph graph(Vertices);

    // Add edges as per your figure 1
    graph.add_edge(0, 1, 4);
    graph.add_edge(0, 7, 8);
    graph.add_edge(1, 2, 8);
    graph.add_edge(1, 7, 11);
    graph.add_edge(2, 3, 7);
    graph.add_edge(2, 8, 2);
    graph.add_edge(2, 5, 4);
    graph.add_edge(3, 4, 9);
    graph.add_edge(3, 5, 14);
    graph.add_edge(4, 5, 10);
    graph.add_edge(5, 6, 2);
    graph.add_edge(6, 7, 1);
    graph.add_edge(6, 8, 6);
    graph.add_edge(7, 8, 7);

    // Compute the MST using adjacency list
    vector<pii> minSpanTreeList = graph.primMSTList();
    std::cout << "Edges in the minimum spanning tree using adjacency list:" << endl;
    for (auto &edge : minSpanTreeList) {
        std::cout << edge.first << " - " << edge.second << endl;
    }
    std::cout << "===========================\n";

    // Compute the MST using adjacency matrix
    graph.primMSTMatrix();
}

//* ================ PART 2: Running times for n = 100, 200, 400, 800 node ================
// Run your programs on connected edge-weighted G with n = 100, 200, 400, 800 nodes
// for each n, with m ~ 3n, n^1.5, n(n-1)/2 edges, and each edge assigned a random 
// number from [1, a] form some a > 1. Record the running time of your programs
// Create a procedure to create input graphs for both implementations and exclude 
// runtime of the procedure from the times of your implmentations for Prim’s algorithm

// Random number generator in a given range
int randInRange(int low, int high) {
    return low + rand() % (high - low + 1);
}


// Create a connected graph with n vertices and m edges
void createGraph(Graph &graph, int n, int m, int a) {
    // Ensure the graph is connected by adding a cycle
    for (int i = 0; i < n; i++) {
        int w = randInRange(1, a); // Random weight
        graph.add_edge(i, (i+1)%n, w);
    }

    int extraEdges = m - n; // Calculate the number of extra edges to add
    set<pair<int, int>> edges; // To keep track of the edges already added

    // Add the remaining edges randomly
    while (extraEdges > 0) {
        int u = randInRange(0, n-1);
        int v = randInRange(0, n-1);
        if (u != v && edges.find({u, v}) == edges.end() && edges.find({v, u}) == edges.end()) {
            int w = randInRange(1, a); // Random weight
            graph.add_edge(u, v, w);
            edges.insert({u, v});
            extraEdges--;
        }
    }
}

void part2Main() {
    int n_values[4] = {100, 200, 400, 800}; // Define the values of n [100, 200, 400, 800]
    for(int i = 0; i < 4; i++){
        int n = n_values[i];
        // Modify as per the problem statement (3n, n^1.5, n(n-1)/2)
        // int m = 3 * n;
        // int m = pow(n, 1.5);
        int m = n * (n-1) / 2;
        int a = 10; // Define the maximum weight

        // Seed the random number generator
        srand(time(nullptr));

        // Create the graph
        Graph graph(n);
        createGraph(graph, n, m, a);

        // Record the start time of Prim's algorithm
        clock_t start = clock();

        // Run Prim's algorithm using adjacency list
        vector<pii> minSpanTreeList = graph.primMSTList();

        // Record the end time and calculate the time taken for Prim's using adjacency list
        clock_t endList = clock();
        double timeTakenList = double(endList - start) / CLOCKS_PER_SEC;

        // Record the start time of Prim's algorithm using adjacency matrix
        start = clock();

        // Run Prim's algorithm using adjacency matrix
        graph.primMSTMatrix();

        // Record the end time and calculate the time taken for Prim's using adjacency matrix
        clock_t endMatrix = clock();
        double timeTakenMatrix = double(endMatrix - start) / CLOCKS_PER_SEC;

        // Output the times
        std::cout << "Running for n = " << n << " and m = " << m << " and a = " << a << endl;
        std::cout << "Time taken for Prim's using adjacency list with n = " << n << ": " << timeTakenList << " seconds\n";
        std::cout << "Time taken for Prim's using adjacency matrix with n = " << n << ": " << timeTakenMatrix << " seconds\n";
        std::cout << "===========================\n"; 
    }
}

//* ==================== MAIN ====================
int main(){
    // std::cout << "========== PART 1 =========\n";
    // part1Main();

    std::cout << "========== PART 2 =========\n";
    part2Main();

    return 0;
}