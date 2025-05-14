#include <iostream>
using namespace std;

#define MAX 100
#define INF 99999  // Large value used as infinity

struct Edge {
    int u, v, weight;
};

// ---------- KRUSKAL'S HELPERS ------------

void swap(Edge &a, Edge &b) {
    Edge temp = a;
    a = b;
    b = temp;
}

void bubbleSort(Edge edges[], int E) {
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight)
                swap(edges[j], edges[j + 1]);
        }
    }
}

int find(int parent[], int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent, parent[i]);
}

void unionSet(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int kruskalMST(int V, Edge edges[], int E) {
    bubbleSort(edges, E);

    int parent[MAX], rank[MAX];
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int totalCost = 0;
    cout << "\nEdges in Kruskal's MST:\n";

    for (int i = 0, e = 0; i < E && e < V - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int setU = find(parent, u);
        int setV = find(parent, v);

        if (setU != setV) {
            cout << u << " - " << v << " : " << edges[i].weight << endl;
            totalCost += edges[i].weight;
            unionSet(parent, rank, setU, setV);
            e++;
        }
    }

    return totalCost;
}

// ---------- PRIM'S ALGORITHM ------------

int primMST(int graph[MAX][MAX], int V) {
    bool selected[MAX] = {false};
    int key[MAX];
    int parent[MAX];

    for (int i = 0; i < V; i++) {
        key[i] = INF;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < V - 1; count++) {
        int minKey = INF, u = -1;
        for (int v = 0; v < V; v++) {
            if (!selected[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        selected[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !selected[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    int totalCost = 0;
    cout << "\nEdges in Prim's MST:\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << " : " << graph[i][parent[i]] << endl;
        totalCost += graph[i][parent[i]];
    }

    return totalCost;
}

// ---------- MAIN FUNCTION ------------

int main() {
    int V, E;
    cout << "Enter number of offices (vertices): ";
    cin >> V;
    cout << "Enter number of connections (edges): ";
    cin >> E;

    Edge edges[MAX];
    int graph[MAX][MAX] = {0};

    cout << "Enter edges (from to cost):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
        graph[u][v] = w;
        graph[v][u] = w;
    }

    int kCost = kruskalMST(V, edges, E);
    cout << "Total cost using Kruskal's Algorithm: " << kCost << endl;

    int pCost = primMST(graph, V);
    cout << "Total cost using Prim's Algorithm: " << pCost << endl;

    return 0;
}
