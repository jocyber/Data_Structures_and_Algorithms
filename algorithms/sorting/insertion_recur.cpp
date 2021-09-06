#include <iostream>
#include <vector>

void insert(std::vector<int> &list, int end) 
{
	int element = list[end], i = end - 1;

	while(i >= 0 && element < list[i]) {
		list[i + 1] = list[i];
		i--;
	}

	list[i + 1] = element;
}

void insertionSort(std::vector<int> &list, int endPos)
{
	if(endPos == 0) // some c
		return;

	insertionSort(list, endPos - 1); // T(n - 1)
	insert(list, endPos); // O(n)
}

//recurrence formulation: T(n) = T(n - 1) + n + c
//by master's method, this recurrence relation runs in O(n^2)


int main() 
{
	std::vector<int> list = {3,4,7,45,5,2,1};
	insertionSort(list, list.size() - 1);

	for(const auto &x : list)
		std::cout << x << " ";

	std::cout << std::endl;	

	return 0;
}
