#include <iostream>
using namespace std;

template <class T>
void printSearchResult(int index, T key) {
    if (index != -1) cout << key << " found at index " << index << endl;
    else cout << key << " not found in array" << endl;
}

// linear search
template <class T>
int linearSearch(T arr[], int size, T key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) return i;
    }
    return -1;
}

// binary search
template <class T>
int binarySearch(T arr[], int size, T key) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}


int main() {

    int intArray[5] = { 11, 12, 22, 25, 64 };
    int intKey = 12;

    cout << "Linear Search" << endl;
    int intIndex = linearSearch(intArray, 5, intKey);
    printSearchResult(intIndex, intKey);

    cout << "Binary Search" << endl;
    int intI = binarySearch(intArray, 5, intKey);
    printSearchResult(intI, intKey);


    float floatArray[4] = { 0.57, 1.62, 2.71, 3.14 };
    float floatKey = 1.62;

    cout << "\nLinear Search" << endl;
    int floatIndex = linearSearch(floatArray, 4, floatKey);
    printSearchResult(floatIndex, floatKey);

    cout << "Binary Search" << endl;
    int floatI = binarySearch(floatArray, 4, floatKey);
    printSearchResult(floatI, floatKey);


    string stringArray[4] = { "apple", "banana", "grape", "orange" };
    string stringKey = "banana";

    cout << "\nLinear Search" << endl;
    int stringIndex = linearSearch(stringArray, 4, stringKey);
    printSearchResult(stringIndex, stringKey);

    cout << "Binary Search" << endl;
    int stringI = binarySearch(stringArray, 4, stringKey);
    printSearchResult(stringI, stringKey);

    return 0;
}