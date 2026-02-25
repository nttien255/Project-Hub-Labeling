#pragma once
#include "Graph.hpp"
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int INF = 1e9;

class PrunedLabeling {
    // Helper function để tìm Hub chung giữa L_out(u) và L_in(v)
    int intersect(const vector<int>& hubs_u, const vector<int>& dists_u,
                  const vector<int>& hubs_v, const vector<int>& dists_v) {
        int r = INF;
        size_t i = 0, j = 0;
        while (i < hubs_u.size() && j < hubs_v.size()) {
            if (hubs_u[i] == hubs_v[j]) {
                if (hubs_u[i] == -1) break; // Sentinel
                if (dists_u[i] != INF && dists_v[j] != INF)
                    r = min(r, dists_u[i] + dists_v[j]);
                i++; j++;
            } else if (hubs_u[i] < hubs_v[j]) i++;
            else j++;
        }
        return r;
    }

    // Hàm loang Pruned BFS tổng quát (dùng cho cả xuôi và ngược)
    void pruned_dijkstra(int hub, int rank, const vector<vector<Edge>>& graph_adj, 
                    vector<vector<int>>& L_v, vector<vector<int>>& L_d, 
                    vector<int>& P, vector<int>& T, vector<int>& visited_P, vector<int>& visited_T,
                    // Để check prune, ta cần label đối nghịch (nếu đang đi xuôi thì cần check label ngược)
                    const vector<vector<int>>& L_opp_v, const vector<vector<int>>& L_opp_d,
                    const vector<int>& rank_map) {
        
        // B1: Chuẩn bị mảng T từ Label đối nghịch để prune nhanh
        for (size_t idx = 0; idx < L_opp_v[hub].size(); idx++) {
            int h = L_opp_v[hub][idx];
            if (h != -1) {
                T[h] = L_opp_d[hub][idx];
                visited_T.push_back(h);
            }
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        P[hub] = 0;
        pq.push({0, hub});
        visited_P.push_back(hub);

        while (!pq.empty()) {
            pair<int,int> cur = pq.top(); pq.pop();
            int d = cur.first, u = cur.second;
            if (d > P[u]) continue;

            // CHECK PRUNING: Liệu đã có đường đi u -> ... -> hub ngắn hơn chưa?
            int query_dist = INF;
            for (size_t idx = 0; idx < L_v[u].size(); idx++) {
                int h = L_v[u][idx];
                if (h != -1 && T[h] != INF) {
                    query_dist = min(query_dist, L_d[u][idx] + T[h]);
                }
            }
            if (query_dist <= d) continue;

            // Nếu không bị prune -> Thêm Hub vào Label
            L_v[u].push_back(rank);
            L_d[u].push_back(d);

            // Loang tiếp
            for (const auto& edge : graph_adj[u]) {
                int v = edge.to;
                int w = edge.weight;
                // Chỉ đi đến đỉnh có rank cao hơn (chưa làm Hub) để đảm bảo DAG
                // Lưu ý: Trong thực tế ta so sánh order_map[v] > rank
                if (P[v] == INF) visited_P.push_back(v);
                if (rank_map[v] > rank && d + w < P[v]) {
                    P[v] = d + w;
                    pq.push({P[v], v});
                }
            }
        }

        // Cleanup
        for (int v : visited_P) P[v] = INF; visited_P.clear();
        for (int h : visited_T) T[h] = INF; visited_T.clear();
    }

public:
    int N;
    // L_in: Hub -> u (Dùng graph xuôi)
    vector<vector<int>> Lin_v, Lin_d;
    // L_out: u -> Hub (Dùng graph ngược)
    vector<vector<int>> Lout_v, Lout_d;

    PrunedLabeling(int n) : N(n), Lin_v(n), Lin_d(n), Lout_v(n), Lout_d(n) {}

    int query(int u, int v) {
        // Khoảng cách u -> v là giao của L_out(u) và L_in(v)
        return intersect(Lout_v[u], Lout_d[u], Lin_v[v], Lin_d[v]);
    }

    void build(const Graph& g, const vector<int>& order) {
        vector<int> rank_map(N); // Ánh xạ ID -> Rank
        for(int i=0; i<N; i++) rank_map[order[i]] = i;

        vector<int> P(N, INF), T(N, INF);
        vector<int> vis_P, vis_T;

        for (int i = 0; i < N; i++) {
            int hub = order[i];
            // Dijkstra trên đồ thị ban đầu
            pruned_dijkstra(hub, i, g.adj, Lin_v, Lin_d, P, T, vis_P, vis_T, Lout_v, Lout_d, rank_map);

            // Dijkstra trên đồ thị ngược
            pruned_dijkstra(hub, i, g.rev_adj, Lout_v, Lout_d, P, T, vis_P, vis_T, Lin_v, Lin_d, rank_map);
        }

        // Sentinel
        for(int i=0; i<N; i++) {
            Lin_v[i].push_back(-1); Lin_d[i].push_back(INF);
            Lout_v[i].push_back(-1); Lout_d[i].push_back(INF);
        }
    }
};