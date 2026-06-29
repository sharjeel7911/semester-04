#include <iostream>
using namespace std;

template <typename T>
void printSearchResult(int index, T key) {
    if (index != -1) cout << key << " found at index " << index << endl;
    else cout << key << " not found in array" << endl;
}

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
    // Test with an integer array (sorted) of size 5
    int intArray[5] = { 11, 12, 22, 25, 64 };
    int intKey = 22;
    int intIndex = binarySearch(intArray, 5, intKey);
    printSearchResult(intIndex, intKey);

    // Test with a float array (sorted) of size 4
    float floatArray[4] = { 0.57, 1.62, 2.71, 3.14 };
    float floatKey = 2.71;
    int floatIndex = binarySearch(floatArray, 4, floatKey);
    printSearchResult(floatIndex, floatKey);

    // Test with a string array (sorted) of size 4
    string stringArray[4] = { "apple", "banana", "grape", "orange" };
    string stringKey = "grape";
    int stringIndex = binarySearch(stringArray, 4, stringKey);
    printSearchResult(stringIndex, stringKey);

    return 0;
}