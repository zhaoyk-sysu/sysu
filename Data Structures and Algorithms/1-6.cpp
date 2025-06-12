/*1-6 数组的查找
问题描述
输入一个长度为5的int型数组和待查找的key值，如果数组中存在该key值的话，输出其在数组中的位置。

输入描述
一行6个整数。分别为长度为5的int数组和待查找的key值

输出描述
输出key值在数组中的位置（从0开始编号），如果有多个的话，从小到大每行输出一个；如果数组中不存在这个值的话输出-1。*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> a(5); // 定义长度为5的数组
    int key;          // 用于存储待查找的key值

    // 输入数组和key值
    for (int i = 0; i < 5; ++i) {
        cin >> a[i];
    }
    cin >> key;

    // 查找key值
    bool found = false; // 标记是否找到key
    for (int i = 0; i < 5; ++i) {
        if (a[i] == key) {
            cout << i << endl; // 输出key值的位置
            found = true;
        }
    }

    // 如果未找到，输出-1
    if (!found) {
        cout << -1 << endl;
    }

    return 0;
}
