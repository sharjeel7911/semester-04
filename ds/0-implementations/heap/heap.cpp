#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

// ==========================================
// 1. MAX-HEAP IMPLEMENTATION (Raw Array)
// ==========================================
class MaxHeap {
private:
    int* arr;         // Pointer to dynamically allocated raw array
    int capacity;     // Total capacity of the array
    int size;         // Current number of elements in the heap

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return (2 * i) + 1; }
    int rightChild(int i) { return (2 * i) + 2; }

    void resize() {
        capacity *= 2;
        int* newArr = new int[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr; // Free old memory
        arr = newArr;  // Point to new memory
    }

    void heapifyUp(int i) {
        while (i > 0 && arr[parent(i)] < arr[i]) {
            swap(arr[parent(i)], arr[i]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int maxIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < size && arr[left] > arr[maxIndex]) maxIndex = left;
        if (right < size && arr[right] > arr[maxIndex]) maxIndex = right;

        if (i != maxIndex) {
            swap(arr[i], arr[maxIndex]);
            heapifyDown(maxIndex);
        }
    }

public:
    MaxHeap(int initialCapacity = 4) {
        capacity = initialCapacity;
        size = 0;
        arr = new int[capacity];
    }

    ~MaxHeap() {
        delete[] arr;
    }

    void insert(int key) {
        if (size == capacity) {
            resize();
        }
        arr[size] = key;
        size++;
        heapifyUp(size - 1);
    }

    int extractMax() {
        if (size <= 0) throw  underflow_error("Heap Underflow");

        int maxVal = arr[0];
        arr[0] = arr[size - 1];
        size--;

        if (size > 0) heapifyDown(0);
        return maxVal;
    }

    void print() {
        for (int i = 0; i < size; i++)  cout << arr[i] << " ";
        cout << "\n";
    }
};

// ==========================================
// 2. MIN-HEAP IMPLEMENTATION (Raw Array)
// ==========================================
class MinHeap {
private:
    int* arr;
    int capacity;
    int size;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return (2 * i) + 1; }
    int rightChild(int i) { return (2 * i) + 2; }

    void resize() {
        capacity *= 2;
        int* newArr = new int[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

    void heapifyUp(int i) {
        // Notice the sign difference: bubble up if parent is GREATER than child
        while (i > 0 && arr[parent(i)] > arr[i]) {
            swap(arr[parent(i)], arr[i]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int minIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);

        // Notice the sign difference: looking for the smallest element
        if (left < size && arr[left] < arr[minIndex]) minIndex = left;
        if (right < size && arr[right] < arr[minIndex]) minIndex = right;

        if (i != minIndex) {
            swap(arr[i], arr[minIndex]);
            heapifyDown(minIndex);
        }
    }

public:
    MinHeap(int initialCapacity = 4) {
        capacity = initialCapacity;
        size = 0;
        arr = new int[capacity];
    }

    ~MinHeap() {
        delete[] arr;
    }

    void insert(int key) {
        if (size == capacity) {
            resize();
        }
        arr[size] = key;
        size++;
        heapifyUp(size - 1);
    }

    int extractMin() {
        if (size <= 0) throw  underflow_error("Heap Underflow");

        int minVal = arr[0];
        arr[0] = arr[size - 1];
        size--;

        if (size > 0) heapifyDown(0);
        return minVal;
    }

    void print() {
        for (int i = 0; i < size; i++)  cout << arr[i] << " ";
        cout << "\n";
    }
};

// ==========================================
// MAIN DRIVER
// ==========================================
int main() {
    // Test Data
    int elements[] = { 15, 30, 5, 10, 20 };

    cout << "--- TESTING MAX-HEAP ---\n";
    MaxHeap maxH;
    for (int x : elements) maxH.insert(x);

    cout << "Max-Heap structure (Array layout): ";
    maxH.print(); // Root should be 30
    cout << "Extracted Max: " << maxH.extractMax() << " (Expected 30)\n";
    cout << "Extracted Max: " << maxH.extractMax() << " (Expected 20)\n\n";

    cout << "--- TESTING MIN-HEAP ---\n";
    MinHeap minH;
    for (int x : elements) minH.insert(x);

    cout << "Min-Heap structure (Array layout): ";
    minH.print(); // Root should be 5
    cout << "Extracted Min: " << minH.extractMin() << " (Expected 5)\n";
    cout << "Extracted Min: " << minH.extractMin() << " (Expected 10)\n";

    return 0;
}