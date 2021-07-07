#ifndef STACK_H
#define STACK_H

#include <stdexcept>

template <class T>
class stack {
	int size = 0;

	struct Node {
		T data;
		Node *next;		

		Node(T data) {this->data = data;}
	};

	Node *head = nullptr;

public:
	stack() {}

	void push(const T &data) {
		if(!head) {
			head = new Node(data);
			size++;
			return;
		}

		Node *newnode = new Node(data);

		if(!isFull(newnode)) {
			newnode->next = head;
			head = newnode;
			size++;
			return;
		}

		throw std::bad_alloc();
	}

	T pop() {
		T value;

		if(!isEmpty()) {
			Node *temp = head;
			head = head->next;
			size--;

			value = temp->data;
			delete temp;
			temp = nullptr;
		}

		return value;
	}

	int stack_size() {return size;}

	T peek() {
		T head_value;

		if(head) 
			head_value = head->data;

		return head_value;
	}

private:
	bool isEmpty() {return size == 0;}

	bool isFull(Node *current) {
		return (!current) ? true : false;
	}			  
};

#endif
