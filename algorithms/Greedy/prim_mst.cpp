#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>

#define null 0
using pair = std::pair<int,int>;

class Graph {

    std::unordered_map<int, std::vector<pair>> adj_list;

public:
    Graph(){}

	//import list of vertices
	Graph(const std::vector<int> &vertices) {
		for(int i = 0; i < vertices.size(); ++i)
			addVertex(vertices[i]);
	}

    void addEdge(const int &vertex, const int &vertex2, const int &weight) {
		if(adj_list.find(vertex) != adj_list.end() && adj_list.find(vertex2) != adj_list.end()) {
			for(const auto &x : adj_list[vertex]) {
				if(x.first == vertex2)
					return;
			}

			adj_list[vertex].push_back(std::make_pair(vertex2, weight));

			for(const auto &x : adj_list[vertex2]) {
				if(x.first == vertex)
					return;
			}

			adj_list[vertex2].push_back(std::make_pair(vertex, weight));
        }
    }

    void addVertex(const int node) {
        if(adj_list.find(node) == adj_list.end())
            adj_list[node] = std::vector<pair>{};
    }
	  
	//prim's minimum spanning tree algorithm
	Graph getMST(const int &start) {
		Graph mst;
		std::priority_queue<pair, std::vector<pair>, std::greater<pair>> queue;

		std::unordered_set<int> S; //partition inside the cut
		int curr_node = start;
		queue.push(std::make_pair(0, start));

		for(const auto &x : adj_list) // add all vertices
			mst.addVertex(x.first);

		while(!queue.empty()) {
			//make another cut (i.e update the partitions)
			curr_node = queue.top().second;
			queue.pop();
			S.insert(curr_node); //add to visited partition
			
			for(const pair &y : adj_list[curr_node]) {
				if(S.find(y.first) == S.end()) // not in S
					queue.push(std::make_pair(y.second, y.first));
			}

			if(!queue.empty()) {
				int lightEdge = queue.top().first; // minimum weight edge crossing cut

				if(S.find(queue.top().second) == S.end()) { // lightedge goes from S to V - {S} {
					mst.addEdge(curr_node, queue.top().second, lightEdge);
				}
			}
		}
	
		return mst;
	}

	void printList() {
		for(const auto &x : adj_list) {
			std::cout << x.first << " -> ";
			for(const auto &y : adj_list[x.first]) {
				std::cout << '(' << y.first << ',' << y.second << ") ";
			}
			std::cout << '\n';
		}
	}
};

int main()
{
		std::vector<int> v = {1,2,3,4,5,6,7};
		Graph g(v);

		g.addEdge(1, 6, 10);
		g.addEdge(1, 2, 28);
		g.addEdge(6, 5, 25);
		g.addEdge(5, 4, 22);
		g.addEdge(5, 7, 24);
		g.addEdge(7, 2, 14);
		g.addEdge(2, 3, 16);
		g.addEdge(7, 4, 18);
		g.addEdge(3, 4, 12);

		Graph mst = g.getMST(1);
		mst.printList();

		return 0;
}
