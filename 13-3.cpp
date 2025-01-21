/*13-3 有向无环图的判定
题目描述
给定一个n个节点m条边的有向图G，节点编号从1到n，保证图中没有重边和自环。

现在，你要判断这个图是否是有向无环图。
一个有向图被称为无环图，当且仅当图中不存在环，即不存在一条路径使得从某个节点出发，经过若干条边后又回到该节点。

注意：测试数据中存在多组数据。

输入描述
第1行，一个整数T (T≤20)，表示数据组数。
接下来是T组数据，每组数据：
第1行包含两个整数n,m (2≤n≤500,1≤m≤10 
4
 )，表示节点个数和边数。
接下来m行，每行包含两个整数u,v (1≤u,v≤n)，表示一条连接节点u和节点v的无向边。
最后接1行空行。

数据保证图中没有重边。

输出描述
对于每组数据，输出一行，如果图G是有向无环图，输出YES，否则输出NO。*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isDAG(int n, int m, vector<pair<int, int>>& edges) {
    vector<vector<int>> graph(n + 1);  
    vector<int> inDegree(n + 1, 0);  
    for (auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        graph[u].push_back(v);
        inDegree[v]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (inDegree[i] == 0) {
            q.push(i); 
        }
    }

    int count = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        count++;

        for (int neighbor : graph[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return count == n;  
}

int main() {
    int T;
    cin >> T; 
    while (T--) {
        int n, m;
        cin >> n >> m;  
        vector<pair<int, int>> edges(m);
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].first >> edges[i].second;  
        }

        if (isDAG(n, m, edges)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }

        if (T > 0) {
            cin.ignore();  
        }
    }
    return 0;
}
