#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Mo file goc cua Stanford
    ifstream infile("data/facebook_combined.txt");
    if (!infile.is_open()) {
        cout << "Loi: Khong tim thay file data/facebook_combined.txt!\n";
        return 1;
    }

    // Mo file moi de ghi ket qua
    ofstream outfile("data/facebook_formatted.txt");

    int u, v;
    vector<pair<int, int>> edges;
    int max_node = 0;

    // Doc tung dong u v
    while (infile >> u >> v) {
        edges.push_back({u, v});
        if (u > max_node) max_node = u;
        if (v > max_node) max_node = v;
    }

    int N = max_node + 1; // Vi ID bat dau tu 0
    int M = edges.size();

    // Ghi dong Header: N M Type (0 = Vo huong)
    outfile << N << " " << M << " 0\n";

    // Ghi lai cac canh, tu dong them trong so w = 1
    for (const auto& edge : edges) {
        outfile << edge.first << " " << edge.second << " 1\n";
    }

    cout << "Format thanh cong!\n";
    cout << "So dinh (N): " << N << "\n";
    cout << "So canh (M): " << M << "\n";
    cout << "File moi da duoc luu tai: data/facebook_formatted.txt\n";

    infile.close();
    outfile.close();
    return 0;
}