#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Digraph {

    std::unordered_map<int, std::vector<int>> adj_list;

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
        if(adj_list.find(node) == adj_list.end())
            adj_list[node] = std::vector<int>{};
    }

	 bool hasCycle() {
		  std::unordered_set<int> visited;
		  std::unordered_set<int> dfs_branch;

		  for(const auto &x : adj_list) {
				if(hasCycle(x.first, visited, dfs_branch))
					return true;
		  }

		  return false;
	 }

private:
	 bool hasCycle(const int &node, std::unordered_set<int> &visited, std::unordered_set<int> &branch) {
		  visited.insert(node);
		  branch.insert(node);

		  for(const int &x : adj_list[node]) {
				if(visited.find(x) == visited.end()) {
					if(hasCycle(x, visited, branch))
						return true;
				} // check if the vertex we're visited is a back edge
				else if(branch.find(x) != branch.end())
					return true;
		  }	

		  branch.erase(node);
		  return false;
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
	g.addEdge(2,4);
	g.addEdge(4,1);
	g.addEdge(4,3);

	if(g.hasCycle())
		std::cout << "There be a cycle, bro." << std::endl;
	else
		std::cout << "No cycle, bro." << std::endl;

	return 0;
}
