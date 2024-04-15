//* g++ -o x q3.cpp

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>
#include <set>
#include <utility>
using namespace std;

//* =================== PART 1: Find Shortest Path using Adjecency List & Matrix ===============================
// Write two programs for Dijkstra's minimum spanning tree algorithm discussed in class, 
// one implements the algorithm with the input graph G represented by adjacent list
// and the other implements the algorithm with G represented by adjacent matrix
typedef pair<int, int> pii; // Define a pair of integers as pii for convenience

class Graph {
private:
    int V; // Number of vertices in the graph
    vector<pii> *adj; // Adjacency list 
    vector<vector<int>> matrix; // Adjacency matrix

    // Helper function to print the shortest path
    void printPath(vector<int> const &prev, int i) {
        if (i < 0) {
            return;
        }
        printPath(prev, prev[i]);
        cout << i << " ";
    }

    // Helper function for Dijkstra's algorithm using adjacency list
    vector<int> dijkstraList(int src, vector<int> &prev) {
        vector<int> dist(V, INT_MAX);
        prev.assign(V, -1);
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        pq.push({0, src});
        dist[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto &i : adj[u]) {
                int v = i.second;
                int weight = i.first;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u; // Set the predecessor
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    // Helper function for Dijkstra's algorithm using adjacency matrix
    vector<int> dijkstraMatrix(int src, vector<int> &prev) {
        vector<int> dist(V, INT_MAX);
        prev.assign(V, -1);
        set<pii> setds;

        dist[src] = 0;
        setds.insert({0, src});

        while (!setds.empty()) {
            int u = setds.begin()->second;
            setds.erase(setds.begin());

            for (int v = 0; v < V; ++v) {
                if (matrix[u][v] != INT_MAX && dist[v] > dist[u] + matrix[u][v]) {
                    if (dist[v] != INT_MAX) {
                        setds.erase(setds.find({dist[v], v}));
                    }
                    dist[v] = dist[u] + matrix[u][v];
                    prev[v] = u; // Set the predecessor
                    setds.insert({dist[v], v});
                }
            }
        }
        return dist;
    }
    
public:
    Graph(int V) : V(V), adj(new vector<pii>[V]), matrix(V, vector<int>(V, INT_MAX)) {}

    ~Graph() {
        delete[] adj; // Free the allocated memory for the adjacency list
    }
    
    void add_edge(int u, int v, int w) {
        adj[u].push_back({w, v});
        matrix[u][v] = w;
    }

    // Dijkstra's algorithm using adjacency list
    void dijkstraUsingList(int src) {
        vector<int> prev;
        vector<int> dist = dijkstraList(src, prev);

        // // Output the distances and paths
        // for (int i = 0; i < V; ++i) {
        //     cout << "Distance from " << src << " to " << i << " is " << dist[i] << ", Path: ";
        //     printPath(prev, i);
        //     cout << endl;
        // }
    }

    // Dijkstra's algorithm using adjacency matrix
    void dijkstraUsingMatrix(int src) {
        vector<int> prev;
        vector<int> dist = dijkstraMatrix(src, prev);

        // // Output the distances and paths
        // for (int i = 0; i < V; ++i) {
        //     cout << "Distance from " << src << " to " << i << " is " << dist[i] << ", Path: ";
        //     printPath(prev, i);
        //     cout << endl;
        // }
    }
};


void part1Main() {
    int Vertices = 5;
    Graph graph(Vertices);

    // mapping vertices to integers
    int s = 0, t = 1, x = 2, z = 3, y = 4;

    // Add edges as per figure 1
    graph.add_edge(s, t, 10);
    graph.add_edge(s, y, 5);
    graph.add_edge(t, x, 1);
    graph.add_edge(t, y, 2);
    graph.add_edge(x, z, 4);
    graph.add_edge(z, x, 6);
    graph.add_edge(z, s, 7);
    graph.add_edge(y, t, 3);
    graph.add_edge(y, x, 9);
    graph.add_edge(y, z, 2);

    // Assuming 's' is the source
    cout << "Using adjacency list:" << endl;
    graph.dijkstraUsingList(s);
    cout << endl;

    cout << "Using adjacency matrix:" << endl;
    graph.dijkstraUsingMatrix(s);
    cout << endl;
}

//* ================ PART 2: Running times for n = 100, 200, 400, 800 node ================
// Run your programs on connected edge-weighted G with n = 100, 200, 400, 800 nodes
// for each n, with m ~ 3n, n^1.5, n(n-1)/2 edges, and each edge assigned a random 
// number from [1, a] form some a > 1. Record the running time of your programs
// Create a procedure to create input graphs for both implementations and exclude 
// runtime of the procedure from the times of your implmentations for Dijkstra's algorithm

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

        // Record the start time of Dijkstra's algorithm using adjacency list
        clock_t startList = clock();

        // Run Dijkstra's algorithm using adjacency list (modify the implementation to not print paths)
        graph.dijkstraUsingList(0);

        // Record the end time and calculate the time taken for Dijkstra's using adjacency list
        clock_t endList = clock();
        double timeTakenList = double(endList - startList) / CLOCKS_PER_SEC;

        // Record the start time of Dijkstra's algorithm using adjacency matrix
        clock_t startMatrix = clock();

        // Run Dijkstra's algorithm using adjacency matrix (modify the implementation to not print paths)
        graph.dijkstraUsingMatrix(0);

        // Record the end time and calculate the time taken for Dijkstra's using adjacency matrix
        clock_t endMatrix = clock();
        double timeTakenMatrix = double(endMatrix - startMatrix) / CLOCKS_PER_SEC;

        // Output the times
        std::cout << "Running for n = " << n << " and m = " << m << " and a = " << a << endl;
        std::cout << "Time taken using adjacency list with n = " << n << ": " << timeTakenList << " seconds\n";
        std::cout << "Time taken using adjacency matrix with n = " << n << ": " << timeTakenMatrix << " seconds\n";
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