#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <list>

using std::pair;
using std::make_pair;

using p = std::pair<int,int>;

class Digraph {

    std::unordered_map<int, std::vector<p>> adj_list; // edge, weight
	 int numNodes = 0;

public:
    Digraph(){} // default constructor

    void addEdge(const int vertex, const int vertex2, const int weight) {
        if(adj_list.find(vertex) != adj_list.end() && adj_list.find(vertex2) != adj_list.end()) {
            for(const auto &x : adj_list[vertex]) {
					if(x.first == vertex2)
						return;
				}

            adj_list[vertex].push_back(make_pair(vertex2, weight));
        }
    }

    void addVertex(const int node) {
        if(adj_list.find(node) == adj_list.end()) {
            adj_list[node] = std::vector<p>{};
			numNodes++;
		  }
    }

	//////////////////////////////////////////////
	//shortest path member function
	//////////////////////////////////////////////

	std::list<int> shortestPathDAG(const int &source, const int &dest) { //O(V + E)
		std::vector<int> top_sort = topological_sort(); // O(V + E)
		std::unordered_map<int,int> dist;
		std::unordered_map<int,int> prev;

		dist[top_sort[0]] = 0; // set initial node distance to 0

		for(int i = 0; i < top_sort.size(); ++i) {
			int node = top_sort[i];

			for(const auto &x : adj_list[node]) {
				if(dist.find(x.first) == dist.end()) {
					dist[x.first] = dist[node] + x.second;
					prev[x.first] = node;
				}
				else {
					int distance = dist[node] + x.second;

					if(dist[x.first] > distance) {
						dist[x.first] = distance;
						prev[x.first] = node;
					}
				}
			}
		}
		
		std::list<int> path;
		shortestDistance(prev, source, dest, path);
		return path;
	}
	/////////////////////////////////////////////
	//////////////////////////////////////////////

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

			for(const auto &x: adj_list[node]) {
					if(visited.find(x.first) == visited.end()) {
						topological_sort(x.first, visited, list, index);
					}
			}

			list[index] = node;
			index--;
	 }

	//find the shortest path between 2 nodes given the shortest distances in DAG
	void shortestDistance(std::unordered_map<int,int> &prev, int source, int dest, std::list<int> &list) {
		 if(source != dest)
		 	shortestDistance(prev, source, prev[dest], list);

		 list.push_back(dest);
	 }
};

int main()
{
	Digraph g;

	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addVertex(4);

	g.addEdge(1, 2, 2);
	g.addEdge(1, 3, 3);
	g.addEdge(2, 3, 2);
	g.addEdge(2, 4, 3);
	g.addEdge(1, 4, 7);

	std::list<int> path = g.shortestPathDAG(1, 3);

	for(auto i = path.begin(); i != path.end(); ++i) {
		std::cout << *i << ' ';
	}

	std::cout << std::endl;

	return 0;
}
