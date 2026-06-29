#include <iostream>
using namespace std;

template <typename T>
int binarySearch(T* arr, int size, T key) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}

int main() {
    int arr[] = { 12, 77, 87, 89, 100, 117, 125, 189, 235, 529, 1000 };

    int intKey = 18;
    int result = binarySearch(arr, sizeof(arr) / sizeof(arr[0]), intKey);
    cout << "Int index: " << (result == -1 ? "Not found" : to_string(result)) << endl;
    return 0;
}

