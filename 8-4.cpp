/*8-4 分糖果
题目背景
在幼儿园里，每天老师都会给m个小朋友们分发n袋糖果。这些糖果袋被整齐地排成一列，每袋糖果的甜度为ai。为了确保每个小朋友都能开心地拿到糖果，老师希望将糖果尽量平均地分给小朋友们。如果糖果分配得不够均匀，有的小朋友可能会因为糖果少而哭泣，这让老师非常头疼。

为了避免这种情况，老师决定将糖果分成m个连续的子序列，并将第j个子序列的糖果分给第j个小朋友。也就是说，第j个小朋友会得到第j个子序列中的所有糖果，并且获得与这个子序列中甜度之和相同的快乐值。

老师希望找到一种划分方案，使得每个小朋友的快乐值尽量均匀。对于一种划分方案，我们定义这m个小朋友中快乐值最大的小朋友的快乐值为这种划分方案的代价。现在要求你计算出所有划分方案中代价的最小值。

题目描述
给定一个长度为n的正整数序列a1,a2,…,an，现在要将这个序列划分成m个连续的子序列，使得这m个子序列的和的最大值尽量小。

输入描述
第一行，两个整数n,m (1≤m≤n≤2×10 5)，表示序列的长度和要划分的子序列的个数。
第二行，n个正整数a1,a2,…,a n(1≤a i≤10 9)，表示这个序列。

输出描述
输出一个整数，表示所有划分方案中代价的最小值。*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canSplit(const vector<int>& candies, int n, int m, long long maxSum) {
    long long currentSum = 0;
    int count = 1; 

    for (int i = 0; i < n; ++i) {
        if (currentSum + candies[i] > maxSum) {
            count++;
            currentSum = candies[i];
            if (count > m) {
                return false;
            }
        } else {
            currentSum += candies[i];
        }
    }
    return true;
}

long long findMinimizedMaxSum(const vector<int>& candies, int n, int m) {
    long long left = *max_element(candies.begin(), candies.end());
    long long right = 0;
    for (int i = 0; i < n; ++i) {
        right += candies[i];
    }
    long long result = right;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (canSplit(candies, n, m, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> candies(n);
    for (int i = 0; i < n; ++i) {
        cin >> candies[i];
    }
    cout << findMinimizedMaxSum(candies, n, m) << endl;
    return 0;
}
