#pragma once
#include <vector>

using namespace std;

struct Edge {
    int to;
    int weight;
};

class Graph {
public:
    int N;
    // adj: Danh sách cạnh đi ra (u -> v)
    vector<vector<Edge>> adj;
    // rev_adj: Danh sách cạnh đi vào (v -> u) - Dùng để loang ngược
    vector<vector<Edge>> rev_adj;

    Graph(int n) : N(n), adj(n), rev_adj(n) {}

    // Thêm tham số `directed`: true = có hướng, false = vô hướng
    void addEdge(int u, int v, int w = 1, bool directed = false) {
        // Cạnh u -> v
        adj[u].push_back({v, w});
        rev_adj[v].push_back({u, w});

        if (!directed) {
            // Nếu vô hướng, thêm cả v -> u
            adj[v].push_back({u, w});
            rev_adj[u].push_back({v, w});
        }
    }

    int getDegree(int u) const {
        return adj[u].size(); // Bậc ra (Out-degree)
    }
};