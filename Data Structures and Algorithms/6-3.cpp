/*6-3 滑动平均值
题目描述
给定一个长度为n的数组，以及一个长度为k的窗口，窗口从数组的最左端开始滑动，每次滑动一个位置，求每次滑动后窗口内元素的平均值。

为了避免浮点数运算，我们只需要将平均值向零取整，即与C++中的整数类型的除法运算相同。

输入描述
第1行，两个整数n和k，表示数组的长度和窗口的长度(1≤n≤2×10 5,1≤k≤n)。
第2行，n个整数a1,a2,…,an，表示数组的元素。
数据保证数组元素的绝对值不超过10 9。

输出描述
输出(n−k+1)个整数，表示每次滑动后窗口内元素的平均值（向零取整）。*/
#include <iostream>
#include <vector>
using namespace std;

int average( long int sum, long int k) {
    return sum / k; 
}

int main() {
    long int n, k;
    cin >> n >> k; 

    vector<long int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i]; 
    }

    vector<int> b(n - k + 1); 
    long int sum = 0;
    for (int i = 0; i < k; i++) {
        sum += a[i];
    }
    b[0] = average(sum, k); 
    for (int j = 1; j <= n - k; j++) {
        sum = sum - a[j - 1] + a[j + k - 1]; // 更新窗口的和
        b[j] = average(sum, k); // 计算新的平均值
    }

    // 输出结果
    for (int j = 0; j < n - k + 1; j++) {
        cout << b[j] << " "; 
    }
    cout << endl; // 换行输出

    return 0;
}
