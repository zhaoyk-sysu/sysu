/*11-1 有序树的遍历
题目描述
给定一棵大小为n的有序树，编号为i (1≤i≤n)的节点有m 
i
​
 个子节点，他们从左到右编号分别为c 
i,1
​
 ,c 
i,2
​
 ,⋯,c 
i,m 
i
​
 
​
 。

现在，你要输出这棵有序树的先序、后序与层次遍历结果。

输入描述
第一行包含一个整数n (1≤n≤2×10 
4
 )，表示节点个数。
接下来n行，第i行包含m 
i
​
 +1个整数，第一个整数m 
i
​
  (0≤m 
i
​
 ≤n)表示节点i的子节点个数，接下来的m 
i
​
 个整数c 
i,1
​
 ,c 
i,2
​
 ,⋯,c 
i,m 
i
​
 
​
 表示节点i从左到右的子节点编号。

输入保证有序树的形态是合法的。

输出描述
三行，每行是n个用空格隔开的整数，分别表示先序、后序与层次遍历结果。*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> tree;
vector<int> preorder_result, postorder_result, levelorder_result;

// 先序遍历
void preorder(int node) {
    preorder_result.push_back(node);
    for (int child : tree[node]) {
        preorder(child);
    }
}

// 后序遍历
void postorder(int node) {
    for (int child : tree[node]) {
        postorder(child);
    }
    postorder_result.push_back(node);
}

// 层次遍历
void level_order(int root) {
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        levelorder_result.push_back(node);
        for (int child : tree[node]) {
            q.push(child);
        }
    }
}

int main() {
    int n;
    cin >> n;
    tree.resize(n + 1); 
    vector<bool> is_child(n + 1, false); 
    for (int i = 1; i <= n; i++) {
        int m;
        cin >> m;
        for (int j = 0; j < m; j++) {
            int child;
            cin >> child;
            tree[i].push_back(child);
            is_child[child] = true;
        }
    }

    int root = 1;
    for (int i = 1; i <= n; i++) {
        if (!is_child[i]) {
            root = i;
            break;
        }
    }

    preorder(root);
    postorder(root);
    level_order(root);

    for (int i = 0; i < preorder_result.size(); i++) {
        cout << preorder_result[i] << (i < preorder_result.size() - 1 ? " " : "\n");
    }
    for (int i = 0; i < postorder_result.size(); i++) {
        cout << postorder_result[i] << (i < postorder_result.size() - 1 ? " " : "\n");
    }
    for (int i = 0; i < levelorder_result.size(); i++) {
        cout << levelorder_result[i] << (i < levelorder_result.size() - 1 ? " " : "\n");
    }

    return 0;
}
