/*2-2 k阶斐波那契序列
题目描述
已知k阶Fibonacci数列的定义为

f 
0
​
 =f 
1
​
 =⋯=f 
k−2
​
 =0,f 
k−1
​
 =1.
f 
n
​
 =f 
n−1
​
 +f 
n−2
​
 +⋯+f 
n−k
​
 , n=k,k+1,⋯

编写一个函数，求k阶Fibonacci数列的第n项，结果对2 
32
 取模。

输入描述
1行，两个整数k,n (2≤k≤100,0≤n≤1000)，分别为Fibonacci数列的阶数和要求的项数。

输出描述
1行，一个整数，表示k阶Fibonacci数列的第n项，结果对2 
的32次方取模。
使用unsigned int类型存储和计算，即可自动对2的32次方 取模*/
#include <iostream>
#include <vector>
using namespace std;

unsigned int kthFibonacci(int k, int n) {
    if (n < k - 1) return 0; // 第n项小于k-1，值为0
    if (n == k - 1) return 1; // 第n项等于k-1，值为1

    vector<unsigned int> f(n + 1, 0); // 存储数列
    f[k - 1] = 1; // 初始化第k-1项为1

    // 动态规划计算k阶Fibonacci数列
    for (int i = k; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            f[i] += f[i - j];
        }
    }

    return f[n]; // 返回第n项
}

int main() {
    int k, n;
    cin >> k >> n; // 输入k和n
    cout << kthFibonacci(k, n) << endl; // 输出第n项
    return 0;
}
