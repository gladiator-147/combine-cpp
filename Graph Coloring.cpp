#include <iostream>
#include <vector>
using namespace std;

// Function to check if it's safe to color vertex 'v' with color 'c'
bool isSafe(int v, vector<vector<int>>& graph, vector<int>& color, int c, int V) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c) // If adjacent vertex has the same color
            return false;
    }
    return true;
}

// Backtracking function to solve the graph coloring problem
bool graphColoringUtil(vector<vector<int>>& graph, vector<int>& color, int V, int m, int v) {
    // If all vertices are assigned a color, return true
    if (v == V)
        return true;

    // Try different colors for vertex v
    for (int c = 1; c <= m; c++) {
        // Check if it's safe to color vertex v with color c
        if (isSafe(v, graph, color, c, V)) {
            color[v] = c;
            // Recur to assign colors to the next vertex
            if (graphColoringUtil(graph, color, V, m, v + 1))
                return true;
            // If assigning color c doesn't lead to a solution, backtrack
            color[v] = 0;
        }
    }
    return false;
}

// Main function to solve the graph coloring problem
bool graphColoring(vector<vector<int>>& graph, int V, int m) {
    vector<int> color(V, 0); // Initialize all vertices with no color
    if (!graphColoringUtil(graph, color, V, m, 0)) {
        cout << "Solution does not exist!" << endl;
        return false;
    }
    cout << "Solution found: ";
    for (int i = 0; i < V; i++) {
        cout << color[i] << " "; // Display the color assigned to each vertex
    }
    cout << endl;
    return true;
}

int main() {
    int V = 4; // Number of vertices
    int m = 3; // Number of colors
    vector<vector<int>> graph = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    graphColoring(graph, V, m);
    return 0;
}