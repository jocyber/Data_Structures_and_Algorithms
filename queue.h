#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template <class T>
class queue {
	
	struct Node {
		T data;
		Node *next;

		Node(T data) {this->data = data;}
	}; 

	Node *front = nullptr, *rear = nullptr;
	int size = 0;

public:
	queue() {}

	void enqueue(const T &data) {
		if(!front) {
			front = new Node(data);
			rear = front;
			size++;
			return;
		}

		Node *newnode = new Node(data);
		if(!isFull(newnode)) {
			rear->next = newnode;
			rear = newnode;
			size++;
			return;
		}

		throw std::bad_alloc();
	}

	int getSize() {
		return size;
	}

	T dequeue() {
		T value;

		if(!isEmpty()) {
			if(front == rear) {
				value = front->data;
				delete front;
				size--;
				front = rear = nullptr;
			}
			else {
				Node *current = front;
				front = front->next;
				value = current->data;

				size--;
				delete current;
				current = nullptr;
			}
		}

		return value;
	}

	T getFront() {
		T value;

		if(front)
			value = front->data;

		return value;
	}
	
	bool isEmpty() {return size == 0;}

private:
	bool isFull(Node *current) {
		return !current ? true : false;
	}

};

#endif
