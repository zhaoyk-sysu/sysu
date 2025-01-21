/*15-2 二分查找
题目描述
给定一个长度为n的升序整数数组a，以及q个询问，每个询问包含一个整数x。
你需要对于每个询问，判断数组a中是否存在一个元素等于x。

输入描述
第1行，2个整数n,q (1≤n,q≤10 
5
 )，表示数组a的长度和询问的个数。
第2行，n个整数a 
i
​
  (∣a 
i
​
 ∣≤10 
9
 )，表示数组a的元素。
第3行，q个整数x 
j
​
  (∣x 
j
​
 ∣≤10 
9
 )，表示q个询问。

输出描述
对于每个询问，输出一行：

如果数组a中存在一个元素等于x，输出YES；
否则，输出NO。*/
#include <iostream>
#include <vector>
#include <algorithm> // 用于二分查找
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    while (q--) {
        int x;
        cin >> x;

        if (binary_search(a.begin(), a.end(), x)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
