/*9-3 二叉树的三种遍历
题目描述
给定一棵大小为n的二叉树，其结点名称使用字符串标识。每个结点的字符串由大写字母构成，且长度不超过6。
现在，你要输出这棵二叉树的先序、中序和后序遍历结果。输入描述
第一行包含一个整数n (1≤n≤10 
4
 )，表示节点个数。
接下来n行，每行包含3个用空格分隔的字符串s 
i
​
 ,l 
i
​
 ,r 
i
​
 ，表示节点的名称和左右子节点。如果子节点为空，则用-（减号）表示。

输入保证节点的字符串名称是两两不同，并且名称是长度不超过6的大写字母序列。
输入保证二叉树的形态是合法的。

输出描述
三行，每行是n个用空格隔开的字符串，分别表示先序、中序和后序遍历结果。*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct Node {
    string data;
    string lchild;
    string rchild;
};
void PreOrder(const unordered_map<string, Node>& tree, const string& node, vector<string>& result) {
    if (node == "-") return;
    result.push_back(node);
    PreOrder(tree, tree.at(node).lchild, result);
    PreOrder(tree, tree.at(node).rchild, result);
}

void InOrder(const unordered_map<string, Node>& tree, const string& node, vector<string>& result) {
    if (node == "-") return;
    InOrder(tree, tree.at(node).lchild, result);
    result.push_back(node);
    InOrder(tree, tree.at(node).rchild, result);
}

void PostOrder(const unordered_map<string, Node>& tree, const string& node, vector<string>& result) {
    if (node == "-") return;
    PostOrder(tree, tree.at(node).lchild, result);
    PostOrder(tree, tree.at(node).rchild, result);
    result.push_back(node);
}

   int main() {
    int n;
    cin >> n;

    unordered_map<string, Node> tree;
    string root;

    for (int i = 0; i < n; i++) {
        string data, lchild, rchild;
        cin >> data >> lchild >> rchild;
        tree[data] = {data, lchild, rchild};
        if (i == 0) root = data; // Assume first input node is the root
    }

    vector<string> preorder, inorder, postorder;

    PreOrder(tree, root, preorder);
    InOrder(tree, root, inorder);
    PostOrder(tree, root, postorder);

    for (const auto& node : preorder) cout << node << " ";
    cout << endl;
    for (const auto& node : inorder) cout << node << " ";
    cout << endl;
    for (const auto& node : postorder) cout << node << " ";
    cout << endl;

    return 0;
}
   
