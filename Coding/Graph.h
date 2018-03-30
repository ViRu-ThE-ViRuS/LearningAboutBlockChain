#pragma once

#include <iostream>
#include <stack>
#include <vector>
#include <utility>

using namespace std;

//data structure to represent a Graph
class Graph {
private:
	const int numberOfNodes; //number of nodes in the Graph
	vector<vector<pair<int, int>>> adjacencyList; //adjacency list representation of the Graph

	//for sorting based on shortest distance connection from current node
	struct Custom_Compare;

	//utility function for depth first search
	void __DFS(const int, vector<bool>&) const;

	//utility function for topological sort
	void __TopologicalSort(const int, vector<bool>&, stack<int>&) const;

public:
	//construct the Graph
	Graph(const int);

	//add a weighted edge to an undirected Graph
	void addEdge(const int, const int, const int);

	//print the Graph
	void printGraph() const;

	//breadth first search
	void BFS() const;

	//depth first search
	void DFS() const;

	//topologcial sort
	void TopologicalSort() const;

	//bellman ford algorithm for single source shortest paths
	void BellmanFord() const;

	//dijkstra algorithm for single source shortest paths
	void Dijkstra() const;
};

const ostream& operator<< (const ostream&, const Graph&);
