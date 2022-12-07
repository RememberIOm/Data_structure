#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int data;
    Node* par;
    vector<Node*> chi_v;

    Node(int data) : data(data), par(NULL) {}

    void setParent(Node* parent) {
        par = parent;
    }

    void insertChild(Node* child) {
        chi_v.push_back(child);
    }

    void delChild(Node* child) {
        for (int i{}; i < chi_v.size(); ++i) {
            if (chi_v.at(i) == child) {
                chi_v.erase(chi_v.begin() + i);
            }
        }
    }
};

class Tree {
public:
    Node* root;
    vector<Node*> node_list;

    Tree(int);
    int size();
    void insertNode(int, int);
    void preorder(Node*);
    void postorder(Node*);
    void recursion(Node*, int);
};

Tree::Tree(int data) {
    Node* node = new Node(data);
    root = node;
    node_list.push_back(node);
}

int Tree::size() {
    return node_list.size();
}

void Tree::insertNode(int par_data, int data) {
    for (int i{}; i < size(); ++i) {
        if (node_list.at(i)->data == par_data) {
            Node* node = new Node(data);
            node->setParent(node_list.at(i));
            node_list.at(i)->insertChild(node);
            node_list.push_back(node);

            return;
        }
    }
}

void Tree::preorder(Node* node) {
    if (!node) return;

    cout << node->data << " ";
    for (int i{}; i < node->chi_v.size(); ++i) {
        preorder(node->chi_v.at(i));
    }
}

void Tree::postorder(Node* node) {
    if (!node) return;

    for (int i{}; i < node->chi_v.size(); ++i) {
        postorder(node->chi_v.at(i));
    }
    cout << node->data << " ";
}

void Tree::recursion(Node* node, int rec) {
    if (!node) return;

    for (int i{}; i < node->chi_v.size(); ++i) {
        if (i == 0) {
            recursion(node->chi_v.at(i), rec + 1);
        }
        else {
            recursion(node->chi_v.at(i), 1);
        }
    }

    if (node->chi_v.size() == 0)
        cout << rec << " ";
}

int main() {
    int n, m;
    int num1, num2;

    cin >> n;
    for (int i{}; i < n; ++i) {
        cin >> m;
        Tree t = Tree(1);
        for (int j{}; j < m; ++j) {
            cin >> num1 >> num2;
            t.insertNode(num1, num2);
        }

        t.recursion(t.root, 1);

        if (i != n - 1)
            cout << endl;
    }

    return 0;
}
