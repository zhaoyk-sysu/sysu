/*插入排序*/
#include <iostream>
#include <vector>

using namespace std;

void insertsor(vector<int>& a, int n) {
    int i, j;
    for (i = 2; i <= n; i++) {
        int key = a[i];
        j = i - 1;
        while (j >= 1 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
        for (int k = 1; k <= n; k++) {
            cout << a[k] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    insertsor(a, n);
    return 0;
}
