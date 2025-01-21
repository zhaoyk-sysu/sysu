/*10-2 二叉树的层次遍历
题目描述
给定一棵大小为n的二叉树，编号为i (1≤i≤n)节点的左子节点编号是l 
i
​
 ，右子节点编号是r 
i
​
 。
求该树的层次遍历结果。

输入描述
第一行包含一个整数n (1≤n≤10 
5
 )，表示节点个数。
接下来n行，第i (1≤i≤n)行包含两个个整数l 
i
​
 ,r 
i
​
  (1≤l 
i
​
 ,r 
i
​
 ≤n)，表示节点i的左右子节点编号，编号为0表示没有对应的子节点。

输出描述
输出n个整数，表示该树的层次遍历结果，节点之间用空格隔开，层之间用换行符隔开。*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct tree {
    int lchild;
    int rchild;
};
vector<tree> t;

void level_order(int root, int n) {
    queue<int> q;
    q.push(root);

    while (!q.empty()) {
        int level_size = q.size();  
        for (int i = 0; i < level_size; i++) {
            int node = q.front();
            q.pop();
            cout << node << (i < level_size - 1 ? " " : "");  

            if (t[node].lchild != 0) q.push(t[node].lchild);
            if (t[node].rchild != 0) q.push(t[node].rchild);
        }
        cout << endl;  
    }
}

int main() {
    int n;
    cin >> n;
    t.resize(n + 1);
    
    vector<bool> is_child(n + 1, false); 

    for (int i = 1; i <= n; i++) {
        cin >> t[i].lchild >> t[i].rchild;
        if (t[i].lchild != 0) is_child[t[i].lchild] = true;
        if (t[i].rchild != 0) is_child[t[i].rchild] = true;
    }

    int root = 1;
    for (int i = 1; i <= n; i++) {
        if (!is_child[i]) {
            root = i;
            break;
        }
    }

    level_order(root, n);
    return 0;
}
