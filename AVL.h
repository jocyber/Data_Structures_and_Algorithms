#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>

template <class T>
struct Node { // node class
	T data;
	int height = 0;
	Node *left;
	Node *right;

	Node(const T &item) {data = item; left = nullptr; right = nullptr;}
};

template <class T>
class AVL {

	int length;
	Node<T> *root = nullptr;

public:
	AVL(){}
	void insert(T item);
	void deleteItem(T item);
	void preOrder() const;
	void inOrder() const;
	void postOrder() const;
	void levelOrder() const;
	int getLength() const;
	int getNumLeafNodes();
	int getSumOfLeaves();
	int getHeight(Node<T> *root) const;

	~AVL();

private: // implementation functions for class
	//member functions for AVL tree
	Node<T>* LL(Node<T> *root);
	Node<T>* RR(Node<T> *root);
	int balanceFactor(Node<T> *root) const;
	Node<T>* rotateTree(Node<T> *root);
	Node<T>* insert(T &item, Node<T> *root);

	void preOrder(Node<T> *root) const;
	void inOrder(Node<T> *root) const;
	void postOrder(Node<T> *root) const;
	void levelOrder(Node<T> *root) const;
	Node<T>* deleteItem(Node<T> *root, T &item);
	int getNumLeafNodes(Node<T> *root);
	int getSumOfLeaves(Node<T> *root);

	void deleteAllNodes(Node<T> *root);

	Node<T>* findMax(Node<T> *root);
};

#include "implementation_files/AVL.cpp"

#endif
