/*12-1 图的邻接矩阵
题目描述
给定一个n个节点m条边的带权有向图G，节点编号从1到n，保证图中没有重边。

现在，你要输出G的邻接矩阵A，即一个n×n的矩阵，其中A 
i,j
​
 表示从节点i到节点j的边的权值，如果不存在这样的边，则A 
i,j
​
 =−1。

输入描述
第1行包含两个整数n,m (1≤n≤10 
3
 ,1≤m≤2×10 
5
 )，表示节点个数和边数。
接下来m行，每行包含三个整数u,v,w (1≤u,v≤n,1≤w≤10 
9
 )，表示从节点u到节点v权值为w的有向边。

数据保证图中没有重边。

输出描述
输出一个n×n的矩阵，表示G的邻接矩阵，其中第i行第j列的元素表示从节点i到节点j的边的权值，如果不存在这样的边，则用−1表示。*/
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m; 

    vector<vector<int>> adj(n, vector<int>(n, -1));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w; 
        adj[u - 1][v - 1] = w;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adj[i][j];
            if (j < n - 1) cout << " "; 
        }
        cout << endl; 
    }

    return 0;
}
