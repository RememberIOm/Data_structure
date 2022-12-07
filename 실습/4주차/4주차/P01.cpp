#include <iostream>
using namespace std;

class Node {
public:
	Node(int data);
	int data;
	Node* next;
};

Node::Node(int data) {
	this->data = data;

	this->next = NULL;
}

class LinkedList {
public:
	Node* f;
	Node* r;
	LinkedList();
	int front();
	int end();
	void addEnd(int data);
	int removeFront();
};

LinkedList::LinkedList() {
	this->f = NULL;
	this->r = NULL;
}

int LinkedList::front() {
	return f->data;
}

int LinkedList::end() {
	return r->data;
}

void LinkedList::addEnd(int data) {
	Node* newNode = new Node(data);
	if (f == NULL) {
		f = r = newNode;
	}
	else {
		r->next = newNode;
		r = newNode;
	}
}

int LinkedList::removeFront() {
	if (f != NULL) {
		Node* tmp = f;
		cout << f->data << endl;
		int tmp_int = f->data;
		f = f->next;
		delete tmp;

		return tmp_int;
	}
}

class LinkedQueue {
public:
	LinkedList* S;
	int n;
	LinkedQueue();
	int size();
	int isEmpty();
	int front();
	int rear();
	void enqueue(int e);
	void dequeue();
};

LinkedQueue::LinkedQueue() {
	this->S = new LinkedList();
	this->n = 0;
}

int LinkedQueue::size() {
	return n;
}

int LinkedQueue::isEmpty() {
	if (n == 0) return 1;
	else return 0;
}

int LinkedQueue::front() {
	if (isEmpty() == true) return -1;
	else return S->front();
}

int LinkedQueue::rear() {
	if (isEmpty() == true) return -1;
	else return S->end();
}

void LinkedQueue::enqueue(int e) {
	n++;
	S->addEnd(e);
}

void LinkedQueue::dequeue() {
	if (isEmpty() == true) cout << "Empty" << endl;
	else {
		S->removeFront();
		n--;
	}
}

int main() {
	int maxSize;
	cin >> maxSize;
	int N;
	cin >> N;
	LinkedQueue Q;

	while (N--) {
		string cmd;
		cin >> cmd;
		if (cmd == "enqueue") {
			int input;
			cin >> input;

			if (Q.size() < maxSize)
				Q.enqueue(input);
			else
				cout << "Full" << '\n';
		}
		else if (cmd == "dequeue") {
			Q.dequeue();
		}
		else if (cmd == "size") {
			cout << Q.size() << '\n';
		}
		else if (cmd == "isEmpty") {
			cout << Q.isEmpty() << '\n';
		}
		else if (cmd == "front") {
			if (Q.front() == -1) cout << "Empty" << '\n';
			else cout << Q.front() << '\n';
		}
		else if (cmd == "rear") {
			if (Q.rear() == -1) cout << "Empty" << '\n';
			else cout << Q.rear() << '\n';
		}
	}

	return 0;
}