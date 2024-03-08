#include <iostream>
using namespace std;

int binary_search(int arr[], int size, int target) {
    int l = 0, r = size - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (arr[m] == target) return m;
        else if (arr[m] < target) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

int main() {
    int arr[] = {1,2,3,4,5,6};
    int size = sizeof(arr)/sizeof(arr[0]);
    int target = 2;
    int target_index = binary_search(arr, size, target);
    if (target_index == -1) cout << "target is not in  array";
    else cout << "target is in array at index " << target_index; 
}