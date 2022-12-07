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
public:
	Node* head;
	Node* tail;

	S_LinkedList() {
		head = NULL;
		tail = NULL;
	}

	int Empty() {
		if (head == NULL && tail == NULL) {
			return 1;
		}
		else {
			return 0;
		}
	}

	int List_size() {
		int list_size = 1;
		Node* cur_node;

		cur_node = head;
		if (Empty()) {
			return 0;
		}
		else {
			while (cur_node != tail) {
				cur_node = cur_node->next;
				++list_size;
			}
		}

		return list_size;
	}

	int Print() {
		Node* cur_node = head;

		if (Empty()) {
			return -1;
		}
		else {
			cout << cur_node->data << ' ';

			while (cur_node != tail) {
				cur_node = cur_node->next;
				cout << cur_node->data << ' ';
			}
		}
	}

	void Append(int data) {
		if (Empty()) {
			Node* node = new Node(data);

			head = node;
			tail = node;
		}
		else {
			Node* node = new Node(data);

			tail->next = node;
			tail = node;
		}
	}

	int Delete(int idx) {
		if (Empty() || List_size() < idx) {
			return -1;
		}
		else if (idx == 0) {
			int output{head->data};
			Node* pre_head = head;
			head = head->next;
			delete pre_head;

			return output;
		}
		else {
			int cur_idx{ 1 };
			Node* pre_node = head;
			Node* cur_node = head->next;

			while (idx != cur_idx) {
				pre_node = cur_node;
				cur_node = cur_node->next;

				++cur_idx;
			}

			pre_node->next = cur_node->next;
			delete cur_node;
		}
	}

	void Insert(int idx, int data) {
		Node* new_node = new Node(data);

		if (idx == 0) {
			if (Empty()) {
				head = new_node;
				tail = new_node;
			}
			else {
				new_node->next = head;
				head = new_node;
			}
		}
		else if (idx < 0 || idx > List_size()) {
			return;
		}
		else if (idx == List_size()) {
			Append(data);
		}
		else {

		}
	}
};

int main() {
	S_LinkedList list_class = S_LinkedList();
	int N{};
	cin >> N;

	for (int i{}; i < N; ++i) {
		string input{};
		cin >> input;

		if (input == "addFront") {
			int input_data{};
			cin >> input_data;
			list_class.Insert(0, input_data);
		}
		else if (input == "removeFront") {
			cout << list_class.Delete(0) << '\n';
		}
		else if (input == "front") {
			if (list_class.Empty() == 0) {
				cout << list_class.head->data << '\n';
			}
			else {
				cout << -1 << '\n';
			}
		}
		else if (input == "empty") {
			if (list_class.Empty() == 0) {
				cout << 0 << '\n';
			}
			else {
				cout << 1 << '\n';
			}
		}
	}
}