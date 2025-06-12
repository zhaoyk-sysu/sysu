/* 8-1 马赛克
题目描述
输入一个高为m，宽为n的图片，图片中的每个像素点的灰度值为0到255之间的整数。
现在有一种马赛克工具，它的工作网格宽度为w，它会将图片划分成大小为w×w的网格，然后将每个网格中的像素点的灰度值取平均值，作为这个网格所有像素的灰度值。如果图片的高（宽）不能被w整除，那么最后一行（一列）的网格的高度（宽度）可能会小于w。

注意，你需要将每个像素点的灰度值舍入到最近的整数，如果平均值恰好是半整数，那么舍入到最近的偶数。

请你计算出最终的图片。

输入描述
第一行包含两个整数m,n,w (1≤m,n≤2×10 3)，表示图片的高和宽，以及马赛克工具的网格宽度。
接下来m行，每行包含n个整数，表示图片的像素点的灰度值（0到255之间）。

数据保证总像素点数量mn≤2×10 4。

输出描述
输出m行，每行包含n个整数，表示最终的图片。

*/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int round_half_to_even(double value) {
    int rounded = round(value);
    if (fabs(value - rounded) == 0.5) {
        if (rounded % 2 != 0) {
            rounded += (value > 0) ? -1 : 1;
        }
    }
    return rounded;
}

int main() {
    int m, n, w;
    cin >> m >> n >> w;
 
    vector<vector<int> > ma(m, vector<int>(n));
 
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> ma[i][j];
        }
    }
 
    vector<vector<int> > result(m, vector<int>(n, 0));
    for (int i = 0; i < m; i += w) {
        for (int j = 0; j < n; j += w) {
            int sum = 0, count = 0;
            
            for (int x = i; x < min(i + w, m); x++) {
                for (int y = j; y < min(j + w, n); y++) {
                    sum += ma[x][y];
                    count++;
                }
            }

            int average = round_half_to_even(static_cast<double>(sum) / count);

            for (int x = i; x < min(i + w, m); x++) {
                for (int y = j; y < min(j + w, n); y++) {
                    result[x][y] = average;
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
