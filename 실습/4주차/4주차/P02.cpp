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
	int dequeue();
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

int LinkedQueue::dequeue() {
	int output;
	if (isEmpty() == true) output = -1;
	else {
		output = S->removeFront();
		n--;
	}

	return output;
}

int main() {
	int T;
	cin >> T;

	while (T--) {
		LinkedQueue P1;
		LinkedQueue P2;
		int N;
		cin >> N;
		for (int i{}; i < N; ++i) {
			int hp;
			cin >> hp;
			P1.enqueue(hp);
		}
		for (int i{}; i < N; ++i) {
			int hp;
			cin >> hp;
			P2.enqueue(hp);
		}

		int P1Point{}, P2Point{}, P1bonusHp{}, P2bonusHp{};
		for (int i{}; i < N; ++i) {
			int afterAtk = P1.dequeue() + P1bonusHp - P2.dequeue() - P2bonusHp;
			if (afterAtk > 0) {
				P1bonusHp = afterAtk - 1;
				P2bonusHp = 0;
				++P1Point;
			}
			else if (afterAtk < 0) {
				P1bonusHp = 0;
				P2bonusHp = (-1 * afterAtk) - 1;
				++P2Point;
			}
			else {
				P1bonusHp = 0;
				P2bonusHp = 0;
			}
		}

		if (P1Point > P2Point) cout << 1 << '\n';
		else if (P1Point < P2Point) cout << 2 << '\n';
		else cout << 0 << '\n';
	}

	return 0;
}