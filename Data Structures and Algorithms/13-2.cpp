/*13-2 无向图的可达性
题目描述
给定一个n个节点m条边的无向图G，节点编号从1到n，保证图中没有重边和自环。

现在，有q个形如(u,v)的询问，你需要判断是否存在一条从节点u到节点v的路径。

输入描述
第一行包含两个整数n,m (2≤n≤10 
4
 ,1≤m≤2×10 
5
 )，表示节点个数和边数。
接下来m行，每行包含两个整数u,v (1≤u,v≤n)，表示一条连接节点u和节点v的无向边。
接下来一行包含一个整数q (1≤q≤10 
4
 )，表示询问个数。
接下来q行，每行包含两个整数u,v (1≤u,v≤n)，表示一次询问。

输出描述
对于每个询问，输出一行，如果存在一条从节点u到节点v的路径，输出YES，否则输出NO。*/
#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
public:
    vector<int> parent, size;
    UnionFind(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void union_sets(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX != rootY) {
            if (size[rootX] < size[rootY]) swap(rootX, rootY);
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    UnionFind uf(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        uf.union_sets(u, v);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int u, v;
        cin >> u >> v;
        if (uf.find(u) == uf.find(v)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
