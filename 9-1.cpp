/* 9-1 堆否
题目描述
给定一个长度为n的数组a=[a 
1
​
 ,a 
2
​
 ,⋯,a 
n
​
 ]，判断由a定义的完全二叉树是否是小根堆。在这里，完全二叉树的根节点是a 
1，第二层子节点是a 2和a 3，第三层子节点是a 4,a 5,a 6,a 7，以此类推。
一棵完全二叉树是小根堆，当且仅当对于任意1≤i,j≤n，若i是j的父结点，则a i≤aj。

注意：测试数据中存在多组数据。

输入描述
第1行，一个整数T (T≤100)，表示数据组数。
接下来是T组数据，每组数据：
第1行，一个整数n (1≤n≤10 5)，表示数组长度。
第2行，n个整数a 1,a 
2,⋯,a n(∣a i∣≤10 6)，表示数组a。

数据保证所有数组长度之和不超过10 6。

输出描述
对于每组数据，输出一行，如果这个数组是小根堆，则输出YES，否则输出NO。
注意区分大小写。*/
#include <iostream>
#include <vector>

using namespace std;

bool isMinHeap(const vector<int>& a, int n) {
    for (int i = 1; i <= n / 2; i++) {  
        if (2 * i <= n && a[i] > a[2 * i]) { 
            return false;
        }
        if (2 * i + 1 <= n && a[i] > a[2 * i + 1]) {  // 检查右子节点
            return false;
        }
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);  
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        if (isMinHeap(a, n)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
