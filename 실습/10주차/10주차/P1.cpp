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
	
public:
	Heap(int direction) {
		v.push_back(-1);
		this->heap_size = 0;
		this->root_index = 1;
		this->direction = direction;
	}

	void swap(int idx1, int idx2) {
		v.at(0) = v.at(idx1);
		v.at(idx1) = v.at(idx2);
		v.at(idx2) = v.at(0);
	}

	void upHeap(int idx) {
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
};

int main() {
	int N;
	cin >> N;

	Heap PQ(MAX);

	for (int i{}; i < N; ++i) {
		string cmd;
		cin >> cmd;

		if (cmd == "insert") {
			int val;
			cin >> val;
			PQ.insert(val);
		}
		else if (cmd == "size") {
			cout << PQ.size() << '\n';
		}
		else if (cmd == "isEmpty") {
			cout << static_cast<int>(PQ.isEmpty()) << '\n';
		}
		else if (cmd == "pop") {
			if (PQ.isEmpty()) {
				cout << -1 << '\n';
			}
			else {
				cout << PQ.pop() << '\n';
			}
		}
		else if (cmd == "top") {
			if (PQ.isEmpty()) {
				cout << -1 << '\n';
			}
			else {
				cout << PQ.top() << '\n';
			}
		}
		else if (cmd == "print") {
			PQ.print();
		}
		else cout << "ERROR\n";
	}

	return 0;
}