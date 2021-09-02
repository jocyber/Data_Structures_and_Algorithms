#ifndef UGRAPH_H
#define UGRAPH_H

#include "queue.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdexcept>

class uGraph {

    std::unordered_map<int, std::vector<int>> adj_list;

public:
    uGraph(){}

    void addEdge(const int vertex, const int vertex2) {
        if(adj_list.find(vertex) != adj_list.end() && adj_list.find(vertex2) != adj_list.end()) {
            for(int i = 0; i < adj_list[vertex].size(); i++) {
                if(adj_list[vertex][i] == vertex2)
                    return;
            }
            adj_list[vertex].push_back(vertex2);

            for(int i = 0; i < adj_list[vertex2].size(); i++) {
                if(adj_list[vertex2][i] == vertex)
                    return;
            }
            adj_list[vertex2].push_back(vertex);

            return;
        }

        throw std::invalid_argument("Vertex set is empty.");
    }

    void addVertex(const int node) {
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
};

#endif
