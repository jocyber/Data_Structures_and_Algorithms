#include <iostream>
#include <vector>

using std::cout;
using uint = unsigned int;

//conjunctive normal form boolean formula
bool checkCNF(std::string &str) {
	uint x1 = (uint)str[0];
	uint x2 = (uint)str[1];
	uint x3 = (uint)str[2];

	return (x1 || !x2) && (!x1 || x3 || x2) && (!x3 || x2);
}

//Satisfiability problem, the first NP-complete problem.
bool SAT_Solver(int n, std::string str) {
		if(n == 0) {
			return checkCNF(str);
		}
		else {
			return SAT_Solver(n - 1, str + '0') ||
							SAT_Solver(n - 1, str + '1');
		}
}

int main()
{
	if(SAT_Solver(3, ""))
		cout << "Boolean formula is satisfiable.\n";
	else
		cout << "Boolean formula is not satisfiable.\n";
	return 0;
}
