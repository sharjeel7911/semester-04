#include <iostream>
using namespace std;

template <class T>
class MyArray {
private:
    T* arr;
    int currSize;
    int maxSize;
public:
    MyArray(int size) : currSize(0), maxSize(size) { arr = new T[size]; }
    ~MyArray() { delete[] arr; }

    bool isFull() { return currSize == maxSize; }
    bool isEmpty() { return currSize == 0; }

    void addVal(T val) {
        if (isFull()) { cout << "Array is full\n"; return; }
        arr[currSize++] = val;
    }

    T removeVal() {
        if (isEmpty()) { cout << "Array is empty\n"; return T(); }
        return arr[--currSize];
    }

    void addValAtIndex(int index, T val) {
        if (isFull()) { cout << "Array is full\n"; return; }
        else if (index < 0 || index > currSize) { cout << "Invalid index\n"; return; }
        else {
            for (int i = currSize; i > index; i--) arr[i] = arr[i - 1];
            arr[index] = val;
            currSize++;
        }
    }

    T removeValFromIndex(int index) {
        if (isEmpty()) { cout << "Array is empty\n"; return T(); }
        else if (index < 0 || index >= currSize) { cout << "Invalid index\n"; return T(); }
        else {
            T removedVal = arr[index];
            for (int i = index; i < currSize - 1; i++) arr[i] = arr[i + 1];
            currSize--;
            return removedVal;
        }
    }

    void display() {
        cout << "Current Size: " << currSize << "\nMax Size: " << maxSize << endl;
        if (isEmpty()) { cout << "Array is empty\n"; return; }
        for (int i = 0; i < currSize; i++) cout << i << ". " << arr[i] << endl;
    }
};