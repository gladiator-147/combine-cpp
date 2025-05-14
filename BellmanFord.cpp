#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define V 4  // Number of vertices

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Bellman-Ford Algorithm
void bellmanFord(vector<Edge>& edges, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (auto edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int wt = edge.weight;
            if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // Check for negative weight cycle
    for (auto edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        int wt = edge.weight;
        if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
            cout << "Negative weight cycle detected.\n";
            return;
        }
    }

    cout << "\nBellman-Ford (from node " << src << "):\n";
    for (int i = 0; i < V; i++)
        cout << "Distance to node " << i << " = " << dist[i] << endl;
}

// Dijkstra Algorithm
int minDistance(vector<int>& dist, vector<bool>& visited) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(vector<vector<int>>& graph, int src) {
    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = true;

        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    cout << "\nDijkstra (from node " << src << "):\n";
    for (int i = 0; i < V; i++)
        cout << "Distance to node " << i << " = " << dist[i] << endl;
}

int main() {
    // Edges for Bellman-Ford
    vector<Edge> edges = {
        {0, 1, 4},
        {0, 2, 5},
        {1, 2, -3},
        {1, 3, 6},
        {2, 3, 2}
    };

    // Adjacency Matrix for Dijkstra (INT_MAX for no edge)
    vector<vector<int>> graph = {
        {0, 4, 5, INT_MAX},
        {INT_MAX, 0, -3, 6},
        {INT_MAX, INT_MAX, 0, 2},
        {INT_MAX, INT_MAX, INT_MAX, 0}
    };

    bellmanFord(edges, 0);
    dijkstra(graph, 0);  // Note: Dijkstra may give wrong result due to negative weight

    return 0;
}
