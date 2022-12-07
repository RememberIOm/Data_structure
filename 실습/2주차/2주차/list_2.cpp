#include <iostream>
using namespace std;

class Node {
public:
	int data;
	Node* next;

	Node(int data) {
		this->data = data;
		this->next = NULL;
	}
};

class S_LinkedList {
private:
	Node* head;
	Node* tail;

public:
	S_LinkedList() {
		head = NULL;
		tail = NULL;
	}

	int empty() {
		if (head == NULL and tail == NULL) {
			return 1;
		}
		else {
			return 0;
		}
	}

	void addFront(int value) {
		Node* new_node = new Node(value);

		if (empty() == 0) {
			new_node->next = head;
			head = new_node;
		}
		else {
			head = new_node;
			tail = new_node;
		}
	}

	int removeFront() {
		if (empty() == 0) {
			Node* pre_head{ head };
			int output{ pre_head->data };
			head = pre_head->next;
			if (head == NULL) {
				tail = NULL;
			}
			delete pre_head;

			return output;
		}
		else {
			return -1;
		}
	}

	int front() {
		if (empty() == 0) {
			return head->data;
		}
		else {
			return -1;
		}
	}
};

int main() {
	S_LinkedList* list = new S_LinkedList();
	int N{};
	cin >> N;

	for (int i{}; i < N; ++i) {
		string command{};
		cin >> command;

		if (command == "addFront") {
			int value{};
			cin >> value;

			list->addFront(value);
		}
		else if (command == "removeFront") {
			cout << list->removeFront() << '\n';
		}
		else if (command == "front") {
			cout << list->front() << '\n';
		}
		else if (command == "empty") {
			cout << list->empty() << '\n';
		}
	}

	return 0;
}