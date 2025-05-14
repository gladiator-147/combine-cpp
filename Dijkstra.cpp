#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define V 5  // Number of landmarks

// Function to find the vertex with minimum distance
int minDistance(vector<int>& dist, vector<bool>& visited) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Dijkstra's Algorithm
void dijkstra(int graph[V][V], int src) {
    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);

    dist[src] = 0;

    for (int count = 0; count < V-1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = true;

        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Print the shortest distances
    cout << "Landmark\tDistance from College\n";
    string places[V] = {"College", "Library", "Hostel", "Canteen", "Playground"};
    for (int i = 0; i < V; i++)
        cout << places[i] << "\t\t" << dist[i] << "\n";
}

int main() {
    // Adjacency Matrix
    int graph[V][V] = {
        // College, Library, Hostel, Canteen, Playground
        {0, 2, 4, 1, 0},     // College
        {2, 0, 1, 2, 0},     // Library
        {4, 1, 0, 0, 3},     // Hostel
        {1, 2, 0, 0, 5},     // Canteen
        {0, 0, 3, 5, 0}      // Playground
    };

    dijkstra(graph, 0);  // College is source
    return 0;
}
