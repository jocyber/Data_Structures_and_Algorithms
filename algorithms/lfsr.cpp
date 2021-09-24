#include <iostream>
#include <stdlib.h>
#include <bitset>

//algorithm for LFSR register
int main(int argc, char *argv[])
{
	unsigned int state = 0b10110;

	for(int i = 1; i < 32; i++) {
		std::bitset<5> x(state);
		std::cout << x << '\n';

		state >>= 1;
		unsigned int lastbit = state & 1;
		unsigned int secondlastbit = (state >> 1) & 1;

		unsigned int result = lastbit ^ secondlastbit;
		result <<= 4;

		state |= result;
	}

	return EXIT_SUCCESS;
}
