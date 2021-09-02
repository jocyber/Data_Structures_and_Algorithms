#ifndef HEAP_H
#define HEAP_H

#include <vector>

template <class T>
class MaxHeap {
	std::vector<T> buffer;

public:
	MaxHeap(){}

	MaxHeap(const std::vector<T> &list) {
		for(const auto &x : list)
			buffer.push_back(x);
			
		heapify(buffer);
	}

	void insert(const T &data);
	T remove();

private:
	bool hasLeft(int i) const;
	bool hasRight(int i) const;

	T getLeft(int i) const;
	T getRight(int i) const;

	void swap(T &data1, T &data2);

	void heapify(std::vector<T> &list);
	bool validParent(int i);
};

#include "../src/max_heap.cpp"

#endif
