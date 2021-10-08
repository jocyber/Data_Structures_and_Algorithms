#include <iostream>
#include <vector>

//T(n) = T(n / 2) + O(1) => O(logn)
int binarySearch(const std::vector<int> &list, int low, int high, int key)
{
	int mid = low + (high - low) / 2;

	if(list[mid] == key)
		return mid;

	if(list[mid] > key)
		return binarySearch(list, low, mid - 1, key);
	else
		return binarySearch(list, mid + 1, high, key);
}	

int main()
{
	std::vector<int> list = {1,3,4,5,6,8,9,10,14};

	std::cout << binarySearch(list, 0, list.size() - 1, 8) << std::endl;
	return 0;
}
