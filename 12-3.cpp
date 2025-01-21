/*12-3 图的二分性
题目描述
给定一个n个节点m条边的无向图G，节点编号从1到n，保证图中没有重边和自环。

现在，你要判断这个图是否是二分图。
一个图被称为二分图，当且仅当图的所有节点可以被染成黑白两种颜色，使得任意一条边的两个端点颜色不同。

注意：测试数据中存在多组数据。

输入描述
第1行，一个整数T (T≤20)，表示数据组数。
接下来是T组数据，每组数据：
第1行包含两个整数n,m (2≤n≤500,1≤m≤10 
4
 )，表示节点个数和边数。
接下来m行，每行包含两个整数u,v (1≤u,v≤n)，表示一条连接节点u和节点v的无向边。
最后接1行空行。

数据保证图中没有重边和自环。

输出描述
对于每组数据，输出一行，如果图G是二分图，输出YES，否则输出NO。*/
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

bool isBipartite(int n, vector<vector<int>>& adj) {
    vector<int> color(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        if (color[i] == 0) { 
            queue<int> q;
            q.push(i);
            color[i] = 1; 

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int neighbor : adj[node]) {
                    if (color[neighbor] == 0) { 
                        color[neighbor] = -color[node];
                        q.push(neighbor);
                    } else if (color[neighbor] == color[node]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    int T;
    cin >> T; 
    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n + 1); 
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        if (isBipartite(n, adj)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
