/*14-2 单条最短路
题目描述
给定一个n个节点m条边的带权有向图G，节点编号从1到n，保证图中没有重边和自环。

现在，你要求这个图中节点1到节点n的最短路径的权值。

输入描述
第1行包含两个整数n,m (2≤n≤10 
3
 ,1≤m≤10 
5
 )，表示节点个数和边数。
接下来m行，每行包含三个整数u,v,w (1≤u,v≤n,1≤w≤10 
9
 )，表示从节点u和节点v有一条权值为w的有向边。

输出描述
输出一个整数，表示节点1到节点n的最短路径的权值，如果不存在这样的路径，输出−1。*/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int v, w;
    Edge(int _v, int _w) : v(_v), w(_w) {}
};

typedef pair<int, int> P;

int dijkstra(int n, vector<vector<Edge>>& graph) {
    vector<int> dist(n + 1, INT_MAX); 
    priority_queue<P, vector<P>, greater<P>> pq;
    dist[1] = 0; 
    pq.push({0, 1}); 
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        
        if (d > dist[u]) continue;

        
        for (const Edge& edge : graph[u]) {
            int v = edge.v;
            int w = edge.w;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    
    return dist[n] == INT_MAX ? -1 : dist[n];
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<Edge>> graph(n + 1);
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(Edge(v, w));
    }

    int result = dijkstra(n, graph);
    
    cout << result << endl;

    return 0;
}
