#include <iostream>
#include <vector>

//T(n) = T(n - 1) + O(1) => O(n)
void binary(int val)
{
	if(val <= 1) {
		std::cout << val << '\n';
		return;
	}

	binary(val / 2); // T(n - 1) based on bits

	if(val % 2 == 0)
		std::cout << 0 << '\n';
	else
		std::cout << 1 << '\n';
}

int main()
{
	binary(11);
	return 0;
}
