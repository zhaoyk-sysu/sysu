/*1-1 猜数字
问题描述
小A和小B在玩猜数字。小B每次从1, 2, 3中随机选择一个，小A每次也从1, 2, 3中选择一个猜。他们一共进行三次这个游戏，请返回小A猜对了几次？

输入描述
第一行为t，表示测试数
接下来t行，每行有6个[1,2,3]中的数字，前三个为小A，后三个为小B

输出描述
t行，每行一个数字
*/
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;

    vector<int> p(t * 6);
    vector<int> a(t, 0);

    // 输入数据
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < 6; j++) {
            cin >> p[i * 6 + j];
        }
    }

    // 处理数据
    for (int i = 0; i < t; i++) {
        for (int k = 0; k < 3; k++) {
            if (p[i * 6 + k] == p[i * 6 + k + 3]) {
                a[i]++;
            }
        }
        cout << a[i] << endl;
    }

    return 0;
}
