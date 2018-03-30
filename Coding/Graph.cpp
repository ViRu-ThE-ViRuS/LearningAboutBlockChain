#include "Graph.h"

#include <iostream>
#include <stack>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

struct Graph::Custom_Compare {
	const bool operator() (const pair<int, int>& a, const pair<int, int>& b) const {
		return a.second < b.second;
	}
};

void Graph::__DFS(const int current, vector<bool>& visited) const {
	visited[current] = true;
	cout << current << endl;

	for (const pair<int, int>& connection : adjacencyList[current]) {
		if (!visited[connection.first]) {
			__DFS(connection.first, visited);
		}
	}
}

void Graph::__TopologicalSort(const int current, vector<bool>& visited, stack<int>& order) const {
	visited[current] = true;

	for (const pair<int, int>& connection : adjacencyList[current]) {
		if (!visited[connection.first]) {
			__TopologicalSort(connection.first, visited, order);
		}
	}

	order.push(current);
}

Graph::Graph(const int n) : numberOfNodes(n) {
	adjacencyList.resize(n);
}

void Graph::addEdge(const int source, const int destination, const int weight) {
	adjacencyList[source].push_back(make_pair(destination, weight));
	adjacencyList[destination].push_back(make_pair(source, weight));
}

void Graph::printGraph() const {
	for (const vector<pair<int, int>>& connections : adjacencyList) {
		for (const pair<int, int>& connection : connections) {
			cout << connection.first << " " << connection.second << endl;
		}

		cout << endl;
	}
}

const ostream& operator<< (const ostream& stream, const Graph& graph) {
	graph.printGraph();
	return stream;
}

void Graph::BFS() const {
	vector<int> D(numberOfNodes, INT_MAX);
	queue<int> q;

	D[0] = 0;
	q.push(0);

	int source = 0;
	while (!q.empty()) {
		source = q.front();
		q.pop();

		for (const pair<int, int>& connection : adjacencyList[source]) {
			if (D[connection.first] == INT_MAX) {
				D[connection.first] = D[source] + 1;
				q.push(connection.first);
			}
		}
	}

	for (const int d : D) {
		cout << d << endl;
	}
}

void Graph::DFS() const {
	vector<bool> visited(numberOfNodes, false);

	for (int i = 0; i < numberOfNodes; ++i) {
		if (!visited[i]) {
			__DFS(i, visited);
		}
	}
}

void Graph::TopologicalSort() const {
	vector<bool> visited(numberOfNodes, false);
	stack<int> order;

	for (int i = 0; i < numberOfNodes; ++i) {
		if (!visited[i]) {
			__TopologicalSort(i, visited, order);
		}
	}

	while (!order.empty()) {
		cout << order.top() << endl;
		order.pop();
	}
}

void Graph::BellmanFord() const {
	vector<int> D(numberOfNodes, INT_MAX);
	D[0] = 0;

	for (int i = 0; i < numberOfNodes - 1; ++i) {
		for (int j = 0; j < numberOfNodes; ++j) {
			for (const pair<int, int>& connection : adjacencyList[j]) {
				if (D[connection.first] > D[j] + connection.second) {
					D[connection.first] = D[j] + connection.second;
				}
			}
		}
	}

	for (int i = 0; i < numberOfNodes - 1; ++i) {
		for (int j = 0; j < numberOfNodes; ++j) {
			for (const pair<int, int>& connection : adjacencyList[j]) {
				if (D[connection.first] > D[j] + connection.second) {
					cout << "Negative Weight Cycle Exists" << endl;
					return;
				}
			}
		}
	}

	for (const int d : D) {
		cout << d << endl;
	}
}

void Graph::Dijkstra() const {
	vector<int> D(numberOfNodes, INT_MAX);
	priority_queue<pair<int, int>, vector<pair<int, int>>, Custom_Compare> mPQ;

	D[0] = 0;
	mPQ.push(make_pair(0, 0));

	int source = 0;
	while (!mPQ.empty()) {
		source = mPQ.top().first;
		mPQ.pop();

		for (const pair<int, int>& connection : adjacencyList[source]) {
			if (D[connection.first] > D[source] + connection.second) {
				D[connection.first] = D[source] + connection.second;
				mPQ.push(connection);
			}
		}
	}

	for (const int d : D) {
		cout << d << endl;
	}
}

/*
#include <iostream>
#include "graph.h"

using namespace std;

int main() {
//accelerate input/output
ios_base::sync_with_stdio(false);
cin.tie(NULL);

//create the Graph
Graph graph(3);
graph.addEdge(0, 1, 10);
graph.addEdge(1, 2, 5);
graph.addEdge(2, 0, 20);

//utilize the various features of this Graph data structure
cout << "Depth First Search" << endl;
graph.DFS();
cout << endl;

cout << "Breadth First Search" << endl;
graph.BFS();
cout << endl;

cout << "Topological Sort" << endl;
graph.TopologicalSort();
cout << endl;

cout << "Bellman Ford" << endl;
graph.BellmanFord();
cout << endl;

cout << "Dijkstra" << endl;
graph.Dijkstra();
cout << endl;

cout << "Print Graph" << endl;
cout << graph;

//program ended
return 0;
}
*/