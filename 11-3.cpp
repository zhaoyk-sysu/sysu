/*11-3 树否
题目描述
给定一个n个节点m条边的无向图G，节点编号从1到n，保证图中没有重边和自环。

现在，你要判断是否能够通过断开一些边，使得图G变成一棵树。
注意：测试数据中存在多组数据。

输入描述
第1行，一个整数T (T≤20)，表示数据组数。
接下来是T组数据，每组数据：
第1行包含两个整数n,m (2≤n≤10 
4
 ,1≤m≤4×10 
4
 )，表示节点个数和边数。
接下来m行，每行包含两个整数u,v (1≤u,v≤n)，表示一条连接节点u和节点v的无向边。
最后接1行空行。

输出描述
对于每组数据，输出一行，

如果G是一棵树，则输出TREE；否则
如果G不是一棵树，但是能够通过断开一些边，使其变成一棵树，则输出YES；否则
输出NO。*/
#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
public:
    vector<int> parent, rank;
    int components; 

    UnionFind(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        components = n;
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
    //判断是否成环，如果两个端点的根相同，证明其已经联通，再把这个边插进去会成环

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            components--; //一下一下把点连接起来
        }
    }
};

int main() {
    int T;
    cin >> T; 

    while (T--) {
        int n, m;
        cin >> n >> m;

        UnionFind uf(n);
        vector<pair<int, int>> edges;
        bool hasCycle = false;

        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            edges.emplace_back(u, v);
        }

        for (auto [u, v] : edges) {
            if (uf.find(u) == uf.find(v)) {
                hasCycle = true; 
            } else {
                uf.unite(u, v);
            }
        }

        if (uf.components == 1 && m == n - 1) {
            cout << "TREE" << endl; 
        } else if (uf.components == 1 && m > n - 1) {
            cout << "YES" << endl; 
        } else {
            cout << "NO" << endl; 
        }
    }

    return 0;
}
