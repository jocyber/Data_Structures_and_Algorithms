#include <iostream>
#include <stdlib.h>
#include <bitset>
#include <string.h>

//algorithm for LFSR
std::string bits(int val, int numBits);

int main(int argc, char *argv[])
{
	unsigned int state = 0b10110;
	std::cout << bits(state, 5) << '\n';

	for(int i = 1; i < 16; i++) {
		state >>= 1;

		//bit masking
		unsigned int lastbit = state & 1;
		unsigned int secondlastbit = (state >> 1) & 1;

		unsigned int result = lastbit ^ secondlastbit;
		result <<= 4;

		state |= result;
		std::cout << bits(state, 5) << '\n';
	}

	return EXIT_SUCCESS;
}

//prints the bits
std::string bits(int val, int numBits) {
	std::string bits = "";

	for(int i = 0; i < numBits; i++) {
		bool lastbit = (val & 1);
		bits = std::to_string(lastbit) + bits;

		val >>= 1;
	}

	return bits;
}
