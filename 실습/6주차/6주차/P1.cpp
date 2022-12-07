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
    void delNode(int);
    void printChi(int);
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
void Tree::delNode(int data) {
    Node* nownode;
    Node* par;
    
    for (int i{}; i < node_list.size(); ++i) {
        if (node_list.at(i)->data == data) {
            nownode = node_list.at(i);
            if (nownode == root) {
                return;
            }
            
            par = nownode->par;
            for (Node*& child : nownode->chi_v) {
                par->insertChild(child);
                child->par = par;
            }
            
            par->delChild(nownode);
            node_list.erase(node_list.begin() + i);
            delete nownode;
        }
    }
    
    return;
}
void Tree::printChi(int data) {
    for (int i{}; i < size(); ++i) {
        if (node_list.at(i)->data == data) {
            if (node_list.at(i)->chi_v.size() == 0) {
                cout << '0' << endl;
                return;
            }
            for (int j{}; j < node_list.at(i)->chi_v.size(); ++j) {
                cout << node_list.at(i)->chi_v.at(j)->data << ' ';
            }
            cout << endl;
            return;
        }
    }
}

int main() {
    int n;
    cin >> n;
    
    Tree t = Tree(1);
    for (int i{}; i < n; ++i) {
        string str;
        cin >> str;
        if (str == "insert") {
            int par, data;
            cin >> par >> data;
            t.insertNode(par, data);
        }
        else if (str == "delete") {
            int data;
            cin >> data;
            t.delNode(data);
        }
        else if (str == "print") {
            int data;
            cin >> data;
            t.printChi(data);
        }
    }
    
    return 0;
}
