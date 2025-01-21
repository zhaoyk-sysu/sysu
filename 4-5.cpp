/*4-5 合法的出栈序列
题目描述
将n个整数1,2,3,…,n依次进栈，其中穿插着n个合法的出栈操作。
现在观察到一个出栈序列：a1,a2,…,an，并且这个序列是n个整数1,2,…,n的一个排列。
问：这个出栈序列是否可能是由这n个整数依次进栈得到的？

注意：测试数据中存在多组数据。

输入描述
第1行，一个整数T (T≤50)，表示数据组数。
接下来是T组数据，每组数据包含：
第1行，一个整数n (1≤n≤5×10 3)，表示整数的个数。
第2行，n个整数a 1,a2,…,an(1≤ai≤n)，表示出栈序列。
数据保证这个出栈序列是1,2,…,n的一个排列。

输出描述
对于每组数据，输出一行，如果这个出栈序列可能是由1,2,…,n这n个整数依次进栈得到的，则输出YES，否则输出NO。
注意区分大小写。*/
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;  // 输入数据组数

    while (T--) {
        int n;
        cin >> n;  // 输入整数个数
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];  // 输入出栈序列
        }

        stack<int> s;  // 栈
        int current = 1;  // 当前正在压栈的数字
        bool isValid = true;  // 是否是合法的出栈序列

        // 模拟栈操作
        for (int i = 0; i < n; i++) {
            while (current <= a[i]) {
                s.push(current++);  // 将当前数字压栈，直到栈顶是 a[i]
            }
            
            // 如果栈顶元素等于当前需要的出栈元素，则出栈
            if (s.top() == a[i]) {
                s.pop();
            } else {
                // 如果栈顶元素不等于当前需要的出栈元素，说明不可能得到该序列
                isValid = false;
                break;
            }
        }

        // 输出结果
        if (isValid) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
