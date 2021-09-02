#include <iostream>
#include <vector>

int getMaxPos(const std::vector<int> &list, int size) {
	int maxPos = 0;

	for(int i = 1; i <= size; i++) {
		if(list[i] > list[maxPos])
			maxPos = i;
	}

	return maxPos;
}

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

//recursive implementation of selection sort algorithm
void selectionSort(std::vector<int> &list, int endPos) {
	if(endPos == 0)
		return;

	int maxPos = getMaxPos(list, endPos);
	swap(list[endPos], list[maxPos]);
	selectionSort(list, endPos - 1);
}

int main() {
	std::vector<int> test = {1,7,8,9,5,3,20};
	selectionSort(test, test.size() - 1);

	for(const auto &x : test) 
		std::cout << x << " ";

	std::cout << std::endl;
	return 0;	
}
