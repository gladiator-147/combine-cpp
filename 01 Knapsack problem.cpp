#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an item
struct Item {
    int value;
    int weight;
};

// Structure to represent a node in the decision tree
struct Node {
    int level;
    int profit;
    int weight;
    int bound;
};

// Function to calculate the upper bound for a given node
int calculateBound(Node& node, int n, int W, vector<Item>& items) {
    if (node.weight >= W) {
        return 0;
    }

    int profitBound = node.profit;
    int j = node.level + 1;
    int totalWeight = node.weight;

    // Take as much as possible from the remaining items
    while (j < n && totalWeight + items[j].weight <= W) {
        totalWeight += items[j].weight;
        profitBound += items[j].value;
        j++;
    }

    // Take a fraction of the last item if needed
    if (j < n) {
        profitBound += (W - totalWeight) * items[j].value / items[j].weight;
    }

    return profitBound;
}

// Function to solve the 0/1 Knapsack problem using Branch and Bound
void knapsackBranchAndBound(vector<Item>& items, int n, int W) {
    Node root;
    root.level = -1;
    root.profit = 0;
    root.weight = 0;

    // Calculate the bound for the root node
    root.bound = calculateBound(root, n, W, items);

    // Priority queue for the nodes, here we use a simple vector
    vector<Node> pq;
    pq.push_back(root);

    int maxProfit = 0;
    while (!pq.empty()) {
        Node curr = pq.back();
        pq.pop_back();

        if (curr.level == n - 1) {
            continue;
        }

        // Generate left child (Include the current item)
        Node left = curr;
        left.level = curr.level + 1;
        left.weight += items[left.level].weight;
        left.profit += items[left.level].value;

        if (left.weight <= W && left.profit > maxProfit) {
            maxProfit = left.profit;
        }

        if (calculateBound(left, n, W, items) > maxProfit) {
            pq.push_back(left);
        }

        // Generate right child (Exclude the current item)
        Node right = curr;
        right.level = curr.level + 1;
        right.bound = calculateBound(right, n, W, items);

        if (right.bound > maxProfit) {
            pq.push_back(right);
        }
    }

    cout << "Maximum profit: " << maxProfit << endl;
}

int main() {
    int n, W;
    
    // Input the number of items and the knapsack capacity
    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);

    // Input each item's value and weight
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight for item " << i + 1 << ": ";
        cin >> items[i].value >> items[i].weight;
    }

    cout << "Enter the capacity of the knapsack: ";
    cin >> W;

    // Call the knapsack function
    knapsackBranchAndBound(items, n, W);
    return 0;
}
