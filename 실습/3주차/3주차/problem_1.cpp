#include <iostream>
using namespace std;

class Array_Stack {
public:
	int* Stack;
	int capacity;
	int t;

	Array_Stack(int capacity) {
		this->capacity = capacity;
		this->Stack = new int[capacity];
		this->t = -1;
	}

	int size() {
		return t + 1;
	}

	bool empty() {
		if (t == -1) return true;
		else return false;
	}

	int top() {
		if (empty()) return -1;
		else return Stack[t];
	}

	void push(int e) {
		Stack[++t] = e;
	}

	int pop() {
		if (empty()) return -1;
		return Stack[t--];
	}
};

int main() {
	int N{};
	cin >> N;

	Array_Stack* current = new Array_Stack(1000000);

	for (int i{}; i < N; ++i) {
		string command{};
		cin >> command;

		if (command == "empty") {
			if (current->empty()) cout << "1" << '\n';
			else cout << "0" << '\n';
		}
		else if (command == "top") {
			cout << current->top() << '\n';
		}
		else if (command == "push") {
			int value{};
			cin >> value;

			current->push(value);
		}
		else if (command == "pop") {
			cout << current->pop() << '\n';
		}
		else if (command == "size") {
			cout << current->size() << '\n';
		}
	}

	return 0;
}