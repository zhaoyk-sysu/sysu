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
#include <stack>

using namespace std;

struct Node {
    string data;
    string lchild;
    string rchild;
};

void PreOrder(const unordered_map<string, Node>& tree, const string& root, vector<string>& result) {
    stack<string> s;
    s.push(root);
    
    while (!s.empty()) {
        string node = s.top();
        s.pop();
        
        if (node == "-" || tree.find(node) == tree.end()) continue;
        result.push_back(node);
        
        if (tree.at(node).rchild != "-") s.push(tree.at(node).rchild);
        if (tree.at(node).lchild != "-") s.push(tree.at(node).lchild);
    }
}

void InOrder(const unordered_map<string, Node>& tree, const string& root, vector<string>& result) {
    stack<string> s;
    string node = root;
    
    while (!s.empty() || node != "-") {
        if (node != "-" && tree.find(node) != tree.end()) {
            s.push(node);
            node = tree.at(node).lchild;
        } else {
            if (!s.empty()) {
                node = s.top();
                s.pop();
                result.push_back(node);
                node = tree.at(node).rchild;
            } else {
                break;
            }
        }
    }
}

void PostOrder(const unordered_map<string, Node>& tree, const string& root, vector<string>& result) {
    stack<string> s1, s2;
    s1.push(root);
    
    while (!s1.empty()) {
        string node = s1.top();
        s1.pop();
        
        if (node == "-" || tree.find(node) == tree.end()) continue;
        s2.push(node);
        
        if (tree.at(node).lchild != "-") s1.push(tree.at(node).lchild);
        if (tree.at(node).rchild != "-") s1.push(tree.at(node).rchild);
    }
    
    while (!s2.empty()) {
        result.push_back(s2.top());
        s2.pop();
    }
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
        if (i == 0) root = data; 
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
