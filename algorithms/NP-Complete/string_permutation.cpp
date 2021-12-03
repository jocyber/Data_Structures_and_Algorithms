#include <iostream>
#include <string.h>

template <class T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

void string_permute(std::string str, int n) {
	if(n == str.length()) {
		return;
	}

	for(int i = 0; i < n; i++) {
			swap(str[i], str[n]);
			std::cout << str << '\n';
			string_permute(str, n + 1);
	}
}

int main()
{
	std::string s = "ABC";
	string_permute(s, 0);
}
