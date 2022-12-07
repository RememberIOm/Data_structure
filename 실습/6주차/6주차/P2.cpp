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
private:
    Node* root;
    vector<Node*> node_list;
    
public:
    Tree(int);
    int size();
    void insertNode(int, int);
    int findDepth(int);
};

Tree::Tree(int data) {
    root = new Node(data);
    node_list.push_back(root);
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

int Tree::findDepth(int data) {
    int output{};
    Node* curNode;
    for (Node* i : node_list) {
        if (i->data == data) {
            curNode = i;
        }
    }
    
    for (; curNode->data != 1; ++output) {
        curNode = curNode->par;
    }
    
    return output;
}

int main() {
    int N, M;
    cin >> N >> M;
    
    Tree t = Tree(1);
    for (int i{}; i < N; ++i) {
        int par, data;
        cin >> par >> data;
        t.insertNode(par, data);
    }
    
    for (int i{}; i < M; ++i) {
        int data;
        cin >> data;
        
        cout << t.findDepth(data) << endl;
    }
    
    return 0;
}
