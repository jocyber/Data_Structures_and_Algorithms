#include <stdexcept>

template <class T>
void MaxHeap<T>::insert(const T &data) {
	buffer.push_back(data);
	int i = buffer.size() - 1;

	while(i > 0 && buffer[i] > buffer[(i - 1) / 2]) {
		swap(buffer[i], buffer[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

template <class T>
T MaxHeap<T>::remove() {
	if(buffer.size() == 0)
		throw std::underflow_error("Heap is empty");

	int element = buffer[0];
	swap(buffer[0], buffer[buffer.size() - 1]);
	buffer.pop_back();

	int i = 0;

	while(hasLeft(i) && !validParent(i)) {
		if(hasRight(i) && getRight(i) > getLeft(i)) {
			swap(buffer[i], buffer[2*i + 2]);
			i = 2*i + 2;
		}
		else {
			swap(buffer[i], buffer[2*i + 1]);
			i = 2*i + 1;
		}
	}

	return element;
}

template <class T>
bool MaxHeap<T>::validParent(int i) {
	if(hasLeft(i) && hasRight(i) && (buffer[i] > getLeft(i) && buffer[i] > getRight(i)))
		return true;
	else if(hasLeft(i) && !hasRight(i) && buffer[i] > getLeft(i))
		return true;
	else if(!hasLeft(i) && !hasRight(i))
		return true;

	return false;
}

template <class T>
bool MaxHeap<T>::hasLeft(int i) const {
	return 2*i + 1 < buffer.size();
}

template <class T>
bool MaxHeap<T>::hasRight(int i) const {
	return 2*i + 2 < buffer.size();
}

template <class T>
T MaxHeap<T>::getLeft(int i) const {
	if(hasLeft(i)) return buffer[2*i + 1];

	throw std::invalid_argument("No left child.");
}

template <class T>
T MaxHeap<T>::getRight(int i) const {
	if(hasRight(i)) return buffer[2*i + 2];

	throw std::invalid_argument("No right child.");
}

template <class T>
void MaxHeap<T>::swap(T &data1, T &data2) {
	T temp = data1;
	data1 = data2;
	data2 = temp;
}

template <class T>
void MaxHeap<T>::heapify(std::vector<T> &list) {
	int j = list.size() - 1;
	int i;

	while(j >= 0) {
		if(hasLeft(j)) {
			i = j;
			while(!validParent(i)) {
				if(hasRight(i) && getRight(i) > getLeft(i)) {
					swap(list[i], list[2*i + 2]);
					i = 2*i + 2;
				}
				else {
					swap(list[i], list[2*i + 1]);
					i = 2*i + 1;
				}
			}
		}
		j--;
	}
}

