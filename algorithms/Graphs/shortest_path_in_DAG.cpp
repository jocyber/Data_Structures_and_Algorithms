#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Digraph {

    std::unordered_map<int, std::vector<int>> adj_list;
	 int numNodes = 0;

public:
    Digraph(){}

    void addEdge(const int vertex, const int vertex2) {
        if(adj_list.find(vertex) != adj_list.end() && adj_list.find(vertex2) != adj_list.end()) {
            for(const int &x : adj_list[vertex]) {
					if(x == vertex2)
						return;
				}

            adj_list[vertex].push_back(vertex2);
        }
    }

    void addVertex(const int node) {
        if(adj_list.find(node) == adj_list.end()) {
            adj_list[node] = std::vector<int>{};
				numNodes++;
		  }
    }

	 std::vector<int> topological_sort() {
		std::unordered_set<int> visited;
		std::vector<int> ordering(numNodes);

		int index = numNodes - 1;

		for(const auto &x: adj_list) {
			if(visited.find(x.first) == visited.end())
				topological_sort(x.first, visited, ordering, index);
		}

		return ordering;
	 }

private:
	 void topological_sort(int node, std::unordered_set<int> &visited, std::vector<int> &list, int &index) {
			visited.insert(node);

			for(const int &x: adj_list[node]) {
					if(visited.find(x) == visited.end()) {
						topological_sort(x, visited, list, index);
					}

			}

			list[index] = node;
			index--;
	 }
};

int main()
{
	Digraph g;

	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addVertex(4);
	g.addVertex(5);

	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,4);
	g.addEdge(5,3);
	g.addEdge(5,4);

	std::vector<int> list = g.topological_sort();

	for(const int &x: list) {
		std::cout << x << " ";
	}

	std::cout << std::endl;

	return 0;
}
