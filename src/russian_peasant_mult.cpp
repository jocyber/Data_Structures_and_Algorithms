#include <iostream>

int mult(int x, int y) {
	if(x == 1)
		return y;
	if(x == 0)
		return 0;

	if(x % 2 == 0)
		return mult(x / 2, 2 * y);
	else
		return mult(x / 2, 2 * y) + y;

}

int main() {
	int x = mult(13, 13);
	std::cout << x << std::endl;

	return 0;		  
}
