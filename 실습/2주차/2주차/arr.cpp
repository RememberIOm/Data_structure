#include <iostream>
using namespace std;

class Array {
public:
	int arr_size{ 10000 };
	float* arr;

	Array() {
		srand(9999);

		this->arr = new float[10000];
		for (int i{ 0 }; i < 10000; ++i) {
			arr[i] = rand() % 30000;
		}
	}

	int At(int idx) {
		if (idx < arr_size) {
			return arr[idx];
		}
		else {
			return -1;
		}
	}

	void Set(int idx, int value) {
		arr[idx] = value;
	}

	void Delete(int idx) {
		for (int i{ idx }; i < arr_size - 1; ++i) {
			arr[idx] = arr[idx + 1];
		}

		arr[arr_size - 1] = 0;
	}

	int Find_Max() {
		int max_idx{};

		for (int i{}; i < arr_size; ++i) {
			if (arr[i] >= arr[max_idx]) {
				max_idx = i;
			}
		}

		return max_idx;
	}
};

int main() {
	Array arr_class = Array();

	int M{};
	cin >> M;

	for (int i{}; i < M; ++i) {
		string input{};
		cin >> input;

		if (input == "At") {
			int input_i{};
			cin >> input_i;

			cout << arr_class.At(input_i) << '\n';
		}
		else if (input == "Set") {
			int input_i{}, input_value{};
			cin >> input_i >> input_value;

			arr_class.Set(input_i, input_value);
		}
		else if (input == "Delete") {
			int input_i{};
			cin >> input_i;

			arr_class.Delete(input_i);
		}
		else if (input == "Find_Max") {
			int max_idx{ arr_class.Find_Max() };

			cout << arr_class.At(max_idx) << " " << max_idx << '\n';
		}
	}

	return 0;
}