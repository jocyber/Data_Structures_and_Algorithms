#include <iostream>
#include <string.h>

//combinatorial algorithm to generate all n bit binary numbers
//O(2^n)
void binary_list(int n, std::string str) {
	if(n == 0) {
		std::cout << str << '\n';
		return;
	}

	binary_list(n - 1, str + '0');
	binary_list(n - 1, str + '1');
}

int main()
{
	binary_list(4, "");
}


