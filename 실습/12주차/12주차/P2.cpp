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

	int hashfunc2(int key) {
		return (17 - (key % 17));
	}

	void find(int key) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrSize;
		int curIdx = hashfunc(key) % arrSize;
		bool firstOpr = true;

		while (hashArr[curIdx].flag == ISITEM or hashArr[curIdx].flag == AVAILABLE) {
			if (hashArr[curIdx].key == key) {
				cout << "True " << probing << '\n';

				return;
			}
			else if (curIdx == initial_idx and !firstOpr) {
				cout << "loop" << '\n';

				return;
			}

			++probing;
			firstOpr = false;
			curIdx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrSize;
		}

		cout << "False " << probing << '\n';
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
				curIdx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrSize;
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
				curIdx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrSize;
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
};

int main() {
	int T; cin >> T;

	while (T--) {
		int P; cin >> P;

		DoubleHashTable table(P);

		int Qput; cin >> Qput;

		while (Qput--) {
			int input; cin >> input;

			table.put(input, input);
		}

		int Qfind; cin >> Qfind;

		while (Qfind--) {
			int R; cin >> R;

			table.find(R);
		}
	}
}