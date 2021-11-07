#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>

#define null 0
using pair = std::pair<int,int>;

//edge object
struct Edge {
		int fromVertex;
		int weight;
		int toVertex;

		Edge(const int &fromVertex, const int &weight, const int &toVertex) {
			this->fromVertex = fromVertex;
			this->weight = weight;
			this->toVertex = toVertex;
		}
};

class Graph {
    std::unordered_map<int, std::vector<Edge>> adj_list;

public:
    Graph(){}

	//import list of vertices
	Graph(const std::vector<int> &vertices) {
		for(int i = 0; i < vertices.size(); ++i)
			addVertex(vertices[i]);
	}

    void addEdge(const int &vertex, const int &vertex2, const int &weight) {
		if(adj_list.find(vertex) != adj_list.end() && adj_list.find(vertex2) != adj_list.end()) {
			for(Edge &x : adj_list[vertex]) {
				if(x.fromVertex == vertex2)
					return;
			}

			adj_list[vertex].push_back(Edge(vertex2, weight, vertex));

			for(Edge &x : adj_list[vertex2]) {
				if(x.fromVertex == vertex)
					return;
			}

			adj_list[vertex2].push_back(Edge(vertex, weight, vertex2));
        }
    }

    void addVertex(const int node) {
        if(adj_list.find(node) == adj_list.end())
            adj_list[node] = std::vector<Edge>{};
    }
	  
	//prim's minimum spanning tree algorithm
	Graph getMST(const int &start) {
		Graph mst;
		std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> queue;

		std::unordered_set<int> S; //partition inside the cut
		queue.push(Edge(start, 0, -1));
		S.insert(start);

		for(const auto &x : adj_list) // add all vertices
			mst.addVertex(x.first);

		while(!queue.empty()) {
			int curr_node = queue.top().fromVertex;
			queue.pop();

			for(Edge &y : adj_list[curr_node]) {
				if(S.find(y.fromVertex) == S.end()) // not in S
					queue.push(Edge(y.fromVertex, y.weight, y.toVertex));
			}

			if(!queue.empty()) {
				int lightEdge = queue.top().weight; // minimum weight edge crossing cut
				int toVertex = queue.top().toVertex;
				int fromVertex = queue.top().fromVertex;

				if(S.find(fromVertex) == S.end()) { // lightedge goes from S to V - {S} {
					mst.addEdge(fromVertex, toVertex, lightEdge);
					S.insert(fromVertex);
				}
			}
		}
	
		return mst;
	}

	void printList() {
		for(const auto &x : adj_list) {
			std::cout << x.first << " -> ";
			for(Edge &y : adj_list[x.first]) {
				std::cout << '(' << y.fromVertex << ',' << y.weight << ") ";
			}
			std::cout << '\n';
		}
	}

	friend bool operator>(const Edge &a, const Edge &b);
};

bool operator>(const Edge &a, const Edge &b) {
  	return a.weight > b.weight;
}

int main()
{
		std::vector<int> v = {1,2,3,4,5,6,7};
		Graph g(v);

		g.addEdge(1,2,28);
		g.addEdge(1,6,10);
		g.addEdge(2,7,14);
		g.addEdge(2,3,16);
		g.addEdge(6,5,25);
		g.addEdge(7,5,24);
		g.addEdge(5,4,22);
		g.addEdge(7,4,18);
		g.addEdge(3,4,12);

		Graph mst = g.getMST(1);
		mst.printList();

		return 0;
}
