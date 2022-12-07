#include <iostream>
using namespace std;

class Array {
private:
	int arr[10000];
	int value_num{};

public:
	Array() {
		for (int i{}; i < 10000; ++i) {
			arr[i] = 0;
		}
	}

	int at(int idx) {
		if (arr[idx] != 0) {
			return arr[idx];
		}
		else {
			return 0;
		}
	}

	int set(int idx, int value) {
		if (arr[idx] != 0) {
			arr[idx] = value;

			return 1;
		}
		else {
			return 0;
		}
	}

	void add(int idx, int value) {
		if (arr[idx] != 0) {
			for (int i{ value_num++ }; i > idx; --i) {
				arr[i] = arr[i - 1];
			}

			arr[idx] = value;
		}
		else {
			arr[value_num++] = value;
		}
	}
};

int main() {
	Array* array = new Array();
	int M{};
	cin >> M;

	for (int i{}; i < M; ++i) {
		string input{};
		cin >> input;

		if (input == "at") {
			int idx{};
			cin >> idx;

			cout << array->at(idx) << '\n';
		}
		else if (input == "set") {
			int idx{}, value{};
			cin >> idx >> value;

			if (array->set(idx, value) == 0) {
				cout << 0 << '\n';
			}
		}
		else if (input == "add") {
			int idx{}, value{};
			cin >> idx >> value;

			array->add(idx, value);
		}
	}

	return 0;
}