#include <vector>
#include <algorithm>
#include <cmath>
#include <stdio.h>
using namespace std;

class UnionFind {
public:
    UnionFind(int size) : parent(size), rank(size, 1) {
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    bool unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU] += 1;
            }
            return true;
        }
        return false;
    }

private:
    vector<int> parent;
    vector<int> rank;
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<tuple<int, int, int>> edges;

        auto manhattan_dist = [](const vector<int>& p1, const vector<int>& p2) {
            return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
        };

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                edges.push_back({manhattan_dist(points[i], points[j]), i, j});
            }
        }

        sort(edges.begin(), edges.end());

        UnionFind uf(n);
        int cost = 0;
        for (const auto& [d, u, v] : edges) {
            if (uf.unionSets(u, v)) {
                cost += d;
            }
        }

        return cost;
    }
};