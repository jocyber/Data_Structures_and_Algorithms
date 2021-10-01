#ifndef UGRAPH_H
#define UGRAPH_H

#include "queue.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class uGraph {

    std::unordered_map<int, std::vector<int>> adj_list;

public:
    uGraph(){}

    void addEdge(const int vertex, const int vertex2) {
        if(adj_list.find(vertex) != adj_list.end() && adj_list.find(vertex2) != adj_list.end()) {
            if(std::find(adj_list[vertex].begin(), adj_list[vertex].end(), vertex2) == adj_list[vertex].end())
                adj_list[vertex].push_back(vertex2);
            
            if(std::find(adj_list[vertex2].begin(), adj_list[vertex2].end(), vertex) == adj_list[vertex2].end())
                adj_list[vertex2].push_back(vertex);
        }
    }

    void addVertex(const int node) {
        if(adj_list.find(node) == adj_list.end())
            adj_list[node] = std::vector<int>{};
    }

    void printList() {
        for(const auto &x : adj_list) {
            std::cout << x.first << ": ";
            for(int j = 0; j < x.second.size(); j++) {
                std::cout << x.second[j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void BFS(int start) {
        if(adj_list.find(start) != adj_list.end()) {
            queue<int> q;
            int u;

            std::unordered_map<int, int> visited;

            for(const auto &x : adj_list)
                visited[x.first] = x.first;

            q.enqueue(start);
            std::cout << start << " ";
            visited[start] = -1;

            while(!q.isEmpty()) {
                u = q.dequeue();

                for(int i = 0; i < adj_list[u].size(); i++) {
                    if(visited[adj_list[u][i]] != -1) {
                        std::cout << adj_list[u][i] << " ";
                        q.enqueue(adj_list[u][i]);
                        visited[adj_list[u][i]] = -1;
                    }
                }
            }

            std::cout << std::endl;
        }
    }

    //reachability problem
    bool validPath(int start, int end) {
        std::unordered_set<int> visited;
        return validPath(start, end, visited);
    }

    //use dfs to determine if the end vertex is reachable
    bool validPath(int start, int end, std::unordered_set<int> &visited) {
        if(start == end)
            return true;

        visited.insert(start);

        for(const int &x : adj_list[start]) {
            if(visited.find(x) == visited.end()) {
                if(validPath(x, end, visited))
                    return true;
            } 
        }

        return false;
    }
};

#endif
