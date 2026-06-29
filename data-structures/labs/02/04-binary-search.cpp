#include <iostream>
#include <string>
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
    int intArray[5] = { 11, 12, 22, 25, 64 };
    int intKey = 22;
    cout << "Int index: " << binarySearch(intArray, sizeof(intArray) / sizeof(intArray[0]), intKey) << endl;

    float floatArray[4] = { 0.57, 1.62, 2.71, 3.14 };
    float floatKey = 2.71;
    cout << "Float index: " << binarySearch(floatArray, sizeof(floatArray) / sizeof(floatArray[0]), floatKey) << endl;

    string stringArray[4] = { "apple", "banana", "grape", "orange" };
    string stringKey = "grape";
    cout << "String index: " << binarySearch(stringArray, sizeof(stringArray) / sizeof(stringArray[0]), stringKey) << endl;

    return 0;
}