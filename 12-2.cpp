/*12-2图的邻接表 */
//读取一个输入的时候先将其进栈，处理完还是三的倍数的再入栈，不是三的倍数的录入邻接数组
//对于可能出现的重边问题，用三位数组存储

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Edge {
    int v, w;
    Edge(int v, int w) : v(v), w(w) {}
};

bool cmp(const Edge &a, const Edge &b) {
    if (a.v == b.v) return a.w < b.w;
    return a.v < b.v;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> adj(n + 1);  

    stack<vector<int>> s;  

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        s.push({u, v, w});  

        while (!s.empty()) {
            vector<int> edge = s.top();
            s.pop();

            int u = edge[0], v = edge[1], w = edge[2];

            if (w % 3 != 0) {
   
                adj[u].push_back(Edge(v, w));
            } else {
     
                s.push({u, v, 2 * w / 3});  
                s.push({v, u, w / 3});     
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end(), cmp);

        cout << adj[i].size();
        for (const Edge &e : adj[i]) {
            cout << " (" << e.v << ", " << e.w << ")";
        }
        cout << endl;
    }

    return 0;
}

