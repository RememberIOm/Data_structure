//�а�: ��ǻ�Ͱ��а� �й�: 12191650 �й�: 003 �̸�: ���ؿ�
//�л� ������ (Honor Code): ���� �����ϰ� ���迡 ���� ���� �����մϴ�. _���ؿ�_

#include <iostream>
#include <vector>
using namespace std;

class HashTable {
public:
	vector<int> hash;

	HashTable(int P) {
		hash.resize(P, -1);
	}

	int hashfunc(int key) {
		return key % hash.size();
	}

	void insert(int key) {
		int idx = hashfunc(key);

		while (hash.at(idx) != -1) {
			++idx;
			idx %= hash.size();
		}

		hash.at(idx) = key;
	}

	void remove(int key) {
		int idx = hashfunc(key);
		int saveIdx = idx;

		while (hash.at(idx) != key) {
			if (hash.at(idx) == -1) {
				break;
			}

			++idx;
			idx %= hash.size();

			if (saveIdx == idx) {
				break;
			}
		}

		if (hash.at(idx) == key) {
			hash.at(idx) = 0;
		}
	}

	void print() {
		for (int i : hash) {
			cout << i << ' ';
		}
	}
};

int main() {
	int T; cin >> T;

	while (T--) {
		int P; cin >> P;
		HashTable* h = new HashTable(P);

		int Q; cin >> Q;

		while (Q--) {
			int key; cin >> key;

			h->insert(key);
		}

		int R; cin >> R;

		while (R--) {
			int key; cin >> key;

			h->remove(key);
		}

		h->print();
		cout << '\n';
	}

	return 0;
}