#include "../AVL.h"
#include <iostream>
#include "../queue.h"
#include <math.h>

template <class T>
void AVL<T>::insert(T item) {
	root = insert(item, root);
}

template <class T>
Node<T>* AVL<T>::insert(T &item, Node<T> *root) {
	if(!root)
		return new Node<T>(item);

	if(item < root->data)
		root->left = insert(item, root->left);
	else if(item > root->data)
		root->right = insert(item, root->right);

	root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
	return rotateTree(root);
}

template <class T>
int AVL<T>::getHeight(Node<T> *root) const {
	return (root == nullptr) ? -1 : root->height;
}

template <class T>
int AVL<T>::balanceFactor(Node<T> *root) const {
	return getHeight(root->left) - getHeight(root->right);
}

template <class T>
Node<T>* AVL<T>::LL(Node<T> *root) { // rotate tree to the right
	Node<T> *temp = root->left;

	root->left = temp->right;
	temp->right = root;

	root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
	temp->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;

	return temp;
}

template <class T>
Node<T>* AVL<T>::RR(Node<T> *root) {//rotate tree to to left
	Node<T> *temp = root->right;

	root->right = temp->left;
	temp->left = root;

	root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
	temp->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;

	return temp;
}

template <class T>
Node<T>* AVL<T>::rotateTree(Node<T> *root) {//perform any of the four rotations
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

template <class T>//return length
int AVL<T>::getLength() const {return length;}

template <class T>
void AVL<T>::levelOrder() const {levelOrder(root);}

template <class T>
void AVL<T>::levelOrder(Node<T> *root) const {
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

template <class T>//call private version since it uses recursion
void AVL<T>::inOrder() const {inOrder(root);}

template <class T>//print tree in order
void AVL<T>::inOrder(Node<T> *root) const {
	if(root) {
		inOrder(root->left);
		std::cout << root->data << " ";
		inOrder(root->right);
	}
}

template <class T>
void AVL<T>::preOrder() const {preOrder(root);}

template <class T>
void AVL<T>::preOrder(Node<T> *root) const {
	if(root) {
		std::cout << root->data << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

template <class T>
void AVL<T>::postOrder() const {postOrder(root);}

template <class T>
void AVL<T>::postOrder(Node<T> *root) const {
	if(root) {
		postOrder(root->left);
		postOrder(root->right);
		std::cout << root->data << " ";
	}
}

template <class T>
int AVL<T>::getNumLeafNodes() {return getNumLeafNodes(root);}

template <class T>//count leaf nodes
int AVL<T>::getNumLeafNodes(Node<T> *root) {
	if(root) {
		if(!root->left && !root->right)//if children are null
			return getNumLeafNodes(root->left) + getNumLeafNodes(root->right) + 1;
		else
			return getNumLeafNodes(root->left) + getNumLeafNodes(root->right);
	}

	return 0;
}

template <class T>//destructor
AVL<T>::~AVL() {deleteAllNodes(root);}

template <class T>//delete all nodes using postorder
void AVL<T>::deleteAllNodes(Node<T> *root) {
	if(root) {
		deleteAllNodes(root->left);
		deleteAllNodes(root->right);
		delete root;
	}	 

	length = 0;	
}

template <class T>
void AVL<T>::deleteItem(T item) {root = deleteItem(root, item);}

template <class T>// delete a node in the tree
Node<T>* AVL<T>::deleteItem(Node<T>* root, T &item) {
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

	if(!root) return root;
	root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
	return rotateTree(root);
}

template <class T>//find max element in tree
Node<T>* AVL<T>::findMax(Node<T> *root) {
	if(!root)
		return root;

	Node<T> *curr = root;

	if(!curr)
		throw std::bad_alloc();

	while(curr->right) //go all the way to the right
		curr = curr->right;

	return curr;
}

template <class T>
int AVL<T>::getSumOfLeaves() {
	return getSumOfLeaves(root);
}

template <class T>
int AVL<T>::getSumOfLeaves(Node<T> *root) {
	if(!root)
		return 0;

	if(!root->left && !root->right)
		return root->data;

	return getSumOfLeaves(root->left) + getSumOfLeaves(root->right);
}

