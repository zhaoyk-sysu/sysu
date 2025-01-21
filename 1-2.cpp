/*1-2 跳台阶
题目描述
一只青蛙一次可以跳上1级台阶，也可以跳上2级。

求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。

输入描述
第一行为t，表示测试数
接下来t行，每行包括整数n，表示台阶总数 n <= 30

输出描述
总共输出t行，每行包含一个整数，为跳法的总数。*/
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;

    vector<int> a(t);
    vector<int> p(t);
    vector<int> b(100);  // 用于保存斐波那契数列
    int k = 3;

    // 输入数据
    for (int i = 0; i < t; i++) {
        cin >> a[i];
        if (a[i] == 1) {
            p[i] = 1;
        } else if (a[i] == 2) {
            p[i] = 2;
        } else {
            b[1] = 1;
            b[2] = 2;
            for (k = 3; k <= a[i]; k++) {
                b[k] = b[k - 1] + b[k - 2];
            }
            p[i] = b[a[i]];
        }
    }

    // 输出结果
    for (int i = 0; i < t; i++) {
        cout << p[i] << endl;
    }

    return 0;
}
