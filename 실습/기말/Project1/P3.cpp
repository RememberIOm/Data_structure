//학과: 컴퓨터공학과 학번: 12191650 분반: 003 이름: 이준용
//학생 명예서약 (Honor Code): 나는 정직하게 시험에 응할 것을 서약합니다. _이준용_

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Vertex {
public:
	int data;
	int state;
	vector<Vertex*> adjacentList;

	Vertex(int data) {
		this->data = data;
		state = 0;
	}
};

class Graph {
public:
	vector<Vertex*> vertexList;

	Graph() {
		vertexList.resize(20001, NULL);
	}

	void insertVertex(int data) {
		vertexList.at(data) = new Vertex(data);
	}

	void insertEdge(int S, int D) {
		int isAdjacent{};
		for (Vertex* i : vertexList.at(S)->adjacentList) {
			if (i == vertexList.at(D)) {
				isAdjacent = 1;
				break;
			}
		}

		if (isAdjacent == 0) {
			vertexList.at(S)->adjacentList.push_back(vertexList.at(D));
			vertexList.at(D)->adjacentList.push_back(vertexList.at(S));
		}
		else {
			cout << -1 << '\n';
		}
	}

	void bfs(int idx) {
		queue<int> search;
		search.push(idx);
		vertexList.at(idx)->state = 1;

		while (!search.empty()) {
			cout << search.front() << ' ';

			for (Vertex* i : vertexList.at(search.front())->adjacentList) {
				if (i->state == 0) {
					search.push(i->data);
					i->state = 1;
				}
			}

			search.pop();
		}
	}
};

int main() {
	int N, M, A; cin >> N >> M >> A;
	Graph* g = new Graph();

	while (N--) {
		int I; cin >> I;

		g->insertVertex(I);
	}

	while (M--) {
		int S, D; cin >> S >> D;

		g->insertEdge(S, D);
	}

	g->bfs(A);

	return 0;
}