#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "lib/graph.hpp"
#include "lib/labeling.hpp"

using namespace std;
using namespace chrono;

void generate_degree_order(const Graph& g, vector<int>& order) {
    int n = g.N;
    order.resize(n);
    vector<pair<int, int>> temp(n);
    for (int i = 0; i < n; i++) temp[i] = {g.getDegree(i), i};
    sort(temp.begin(), temp.end(), [](pair<int,int> a, pair<int,int> b){
        return a.first > b.first; 
    });
    for(int i=0; i<n; i++) order[i] = temp[i].second;
}

int main() {
    // ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N, M, type;
    // Nhập thêm Type: 0 = Vô hướng, 1 = Có hướng
    cout << "Nhap N, M, Type (0: Vo huong, 1: Co huong): ";
    if (!(cin >> N >> M >> type)) return 0;
    bool directed = (type == 1);

    Graph g(N);
    cout << "Nhap " << M << " canh (u v w):\n";
    for (int i = 0; i < M; i++) {
        int u, v, w = 1;
        cin >> u >> v >> w;
        g.addEdge(u, v, w, directed);
    }

    vector<int> order;
    generate_degree_order(g, order);

    PrunedLabeling hl(N);
    cout << "Building...\n";
    hl.build(g, order);

    cout << "Query (u v): \n";
    int u, v;
    while (cin >> u >> v) {
        if (u < 0) break;
        int d = hl.query(u, v);
        
        // Check với Dijkstra để đảm bảo đúng
        cout << "Distance u-v: " << d << '\n';
    }
    return 0;
}