#pragma once
#include <vector>

//data structure to represent a Binary Indexed Tree / Fenwick Tree
class FenwickTree {
private:
	int size;
	std::vector<int> table;

public:
	//construct the fenwick tree
	FenwickTree(const int);

	//update an index in the fenwick tree
	void update(int, const int);

	//get the prefix sum till the current index
	int sum(int) const;

	//get the sum of all the nodes in the range
	int rangeSum(int, int) const;
};