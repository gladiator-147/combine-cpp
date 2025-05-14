#include <iostream>
using namespace std;

#define V 6         // Number of nodes (changeable)
#define INF 99999   // Infinity equivalent

// Display distances
void display(int dist[], int n, const string landmarks[]) {
    cout << "\nLandmark\tDistance from College\n";
    for (int i = 0; i < n; i++) {
        cout << landmarks[i] << "\t\t" << dist[i] << endl;
    }
}

// Dijkstra's Algorithm
void dijkstra(int graph[V][V], int src, const string landmarks[]) {
    int dist[V];
    bool visited[V] = {false};

    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int min = INF, u;

        // Select min distance unvisited node
        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        visited[u] = true;

        // Update distances of adjacent nodes
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    cout << "\nDijkstra’s Algorithm Results:";
    display(dist, V, landmarks);
}

// Bellman-Ford Algorithm
bool bellmanFord(int graph[][3], int E, int src, const string landmarks[]) {
    int dist[V];
    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;

    // Relax edges V-1 times
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph[j][0];
            int v = graph[j][1];
            int w = graph[j][2];
            if (dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // Check for negative cycles
    for (int j = 0; j < E; j++) {
        int u = graph[j][0];
        int v = graph[j][1];
        int w = graph[j][2];
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            cout << "\nNegative weight cycle detected!\n";
            return false;
        }
    }

    cout << "\nBellman-Ford Algorithm Results:";
    display(dist, V, landmarks);
    return true;
}

// ----------- MAIN FUNCTION ---------------

int main() {
    const string landmarks[V] = {
        "College", "Library", "Hostel", "Canteen", "Station", "Mall"
    };

    // Adjacency matrix for Dijkstra (no negative weights)
    int adj[V][V] = {
        {0,  2,  4,  0,  0,  0},
        {2,  0,  1,  7,  0,  0},
        {4,  1,  0,  3,  5,  0},
        {0,  7,  3,  0,  2,  6},
        {0,  0,  5,  2,  0,  1},
        {0,  0,  0,  6,  1,  0}
    };

    dijkstra(adj, 0, landmarks); // Source = College (index 0)

    // Edge list for Bellman-Ford (supports negative weights)
    int edges[][3] = {
        {0, 1, 2}, {0, 2, 4},
        {1, 2, 1}, {1, 3, 7},
        {2, 3, 3}, {2, 4, 5},
        {3, 4, 2}, {3, 5, 6},
        {4, 5, 1}
    };
    int E = sizeof(edges) / sizeof(edges[0]);

    bellmanFord(edges, E, 0, landmarks); // Source = College

    return 0;
