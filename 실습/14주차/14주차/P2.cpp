#include <iostream>
#include <vector>
using namespace std;

class Vertex {
public:
	int num;
	int state;
	string data;
	vector<Vertex*> adjacent;

	Vertex(int n, string d) {
		this->num = n;
		this->state = 0;
		this->data = d;
	}
};

void BFS(Vertex* v) {
	cout << v->data;
	v->state = 1;

	vector<Vertex*> notSorted;
	for (auto v : v->adjacent) {
		notSorted.push_back(v);
	}

	vector<Vertex*> sorted;
	while (!notSorted.empty()) {
		int minNum = 500;
		int idx = -1;
		Vertex* minVertex = NULL;

		for (int i{}; i < notSorted.size(); ++i) {
			if (minNum > notSorted.at(i)->num) {
				minNum = notSorted.at(i)->num;
				idx = i;
				minVertex = notSorted.at(i);
			}
		}

		notSorted.erase(notSorted.begin() + idx);

		if (minVertex->state == 0) {
			BFS(minVertex);
		}
	}
}

int main() {
	vector<Vertex*> mapping(500);

	int N, M, K; cin >> N >> M >> K;

	for (int i{}; i < N; ++i) {
		int I;
		string C;
		cin >> I >> C;

		mapping.at(I) = new Vertex(I, C);
	}

	for (int i{}; i < M; ++i) {
		int S, D; cin >> S >> D;

		mapping.at(S)->adjacent.push_back(mapping.at(D));
		mapping.at(D)->adjacent.push_back(mapping.at(S));
	}

	BFS(mapping.at(K));

	return 0;
}