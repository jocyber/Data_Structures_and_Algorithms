#include <iostream>

int mult(int x, int y) {
	if(x == 1)
		return y; // some c
	if(x == 0)
		return 0;

	if(x % 2 == 0)
		return mult(x / 2, 2 * y); // T(n - 1) + O(n)
	else
		return mult(x / 2, 2 * y) + y; // T(n - 1) + O(n)

}

//recurrence formulation: T(n) = T(n - 1) + O(n) + c => O(n^2)
//

int main() {
	int x = mult(13, 13);
	std::cout << x << std::endl;

	return 0;		  
}
