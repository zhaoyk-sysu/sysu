/*5-1 合法的括号序列
题目描述
输入一个长度为n的括号序列，判断这个括号序列是否合法。合法的括号序列定义如下：
空序列是合法的。
如果A是合法的，则(A), [A], {A}都是合法的。
如果A和B是合法的，则AB是合法的。
除以上情况，其他情况均为非法。

注意：测试数据中存在多组数据。

输入描述
第1行，一个整数T (T≤100)，表示数据组数。
接下来是T组数据，每组数据一行，长度不超过2×10 3的非空字符串，表示括号序列。
数据保证括号序列仅包含这些字符：(, ), [, ], {, }。

输出描述
对于每组数据，输出一行，如果这个括号序列合法，则输出YES，否则输出NO。
注意区分大小写。*/
#include <iostream>  
#include <stack>  
#include <string>  
#include <unordered_map>  
  
using namespace std;  
  
bool isValid(string s) {  
    unordered_map<char, int> m{{'(', 1}, {'[', 2}, {'{', 3},  
                               {')', 4}, {']', 5}, {'}', 6}};  
    stack<char> st;  
    for (char c : s) {  
        int flag = m[c];  
        if (flag >= 1 && flag <= 3) {  
            st.push(c);  
        } else if (!st.empty() && m[st.top()] == flag - 3) {  
            st.pop();  
        } else {  
            return false;  
        }  
    }  
    return st.empty();  
}  
  
int main() {  
    int T;  
    cin >> T;  
    cin.ignore();  // ���Ի��з�  
  
    for (int i = 0; i < T; ++i) {  
        string sequence;  
        getline(cin, sequence);  
        if (isValid(sequence)) {  
            cout << "YES" << endl;  
        } else {  
            cout << "NO" << endl;  
        }  
    }  
  
    return 0;  
}

