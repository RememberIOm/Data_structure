#include <iostream>
#include <string>
#include <vector>

using namespace std;
enum direction { MIN = 1, MAX = -1 };

class Heap {
private:
	vector<int> v;
	int heap_size;
	int root_index;
	int direction;
	
	int upHeapCnt;

public:
	Heap(int direction) {
		v.push_back(-1);
		this->heap_size = 0;
		this->root_index = 1;
		this->direction = direction;

		this->upHeapCnt = 0;
	}

	void swap(int idx1, int idx2) {
		v.at(0) = v.at(idx1);
		v.at(idx1) = v.at(idx2);
		v.at(idx2) = v.at(0);
	}

	void upHeap(int idx) {
		++upHeapCnt;

		if (idx == root_index) return;
		else {
			int parent = idx / 2;
			if (v.at(parent) * direction > v.at(idx) * direction) {
				swap(parent, idx);
				upHeap(parent);
			}
		}
	}

	void downHeap(int idx) {
		int left = idx * 2;
		int right = idx * 2 + 1;
		if (right <= heap_size) {
			if (v.at(left) * direction <= v.at(right) * direction) {
				if (v.at(left) * direction < v.at(idx) * direction) {
					swap(left, idx);
					downHeap(left);
				}
				else return;
			}
			else {
				if (v.at(right) * direction < v.at(idx) * direction) {
					swap(right, idx);
					downHeap(right);
				}
				else return;
			}
		}
		else if (left <= heap_size) {
			if (v.at(left) * direction < v.at(idx) * direction) {
				swap(left, idx);
				downHeap(left);
			}
			else return;
		}
		else return;
	}

	void insert(int e) {
		v.push_back(e);
		++heap_size;
		upHeap(heap_size);
	}

	int pop() {
		int top = v.at(root_index);
		v.at(root_index) = v.at(heap_size);
		--heap_size;
		v.pop_back();
		downHeap(root_index);

		return top;
	}

	int top() {
		return v.at(root_index);
	}

	int size() {
		return heap_size;
	}

	bool isEmpty() {
		if (heap_size == 0) return true;
		else return false;
	}

	void print() {
		if (isEmpty() == false) {
			for (int i{ root_index }; i < heap_size; ++i) {
				cout << v.at(i) << " ";
			}
			cout << v.at(heap_size) << '\n';
		}
		else cout << -1 << '\n';
	}

	int find(int x) {
		if (isEmpty() == false) return v.at(x);
	}

	const int getValue(const int& idx) {
		return this->v.at(idx);
	}

	const int getUpHeapCnt() {
		return this->upHeapCnt;
	}
};

int main() {
	int T;
	cin >> T;

	for (int i{}; i < T; ++i) {
		int N, p;
		cin >> N >> p;

		Heap PQ(MIN);

		for (int j{}; j < N; ++j) {
			int val;
			cin >> val;

			PQ.insert(val);
		}

		// First Line
		PQ.print();

		// Second Line
		cout << PQ.getValue(p) << '\n';

		// Third Line
		vector<int> tmp1, tmp2;
		for (int j{ 1 }; j <= PQ.size(); ++j) {
			tmp1.push_back(PQ.getValue(j));
		}

		for (int j{}; j < p; ++j) {
			int min{ tmp1.front() }, minIdx{};
			for (int k{ 1 }; k < tmp1.size(); ++k) {
				if (min > tmp1.at(k)) {
					min = tmp1.at(k);
					minIdx = k;
				}
			}
			tmp1.erase(tmp1.begin() + minIdx);

			tmp2.push_back(min);
		}

		cout << tmp2.back() << '\n';

		// Fourth Line
		static int upHeapCnt{};
		upHeapCnt += PQ.getUpHeapCnt();
		cout << upHeapCnt << '\n';
	}

	return 0;
}