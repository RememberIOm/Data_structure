#include <iostream>
using namespace std;

class Node {
public:
	int data;
	Node* leftChild;
	Node* rightChild;
	Node* parent;

	Node() {
		this->leftChild = NULL;
		this->rightChild = NULL;
		this->parent = NULL;
	}

	Node(int data) {
		this->data = data;
		this->leftChild = NULL;
		this->rightChild = NULL;
		this->parent = NULL;
	}
};

class binarySearchTree {
private:
	Node* root;

public:
	binarySearchTree() { this->root = NULL; }

	void insert(int inputData) {
		Node* newNode = new Node(inputData);
		Node* saveNode = NULL;

		if (root == NULL) { root = newNode; }
		else {
			Node* curNode = root;

			while (curNode != NULL) {
				saveNode = curNode;
				if (curNode->data == inputData) {
					cout << "Duplication" << '\n';

					return;
				}
				else if (curNode->data > inputData) {
					curNode = curNode->leftChild;
				}
				else {
					curNode = curNode->rightChild;
				}
			}

			if (saveNode->data > inputData) {
				newNode->parent = saveNode;
				saveNode->leftChild = newNode;
			}
			else {
				newNode->parent = saveNode;
				saveNode->rightChild = newNode;
			}
		}
	}

	Node* find(int inputData) {
		Node* curNode = root;

		while (curNode != NULL) {
			if (curNode->data == inputData) {
				return curNode;
			}
			else if (curNode->data > inputData) {
				curNode = curNode->leftChild;
			}
			else {
				curNode = curNode->rightChild;
			}
		}

		return NULL;
	}

	Node* min_findNode(Node* _Node) {
		Node* curNode = _Node;
		Node* saveNode = NULL;

		while (curNode != NULL) {
			saveNode = curNode;
			curNode = curNode->leftChild;
		}

		return saveNode;
	}

	Node* max_findNode(Node* _Node) {
		Node* curNode = _Node;
		Node* saveNode = NULL;

		while (curNode != NULL) {
			saveNode = curNode;
			curNode = curNode->rightChild;
		}

		return saveNode;
	}

	void erase(int data) {
		Node* curNode = find(data);
		int numOfchild = bool(curNode->leftChild) + bool(curNode->rightChild);

		if (numOfchild == 0) {
			if (curNode == root) {
				root = NULL;
			}
			else {
				if (curNode->parent->data > curNode->data) {
					curNode->parent->leftChild = NULL;
				}
				else {
					curNode->parent->rightChild = NULL;
				}
			}

			delete curNode;
		}
		else if (numOfchild == 2) {
			Node* minNode = min_findNode(curNode->rightChild);
			int data = minNode->data;
			erase(minNode->data);
			curNode->data = data;
		}
		else if (numOfchild == 1) {
			if (curNode == root) {
				if (curNode->leftChild != NULL) {
					root = curNode->leftChild;
				}
				else {
					root = curNode->rightChild;
				}
			}
			else {
				Node* curParent = curNode->parent;
				Node* child = (curNode->leftChild) ? curNode->leftChild : curNode->rightChild;

				if (curParent->data > child->data) {
					curParent->leftChild = child;
					child->parent = curParent;
				}
				else {
					curParent->rightChild = child;
					child->parent = curParent;
				}
			}

			delete curNode;
		}
	}

	void preorderPrint(Node* curNode) {
		if (curNode != NULL) {
			cout << curNode->data << " ";
			preorderPrint(curNode->leftChild);
			preorderPrint(curNode->rightChild);
		}
	}

	void preorder() {
		preorderPrint(root);
		cout << '\n';
	}

	void inorderPrint(Node* curNode) {
		if (curNode != NULL) {
			inorderPrint(curNode->leftChild);
			cout << curNode->data << " ";
			inorderPrint(curNode->rightChild);
		}
	}

	void inorder() {
		if (root == NULL) {
			cout << "Empty";
		}
		else {
			inorderPrint(root);
		}
		
		cout << '\n';
	}
};

int main() {
	int T;
	cin >> T;

	for (int i{}; i < T; ++i) {
		binarySearchTree tree;
		int P;
		cin >> P;

		for (int j{}; j < P; ++j) {
			int N;
			cin >> N;
			tree.insert(N);
		}

		int Q;
		cin >> Q;

		for (int j{}; j < Q; ++j) {
			int N;
			cin >> N;
			tree.erase(N);
		}

		tree.inorder();
	}

	return 0;
}