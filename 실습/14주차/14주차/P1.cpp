#include <iostream>
#include <vector>
using namespace std;

#define MappingSize 501

class Vertex {
public:
	Vertex* prev;
	Vertex* next;
	int degree;
	int data;
	string strData;
	int state;

	Vertex(int data, string strData) {
		this->degree = 0;
		this->data = data;
		this->strData = strData;
		this->state = 0;
	}

	void increase_degree() {
		++this->degree;
	}

	void decrease_degree() {
		--this->degree;
	}
};

class edge {
public:
	edge* prev;
	edge* next;
	Vertex* source;
	Vertex* destination;
	string data;
	int state;

	edge(Vertex* a, Vertex* b, string data) {
		this->source = a;
		this->destination = b;
		this->data = data;
		this->state = 0;
	}
};

class DoublyVertexLinkedList {
public:
	Vertex* head;
	Vertex* tail;
	int listSize;

	DoublyVertexLinkedList() {
		this->head = NULL;
		this->tail = NULL;
		listSize = 0;
	}

	void insert(Vertex* insertVertex) {
		if (this->head == NULL) {
			head = insertVertex;
			tail = insertVertex;
		}
		else {
			tail->next = insertVertex;
			insertVertex->prev = tail;
			tail = insertVertex;
		}
		++listSize;
	}

	void remove(Vertex* delVertex) {
		if (delVertex == head || delVertex == tail) {
			if (delVertex == head && delVertex != tail) {
				Vertex* temp = head;
				head = head->next;
				head->prev = NULL;
				delete temp;
			}
			else if (delVertex == tail && delVertex != head) {
				Vertex* temp = tail;
				tail = tail->prev;
				tail->next = NULL;
				delete temp;
			}
			else
				head = tail = NULL;
		}
		else {
			delVertex->prev->next = delVertex->next;
			delVertex->next->prev = delVertex->prev;
			delete delVertex;
		}
		--listSize;
	}
};

class DoublyEdgeLinkedList {
public:
	edge* head;
	edge* tail;
	int listSize;

	DoublyEdgeLinkedList() {
		this->head = NULL;
		this->tail = NULL;
		listSize = 0;
	}

	void insert(edge* insertEdge) {
		if (this->head == NULL) {
			head = insertEdge;
			tail = insertEdge;
		}
		else {
			tail->next = insertEdge;
			insertEdge->prev = tail;
			tail = insertEdge;
		}
		++listSize;
	}

	void remove(edge* delEdge) {
		if (delEdge == head || delEdge == tail) {
			if (delEdge == head && delEdge != tail) {
				edge* temp = head;
				head = head->next;
				head->prev = NULL;
				delete temp;
			}
			else if (delEdge == tail && delEdge != head) {
				edge* temp = tail;
				tail = tail->prev;
				tail->next = NULL;
				delete temp;
			}
			else
				head = tail = NULL;
		}
		else {
			delEdge->prev->next = delEdge->next;
			delEdge->next->prev = delEdge->prev;
			delete delEdge;
		}
		--listSize;
	}
};

class graph {
public:
	edge*** edgeMatrix;
	DoublyEdgeLinkedList* EdgeList;
	DoublyVertexLinkedList* VertexList;
	int vertexSize;
	int mappingTable[MappingSize];

	graph() {
		this->VertexList = new DoublyVertexLinkedList();
		this->EdgeList = new DoublyEdgeLinkedList();
		this->vertexSize = 0;

		for (int i = 0; i < MappingSize; ++i)
			mappingTable[i] = -1;

		this->edgeMatrix = new edge * *[1];
		this->edgeMatrix[0] = new edge * [1];
		this->edgeMatrix[0][0] = NULL;
	}

	bool isfindVertex(int n) {
		bool flag = false;
		Vertex* temp = VertexList->head;

		while (temp != NULL) {
			if (temp->data == n) {
				flag = true;
				break;
			}

			temp = temp->next;
		}

		return flag;
	}

	Vertex* findVertex(int n) {
		Vertex* temp = VertexList->head;

		while (temp != NULL) {
			if (temp->data == n) {
				break;
			}

			temp = temp->next;
		}

		return temp;
	}

	void insert_vertex(int n, string data) {
		if (isfindVertex(n) == true) {
			return;
		}

		else {
			edge*** tempMatrix = new edge * *[vertexSize + 1];
			for (int i = 0; i < vertexSize + 1; ++i) {
				tempMatrix[i] = new edge * [vertexSize + 1];
				for (int j = 0; j < vertexSize + 1; ++j) {
					tempMatrix[i][j] = NULL;
				}
			}

			for (int i = 0; i < vertexSize; ++i) {
				for (int j = 0; j < vertexSize; ++j) {
					tempMatrix[i][j] = this->edgeMatrix[i][j];
				}
			}

			this->edgeMatrix = tempMatrix;

			Vertex* newVertex = new Vertex(n, data);
			VertexList->insert(newVertex);
			++this->vertexSize;
			mappingTable[vertexSize - 1] = n;
		}
	}

	void erase_vertex(int n) {
		if (isfindVertex(n) == false || vertexSize == 0) {
			return;
		}
		else {
			edge*** tempMatrix = new edge * *[vertexSize - 1];
			for (int i = 0; i < vertexSize - 1; ++i) {
				tempMatrix[i] = new edge * [vertexSize - 1];
				for (int j = 0; j < vertexSize - 1; ++j) {
					tempMatrix[i][j] = NULL;
				}
			}

			int middleIdx = 0;
			for (int i = 0; i < vertexSize; ++i) {
				if (mappingTable[i] == n)
					middleIdx = i;
			}

			for (int i = middleIdx; i < vertexSize; ++i) {
				mappingTable[i] = mappingTable[i + 1];
			}

			for (int i = 0; i < vertexSize; ++i) {
				if (this->edgeMatrix[middleIdx][i] != NULL) {
					EdgeList->remove(this->edgeMatrix[middleIdx][i]);
				}
			}

			for (int i = 0; i < vertexSize; ++i) {
				for (int j = 0; j < vertexSize; ++j) {
					if (i < middleIdx && j < middleIdx) {
						tempMatrix[i][j] = this->edgeMatrix[i][j];
					}
					else if (i > middleIdx && j > middleIdx) {
						tempMatrix[i - 1][j - 1] = this->edgeMatrix[i][j];
					}
					else if (j > middleIdx) {
						tempMatrix[i][j - 1] = this->edgeMatrix[i][j];
					}
					else if (i > middleIdx) {
						tempMatrix[i - 1][j] = this->edgeMatrix[i][j];
					}
				}
			}

			this->edgeMatrix = tempMatrix;
			VertexList->remove(findVertex(n));
			--this->vertexSize;
		}
	}

	void insert_edge(int indirectSource, int IndirectDestination, string data) {
		if (isfindVertex(indirectSource) == false || isfindVertex(IndirectDestination) == false) {
			cout << -1 << '\n';
			return;
		}

		int destination = -1;
		int source = -1;
		for (int i = 0; i <= vertexSize; ++i) {
			if (mappingTable[i] == IndirectDestination)
				destination = i;
			if (mappingTable[i] == indirectSource)
				source = i;
			if (source != -1 && destination != -1)
				break;
		}

		if (edgeMatrix[source][destination] != NULL || edgeMatrix[destination][source] != NULL) {
			cout << -1 << '\n';
			return;
		}

		edge* newEdge = new edge(findVertex(indirectSource), findVertex(IndirectDestination), data);
		edgeMatrix[source][destination] = newEdge;
		edgeMatrix[destination][source] = newEdge;

		findVertex(indirectSource)->increase_degree();
		findVertex(IndirectDestination)->increase_degree();

		EdgeList->insert(newEdge);
	}

	void erase_edge(int indirectSource, int IndirectDestination) {
		int destination = -1;
		int source = -1;

		for (int i = 0; i <= vertexSize; ++i) {
			if (mappingTable[i] == IndirectDestination)
				destination = i;
			if (mappingTable[i] == indirectSource)
				source = i;
			if (source != -1 && destination != -1)
				break;
		}

		if (edgeMatrix[source][destination] == NULL || edgeMatrix[destination][source] == NULL) {
			return;
		}
		findVertex(indirectSource)->decrease_degree();
		findVertex(IndirectDestination)->decrease_degree();

		edge* delEdge = edgeMatrix[source][destination];
		EdgeList->remove(delEdge);

		edgeMatrix[source][destination] = NULL;
		edgeMatrix[destination][source] = NULL;
	}

	void DFS(int v) {
		Vertex* finding = findVertex(v);
		cout << finding->strData;
		finding->state = 1;
		int mapNum;

		for (int i = 0; i < VertexList->listSize; ++i) {
			if (mappingTable[i] == finding->data) {
				mapNum = i;
				break;
			}
		}

		vector<int> remain;
		for (int i = 0; i < VertexList->listSize; ++i) {
			if (edgeMatrix[mapNum][i] != NULL) {
				remain.push_back(mappingTable[i]);
			}
		}

		while (!remain.empty()) {
			int minNum = 500, idx;

			for (int i = 0; i < remain.size(); ++i) {
				if (minNum > remain.at(i)) {
					minNum = remain.at(i);
					idx = i;
				}
			}

			remain.erase(remain.begin() + idx);

			if (findVertex(minNum)->state == 0) {
				DFS(minNum);
			}
		}
	}
};

int main() {
	int N, M, K; cin >> N >> M >> K;
	graph graph0;

	for (int i = 0; i < N; ++i) {
		int I; cin >> I;
		string C; cin >> C;
		graph0.insert_vertex(I, C);
	}

	for (int i = 0; i < M; ++i) {
		int S, D; cin >> S >> D;
		graph0.insert_edge(S, D, "");
	}

	graph0.DFS(K);

	return 0;
}