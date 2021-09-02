#ifndef BST_H
#define BST_H

#include <iostream>
#include "../includes/queue.h"
#include <math.h>

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
	void insert(T item) {
		root = insert(item, root);
	}

private:
	Node<T>* insert(T &item, Node<T> *root) {
		if(!root)
			return new Node<T>(item);

		if(item < root->data)
			root->left = insert(item, root->left);
		else if(item > root->data)
			root->right = insert(item, root->right);

		root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
		return rotateTree(root);
	}


	int getHeight(Node<T> *root) const {
		return (root == nullptr) ? -1 : root->height;
	}


	int balanceFactor(Node<T> *root) const {
		return getHeight(root->left) - getHeight(root->right);
	}


	Node<T>* LL(Node<T> *root) { // rotate tree to the right
		Node<T> *temp = root->left;

		root->left = temp->right;
		temp->right = root;

		root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
		temp->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;

		return temp;
	}


	Node<T>* RR(Node<T> *root) {//rotate tree to to left
		Node<T> *temp = root->right;

		root->right = temp->left;
		temp->left = root;

		root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
		temp->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;

		return temp;
	}


	Node<T>* rotateTree(Node<T> *root) {//perform any of the four rotations
		if(balanceFactor(root) > 1) {
			if(balanceFactor(root->left) <= -1)
				root->left = RR(root->left);
			return LL(root);
		}
		else if(balanceFactor(root) < -1) {
			if(balanceFactor(root->right) >= 1)
				root->right = LL(root->right);
			return RR(root);
		}
		return root;
	}

	//return length
	int getLength() const {return length;}

public:
	void levelOrder() const {levelOrder(root);}

private:
	void levelOrder(Node<T> *root) const {
		Node<T> *curr = root;
		int size;
		queue<Node<T>*> q;
		q.enqueue(curr);

		while(!q.isEmpty()) {
			size = q.getSize();

			for(int i = 0; i < size; i++) {
				std::cout << q.getFront() << std::endl;
				curr = q.getFront();
				q.dequeue();

				if(curr->left)
					q.enqueue(curr->left);
				if(curr->right)
					q.enqueue(curr->right);
			}
		}
	}

public:
	//call private version since it uses recursion
	void inOrder() const {inOrder(root);}

private:
	//print tree in order
	void inOrder(Node<T> *root) const {
		if(root) {
			inOrder(root->left);
			std::cout << root->data << " ";
			inOrder(root->right);
		}
	}


public:
	void preOrder() const {preOrder(root);}

private:
	void preOrder(Node<T> *root) const {
		if(root) {
			std::cout << root->data << " ";
			preOrder(root->left);
			preOrder(root->right);
		}
	}

public:
	void postOrder() const {postOrder(root);}

private:
	void postOrder(Node<T> *root) const {
		if(root) {
			postOrder(root->left);
			postOrder(root->right);
			std::cout << root->data << " ";
		}
	}

public:
	int getNumLeafNodes() {return getNumLeafNodes(root);}

private:
	//count leaf nodes
	int getNumLeafNodes(Node<T> *root) {
		if(root) {
			if(!root->left && !root->right)//if children are null
				return getNumLeafNodes(root->left) + getNumLeafNodes(root->right) + 1;
			else
				return getNumLeafNodes(root->left) + getNumLeafNodes(root->right);
		}

		return 0;
	}

public:
	//destructor
	~AVL() {deleteAllNodes(root);}

private:
	//delete all nodes using postorder
	void deleteAllNodes(Node<T> *root) {
		if(root) {
			deleteAllNodes(root->left);
			deleteAllNodes(root->right);
			delete root;
		}	 

		length = 0;	
	}

public:
	void deleteItem(T item) {root = deleteItem(root, item);}

private:
	// delete a node in the tree
	Node<T>* deleteItem(Node<T>* root, T &item) {
		if(!root)
			return root;

		if(item < root->data)//find item
			root->left = deleteItem(root->left, item);
		else if(item > root->data)//find item
			root->right = deleteItem(root->right, item);
		else if(item == root->data) {//if node found
			if(root->left && root->right) {//if both children exist
				Node<T>* temp = findMax(root->left);//return inorder predecessor
				root->data = temp->data;//root equals the predecessor
				root->left = deleteItem(root->left, root->data);//recursively delete predecessor
			} 
			else {//if item has one or less children
				Node<T> *temp = root;

				if(!root->left)
					temp = root->right;
				else if(!root->right)
					temp = root->left;

				delete root;
				length--;

				return temp;
			}
		}	

		root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
		return rotateTree(root);
	}

	//find max element in tree
	Node<T>* findMax(Node<T> *root) {
		if(!root)
			return root;

		Node<T> *curr = root;

		if(!curr)
			throw std::bad_alloc();

		while(curr->right) //go all the way to the right
			curr = curr->right;

		return curr;
	}

public:
	int getSumOfLeaves() {
		return getSumOfLeaves(root);
	}

private:
	int getSumOfLeaves(Node<T> *root) {
		if(!root)
			return 0;

		if(!root->left && !root->right)
			return root->data;

		return getSumOfLeaves(root->left) + getSumOfLeaves(root->right);
	}
};

#endif
