#include <iostream>
#include <queue>
#include <sstream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};

Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void levelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front(); q.pop();
        cout << curr->data << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

bool search(Node* root, int key) {
    if (!root) return false;
    if (key == root->data) return true;
    if (key < root->data) return search(root->left, key);
    else return search(root->right, key);
}

int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

Node* findMin(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;
    if (key < root->data) root->left = deleteNode(root->left, key);
    else if (key > root->data) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void mirror(Node*& root) {
    if (!root) return;
    mirror(root->left);
    mirror(root->right);
    swap(root->left, root->right);
}

int main() {
    Node* root = NULL;
    string line;
    cout << "Enter space-separated values to insert into BST:\n";
    getline(cin, line);
    stringstream ss(line);
    int val;
    while (ss >> val)
        root = insert(root, val);

    cout << "\nInorder Traversal: ";
    inorder(root);
    cout << "\nLevel Order Display: ";
    levelOrder(root);
    cout << "\nHeight of Tree: " << height(root) << endl;

    cout << "\nEnter value to search: ";
    int key;
    cin >> key;
    cout << (search(root, key) ? "Found." : "Not Found.") << endl;

    cout << "\nEnter value to delete: ";
    cin >> key;
    root = deleteNode(root, key);
    cout << "After Deletion - Level Order: ";
    levelOrder(root);
    cout << endl;

    mirror(root);
    cout << "\nAfter Mirroring - Inorder: ";
    inorder(root);
    cout << endl;

    return 0;
}
