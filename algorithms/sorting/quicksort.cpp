#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using std::vector;
using std::cout;
using std::endl;

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int partition(vector<int> &list, int p, int r) {
	int e = list[r];
	int i = p - 1;

	for(int j = p; j < r; j++) {
		if(list[j] <= e) {
			i++;
			swap(list[i], list[j]);
		}
	}

	i++;
	swap(list[i], list[r]);
	return i;
}

void quicksort(vector<int> &list, int low, int high) {
	int p;
	
	if(low < high) {
		p = partition(list, low, high);
		quicksort(list, low, p - 1);
		quicksort(list, p + 1, high);
	}
}

int main()
{
	srand(time(0));
	vector<int> list(50);

	int random;

	for(int i = 0; i < 50; i++) {
		random = rand() % 100 + 1;
		list[i] = random;
	}	  

	quicksort(list, 0, list.size() - 1);

	for(const auto &x : list) {
		cout << x << ' ';
	}

	cout << endl;

	return 0;
}
