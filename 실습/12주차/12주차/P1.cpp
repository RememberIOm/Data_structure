#include <iostream>
#define NOITEM 0
#define ISITEM 1
#define AVAILABLE 2
using namespace std;

class cell {
public:
	int key;
	int value;
	int flag;

	cell() {
		key = -1;
		value = -1;
		flag = NOITEM;
	}
};

class DoubleHashTable {
private:
	cell* hashArr;
	int arrSize;
	int curSize;

public:
	DoubleHashTable(int size) {
		arrSize = size;
		curSize = 0;
		hashArr = new cell[arrSize];
	}

	int hashfunc(int key) {
		return key % arrSize;
	}

	void find(int key) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrSize;
		int curIdx = hashfunc(key) % arrSize;
		bool firstOpr = true;

		while (hashArr[curIdx].flag == ISITEM or hashArr[curIdx].flag == AVAILABLE) {
			if (hashArr[curIdx].key == key) {
				cout << "find " << key << '\n';

				return;
			}
			else if (curIdx == initial_idx and !firstOpr) {
				cout << "loop" << '\n';

				return;
			}

			++probing;
			firstOpr = false;
			curIdx = (hashfunc(key) + probing - 1) % arrSize;
		}

		cout << "don't find " << key << '\n';
	}

	void put(int key, int value) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrSize;
		int curIdx = hashfunc(key) % arrSize;
		bool firstOpr = true;

		if (isFull()) { cout << "Full" << '\n'; }
		else {
			while (hashArr[curIdx].flag == ISITEM) {
				if (curIdx == initial_idx and !firstOpr) {
					cout << "loop" << '\n';
					
					break;
				}

				++probing;
				firstOpr = false;
				curIdx = (hashfunc(key) + probing - 1) % arrSize;
			}

			hashArr[curIdx].key = key;
			hashArr[curIdx].value = value;
			hashArr[curIdx].flag = ISITEM;
		}
	}

	void erase(int key) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrSize;
		int curIdx = hashfunc(key) % arrSize;
		bool firstOpr = true;

		if (isEmpty()) { cout << "Empty" << '\n'; }
		else {
			while (hashArr[curIdx].flag == ISITEM or hashArr[curIdx].flag == AVAILABLE) {
				if (hashArr[curIdx].key == key) {
					hashArr[curIdx].flag = AVAILABLE;
					hashArr[curIdx].key = -1;
					hashArr[curIdx].value = -1;

					break;
				}
				else if (curIdx == initial_idx and !firstOpr) {
					cout << "loop" << '\n';

					break;
				}

				++probing;
				firstOpr = false;
				curIdx = (hashfunc(key) + probing - 1) % arrSize;
			}
		}

		--curSize;
	}

	bool isFull() {
		return (curSize == arrSize);
	}

	bool isEmpty() {
		return (curSize == 0);
	}

	void print() {
		for (int i{}; i < arrSize; ++i) {
			cout << hashArr[i].value << ' ';
		}
	}
};

int main() {
	int T; cin >> T;
	
	while (T--) {
		int P; cin >> P;

		DoubleHashTable table(P);

		int Q; cin >> Q;

		while (Q--) {
			int input; cin >> input;

			table.put(input, input);
		}

		table.print();
	}
}