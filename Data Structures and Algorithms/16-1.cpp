/*选择排序*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            swap(a[i], a[minIndex]);
        }

       
        for (int k = 0; k < n; ++k) {
            cout << a[k] << (k == n - 1 ? "\n" : " ");
        }
    }

    return 0;
}