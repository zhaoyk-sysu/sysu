/*14-1 最小生成树
题目描述
给定一个n个节点m条边的连通的带权无向图G，节点编号从1到n，图中可能有重边。

现在，你要求这个图的最小生成树，并输出最小生成树的权值。

输入描述
第1行包含两个整数n,m (2≤n≤10 
3
 ,n−1≤m≤10 
5
 )，表示节点个数和边数。
接下来m行，每行包含三个整数u,v,w (1≤u,v≤n,1≤w≤10 
9
 )，表示从节点u和节点v有一条权值为w的无向边。

输出描述
输出一个整数，表示最小生成树的权值。*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    int weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight; 
    }
};

class UnionFind {
public:
    vector<int> parent, rank;

    UnionFind(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i; 
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); 
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return false;

        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    sort(edges.begin(), edges.end());

    UnionFind uf(n);
    long long mstWeight = 0;
    int edgesUsed = 0;

    for (const auto& edge : edges) {
        if (uf.unite(edge.u, edge.v)) { 
            mstWeight += edge.weight;
            edgesUsed++;
            if (edgesUsed == n - 1) break; 
        }
    }

    cout << mstWeight << endl;

    return 0;
}
