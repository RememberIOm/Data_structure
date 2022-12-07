#include <iostream>
using namespace std;

template <typename T>
class Array_Stack {
public:
	T* Stack;
	int capacity;
	int t;

	Array_Stack(int capacity) {
		this->capacity = capacity;
		this->Stack = new T[capacity];
		this->t = -1;
	}

	int size() {
		return t + 1;
	}

	bool empty() {
		if (t == -1) return true;
		else return false;
	}

	T top() {
		if (empty()) return -1;
		else return Stack[t];
	}

	void push(int e) {
		Stack[++t] = e;
	}

	T pop() {
		if (empty()) return -1;
		return Stack[t--];
	}
};

bool isOper(char item) {
	if (item == '+' || item == '-' || item == '*') {
		return true;
	}
	else return false;
}

int getOper_order(char op) {
	switch (op)
	{
	case '*':
		return 2;
	case '+':
		return 1;
	case '-':
		return 1;
	case '(':
		return 0;
	default:
		return -1;
		break;
	}
}

int compareOper(char op1, char op2) {
	int op1Prec = getOper_order(op1);
	int op2Prec = getOper_order(op2);

	if (op1Prec > op2Prec)
		return 1;
	else if (op1Prec < op2Prec)
		return -1;
	else
		return 0;
}

int main() {
	int N{};
	cin >> N;

	for (int i{}; i < N; ++i) {
		Array_Stack<char>* expStk = new Array_Stack<char>(1000000);
		Array_Stack<char>* finalStk = new Array_Stack<char>(1000000);
		string input{};
		cin >> input;

		for (char j : input) {
			if (isOper(j)) {
				if (!expStk->empty() && compareOper(expStk->top(), j) >= 0) {
					finalStk->push(expStk->pop());
				}
				
				expStk->push(j);
			}
			else {
				if (j == '(')
					expStk->push(j);
				else if (j == ')') {
					char moveExp{ expStk->pop() };
					while (moveExp != '(') {
						finalStk->push(moveExp);

						moveExp = expStk->pop();
					}
				}
				else
					finalStk->push(j);
			}
		}

		string output{};
		while (!finalStk->empty()) {
			output = finalStk->pop() + output;
		}
		while (!expStk->empty()) {
			output += expStk->pop();
		}

		cout << output << '\n';
	}

	return 0;
}