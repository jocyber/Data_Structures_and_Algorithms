#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <utility>

#define null 0
using std::pair;

class Graph {

    std::unordered_map<int, std::vector<std::pair<int,int>>> adj_list;

public:
    Graph(){}

    void addEdge(const int vertex, const int vertex2, const int weight) {
        if(adj_list.find(vertex) != adj_list.end() && adj_list.find(vertex2) != adj_list.end()) {
            for(const auto &x: adj_list[vertex]) {
                if(x.first == vertex2) {
					std::cout << "Vertex " << vertex << " is already connected to " << vertex2 << std::endl;
                    return;
				}				
            }
            adj_list[vertex].push_back(std::make_pair(vertex2, weight));
        }
    }

    void addVertex(const int node) {
       if(adj_list.find(node) == adj_list.end())
            adj_list[node] = std::vector<std::pair<int, int>> {};
    }

	void printList() {
		for(const auto &x: adj_list) {
			std::cout << x.first << " -> ";

			for(const auto &y : adj_list[x.first]) {
				std::cout << "(" << y.first << ", " << y.second << ") ";
			}

			std::cout << '\n';
		}
	}

	void dijkstra_algo(int start) {
		std::unordered_map<int, int> dist;
		std::unordered_map<int, int> prev;
		std::priority_queue<pair<int,int>, std::vector<pair<int,int>>, std::greater<pair<int,int>>> q;
		std::unordered_set<int> removed;

		q.push(std::make_pair(0, start));
		setAlltoInf(dist);

		dist[start] = 0;
		prev[start] = null;
		
		while(!q.empty()) {
			pair<int,int> curr_node = q.top();
			q.pop();
			removed.insert(curr_node.second);

			for(const auto &x : adj_list[curr_node.second]) {	
				//relax all edges connected to the current node

				if(removed.find(x.first) == removed.end()) {
					int relax = dist[curr_node.second] + x.second;

					if(dist[x.first] > relax) {
						dist[x.first] = relax;
						prev[x.first] = curr_node.second;
						q.push(std::make_pair(dist[x.first], x.first));
					}
				}
			}
		}

		printDistances(dist, prev);
	}

private:
	void printDistances(std::unordered_map<int, int> &dist, std::unordered_map<int, int> &prev) {
		for(const auto &x: dist) {
			int vertex = x.first;
			std::cout << prev[vertex] << "->" << vertex << ": " << x.second << '\n';
		}
	}

	void setAlltoInf(std::unordered_map<int, int> &dist) {
		for(const auto &x : adj_list) {
			dist[x.first] = INT_MAX;
		}
	}

};

int main()
{
	Graph g;
	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addVertex(4);

	g.addEdge(1,2,3);
	g.addEdge(1,4,5);
	g.addEdge(4,3,2);
	g.addEdge(3,2,-10);
	g.addEdge(2,1,-7);


	g.dijkstra_algo(1);

	return 0;
}
