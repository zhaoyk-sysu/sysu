/*15-1 拓扑排序
题目描述
给定一个n个节点m条边的有向无环图G，节点编号从1到n，保证图中没有重边。

现在，你要输出图G的拓扑排序，如果图G有多个拓扑排序，输出字典序最小的那个。

拓扑排序：对于有向图G，如果存在一种节点的排列顺序，使得对于图中的每一条边(u,v)，u在排列中出现在v之前，那么这种排列被称为图G的拓扑排序。

输入描述
第1行包含两个整数n,m (2≤n≤5×10 
3
 ,1≤m≤5×10 
4
 )，表示节点个数和边数。
接下来m行，每行包含两个整数u,v (1≤u,v≤n)，表示一条连接节点u和节点v的有向边。

数据保证图中没有重边和回路。

输出描述
一行，n个整数，表示图G的拓扑排序。如果图G有多个拓扑排序，输出字典序最小的那个。*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool TopSort(vector<vector<int>> &G, int n, vector<int> &inDegree) {
    int num = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            pq.push(i);
        }
    }

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        cout << u + 1 << " ";
        num++;

        for (int v : G[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                pq.push(v);
            }
        }
    }

    return (num == n);
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n);
    vector<int> inDegree(n, 0);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        G[x - 1].push_back(y - 1);
        inDegree[y - 1]++;
    }

    if (!TopSort(G, n, inDegree)) {
        cout << "拓扑排序失败，图中有环" << endl;
    }

    return 0;
}
