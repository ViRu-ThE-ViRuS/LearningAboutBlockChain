#pragma once
#include "FenwickTree.h"
#include <vector>

FenwickTree::FenwickTree(const int size) : size(size) {
	table.resize(size);
}

void FenwickTree::update(int i, const int delta) {
	i += 1;
	while (i <= size) {
		table[i] += delta;
		i += i & -i;
	}
}

int FenwickTree::sum(int i) const {
	i += 1;
	int sum = 0;
	while (i > 0) {
		sum += table[i];
		i -= i & -i;
	}

	return sum;
}

int FenwickTree::rangeSum(int i, int j) const {
	return sum(j) - sum(i - 1);
}