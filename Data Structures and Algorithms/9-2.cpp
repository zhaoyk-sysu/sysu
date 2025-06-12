/*9-2 子树价值
题目描述
给定一棵大小为n的二叉树，编号为i (1≤i≤n)节点的权重是w 
i
​
 ，左子节点编号是l 
i
​
 ，右子节点编号是r 
i
​
 。求每个节点为根的子树价值。

子树价值等于其根节点的权重加上左右子树价值中的较大值。特别地，空子树的价值为0。

输入描述
第一行包含一个整数n (1≤n≤10 
5
 )，表示节点个数。
接下来n行，第i (1≤i≤n)行包含三个整数w 
i,l i,r i(0≤w i≤10 4,1≤l i,r i≤n)，表示节点i的权重和左右子节点编号，编号为0表示没有对应的子节点。
输入保证树的节点编号从1到n，并且二叉树的形态是合法的。

输出描述
n行，每行一个整数，第i行表示以节点i为根的子树价值。*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int data;     
    int lchild;    
    int rchild;    
};


int calculateSubtreeValue(int node, vector<Node>& tree, vector<int>& values) {
    if (node == 0) return 0; 
    if (values[node] != -1) return values[node]; 

    int left_value = calculateSubtreeValue(tree[node].lchild, tree, values);  
    int right_value = calculateSubtreeValue(tree[node].rchild, tree, values);

    values[node] = tree[node].data + max(left_value, right_value);
    return values[node];
}

int main() {
    int n;
    cin >> n;

    vector<Node> tree(n + 1);  
    vector<int> values(n + 1, -1);  

    for (int i = 1; i <= n; i++) {
        cin >> tree[i].data >> tree[i].lchild >> tree[i].rchild;
    }

    for (int i = 1; i <= n; i++) {
        calculateSubtreeValue(i, tree, values);
    }

    for (int i = 1; i <= n; i++) {
        cout << values[i] << endl;
    }

    return 0;
}
