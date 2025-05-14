#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

#define N 4
#define INF 99999

// Structure to represent a node in the search tree
struct Node {
    vector<int> path;
    vector<bool> visited;
    int level;
    int cost;
    int bound;

    // Priority is based on bound (lower is better)
    bool operator>(const Node& other) const {
        return bound > other.bound;
    }
};

// Function to calculate the bound (lower bound of total cost)
int calculateBound(const Node& node, const vector<vector<int>>& dist) {
    int bound = node.cost;

    for (int i = 0; i < N; i++) {
        if (!node.visited[i]) {
            int min1 = INF;
            for (int j = 0; j < N; j++) {
                if (i != j && (!node.visited[j] || j == node.path[0])) {
                    min1 = min(min1, dist[i][j]);
                }
            }
            bound += min1;
        }
    }
    return bound;
}

void tspBranchAndBound(const vector<vector<int>>& dist) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // Start from node 0
    Node root;
    root.path.push_back(0);
    root.visited = vector<bool>(N, false);
    root.visited[0] = true;
    root.level = 1;
    root.cost = 0;
    root.bound = calculateBound(root, dist);

    pq.push(root);

    int minCost = INF;
    vector<int> bestPath;

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        if (curr.bound >= minCost) continue;

        if (curr.level == N) {
            int lastCity = curr.path.back();
            int returnCost = dist[lastCity][0];

            if (returnCost != 0) {
                int totalCost = curr.cost + returnCost;
                if (totalCost < minCost) {
                    minCost = totalCost;
                    bestPath = curr.path;
                    bestPath.push_back(0); // complete the cycle
                }
            }
            continue;
        }

        int currentCity = curr.path.back();

        for (int i = 0; i < N; i++) {
            if (!curr.visited[i]) {
                Node child = curr;
                child.path.push_back(i);
                child.visited[i] = true;
                child.level = curr.level + 1;
                child.cost += dist[currentCity][i];
                child.bound = calculateBound(child, dist);

                if (child.bound < minCost) {
                    pq.push(child);
                }
            }
        }
    }

    cout << "Minimum cost: " << minCost << endl;
    cout << "Path: ";
    for (int city : bestPath) {
        cout << city << " ";
    }
    cout << endl;
}

int main() {
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    tspBranchAndBound(dist);
    return 0;
}
