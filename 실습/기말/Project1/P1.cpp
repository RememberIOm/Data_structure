//학과: 컴퓨터공학과 학번: 12191650 분반: 003 이름: 이준용
//학생 명예서약 (Honor Code): 나는 정직하게 시험에 응할 것을 서약합니다. _이준용_

#include <iostream>
#include <vector>
using namespace std;

class Heap {
public:
	vector<int> heapList;
	int heapsize;

	Heap() {
		heapList.resize(20001);
		heapsize = 0;
	}

	void upHeap(int idx) {
		if (idx != 1) {
			if (heapList.at(idx) < heapList.at(idx / 2)) {
				int temp = heapList.at(idx);
				heapList.at(idx) = heapList.at(idx / 2);
				heapList.at(idx / 2) = temp;

				upHeap(idx / 2);
			}
		}
	}

	void downHeap(int idx) {
		if (heapList.at(idx * 2) != 0 or heapList.at(idx * 2 + 1) != 0) {
			int minIdx;
			if (heapList.at(idx * 2) < heapList.at(idx * 2 + 1) or heapList.at(idx * 2 + 1) == 0) {
				minIdx = idx * 2;
			}
			else {
				minIdx = idx * 2 + 1;
			}

			if (heapList.at(idx) > heapList.at(minIdx)) {
				int temp = heapList.at(idx);
				heapList.at(idx) = heapList.at(minIdx);
				heapList.at(minIdx) = temp;

				downHeap(minIdx);
			}
		}
	}

	void insert(int data) {
		heapList.at(heapsize + 1) = data;

		upHeap(++heapsize);
	}

	int remove() {
		int output{ heapList.at(1) };

		if (output != 0) {
			heapList.at(1) = heapList.at(heapsize);
			heapList.at(heapsize) = 0;

			--heapsize;

			downHeap(1);

			return output;
		}

		return -1;
	}

	void print() {
		for (int i{ 1 }; i <= heapsize; ++i) {
			cout << heapList.at(i) << ' ';
		}
	}

	int isEmpty() {
		if (heapsize) {
			return 0;
		}
		else {
			return 1;
		}
	}
};

int main() {
	int T; cin >> T;

	while (T--) {
		Heap* h = new Heap();
		int N; cin >> N;

		while (N--) {
			int input; cin >> input;
			h->insert(input);
		}

		int p; cin >> p;

		for (int out{ h->remove() };; out = h->remove()) {
			if (out == p) {
				break;
			}
			else if (out == -1) {
				break;
			}
		}

		if (h->isEmpty()) {
			cout << "Empty\n";
		}
		else {
			h->print();
			cout << '\n';
		}
	}

	return 0;
}