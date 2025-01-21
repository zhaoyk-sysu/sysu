/*快速排序*/
#include <iostream>
#include <vector>

using namespace std;


int partition(vector<int>& a, int low, int high) {
    int pivot = a[low]; 
    int i = low, j = high;

    while (i < j) {
     
        while (i < j && a[j] > pivot) {
            j--;
        }
       
        while (i < j && a[i] <= pivot) {
            i++;
        }
        
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
  
    swap(a[low], a[i]);
    return i; 
}


void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); 

        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    quickSort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
