#include <algorithm>
#include <iostream>
#include <stdexcept>
using namespace std;

// ==========================================
// 1. MAX-HEAP IMPLEMENTATION (Raw Array)
// ==========================================
class MaxHeap {
 private:
	int* arr;
	int capacity;
	int size;  // current number of elements in the heap

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
		while (i > 0 && arr[parent(i)] < arr[i]) {
			swap(arr[parent(i)], arr[i]);
			i = parent(i);
		}
	}

	void heapifyDown(int i) {
		int maxIndex = i;
		int left = leftChild(i);
		int right = rightChild(i);

		if (left < size && arr[left] > arr[maxIndex]) {
			maxIndex = left;
		}
		if (right < size && arr[right] > arr[maxIndex]) {
			maxIndex = right;
		}
		if (i != maxIndex) {
			swap(arr[i], arr[maxIndex]);
			heapifyDown(maxIndex);
		}
	}

	void printTree(int index, string padding, string edge, bool hasLeftSibling) {
		if (index >= size) return;

		cout << "\n" << padding << edge << arr[index];

		string newPadding = padding + (hasLeftSibling ? "|    " : "     ");

		int right = 2 * index + 2;
		int left = 2 * index + 1;

		printTree(right, newPadding, "|----", left < size);
		printTree(left, newPadding, "|____", false);
	}

 public:
	MaxHeap(int initialCapacity = 4) {
		capacity = initialCapacity;
		size = 0;
		arr = new int[capacity];
	}

	~MaxHeap() { delete[] arr; }

	void insertVal(int key) {
		if (size == capacity) {
			resize();
		}
		arr[size] = key;
		size++;
		heapifyUp(size - 1);
	}

	int deleteVal() {
		if (size <= 0) {
			throw underflow_error("Heap Underflow");
		}

		int maxVal = arr[0];
		arr[0] = arr[size - 1];
		size--;

		if (size > 0) heapifyDown(0);
		return maxVal;
	}

	void heapSort(int arr[], int n) {
		MaxHeap h(n);

		// Step 1: Insert all elements into the Max-Heap
		for (int i = 0; i < n; i++) {
			h.insertVal(arr[i]);
		}

		// Step 2: Extract the maximum element one by one and place it at the end of the array to sort it in ascending order
		for (int i = n - 1; i >= 0; i--) {
			arr[i] = h.deleteVal();
		}
	}

	void print() {
		for (int i = 0; i < size; i++) cout << arr[i] << " ";
		cout << "\n";
	}

	void visualize() {
		if (size == 0) {
			cout << "Empty Heap\n";
			return;
		}

		cout << arr[0];
		printTree(2, "", "|----", size > 1);
		printTree(1, "", "|____", false);
		cout << endl;
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

	void printTree(int index, string padding, string edge, bool hasLeftSibling) {
		if (index >= size) return;

		cout << "\n" << padding << edge << arr[index];

		string newPadding = padding + (hasLeftSibling ? "|    " : "     ");

		int right = 2 * index + 2;
		int left = 2 * index + 1;

		printTree(right, newPadding, "|----", left < size);
		printTree(left, newPadding, "|____", false);
	}

 public:
	MinHeap(int initialCapacity = 4) {
		capacity = initialCapacity;
		size = 0;
		arr = new int[capacity];
	}

	~MinHeap() { delete[] arr; }

	void insertVal(int key) {
		if (size == capacity) {
			resize();
		}
		arr[size] = key;
		size++;
		heapifyUp(size - 1);
	}

	int deleteVal() {
		if (size <= 0) throw underflow_error("Heap Underflow");

		int minVal = arr[0];
		arr[0] = arr[size - 1];
		size--;

		if (size > 0) heapifyDown(0);
		return minVal;
	}

	void heapSort(int arr[], int n) {
		MinHeap h(n);

		// Step 1: Insert all elements into the Max-Heap
		for (int i = 0; i < n; i++) {
			h.insertVal(arr[i]);
		}

		// Step 2: Extract the maximum element one by one and place it at the end of the array to sort it in descending order
		for (int i = n - 1; i >= 0; i--) {
			arr[i] = h.deleteVal();
		}
	}

	void print() {
		for (int i = 0; i < size; i++) cout << arr[i] << " ";
		cout << "\n";
	}

	void visualize() {
		if (size == 0) {
			cout << "Empty Heap\n";
			return;
		}

		cout << arr[0];
		printTree(2, "", "|----", size > 1);
		printTree(1, "", "|____", false);
		cout << endl;
	}
};

// ==========================================
// MAIN DRIVER
// ==========================================
int main() {
	// Test Data
	int elements[] = {15, 30, 5, 10, 20};

	cout << "--- TESTING MAX-HEAP ---\n";
	MaxHeap maxH;
	for (int x : elements) maxH.insertVal(x);
	maxH.visualize();

	cout << "Max-Heap structure (Array layout): ";
	maxH.print();  // Root should be 30
	cout << "Extracted Max: " << maxH.deleteVal() << " (Expected 30)\n";
	cout << "Extracted Max: " << maxH.deleteVal() << " (Expected 20)\n\n";

	cout << "--- TESTING MIN-HEAP ---\n";
	MinHeap minH;
	for (int x : elements) minH.insertVal(x);
	minH.visualize();
	cout << "Min-Heap structure (Array layout): ";
	minH.print();  // Root should be 5
	cout << "Extracted Min: " << minH.deleteVal() << " (Expected 5)\n";
	cout << "Extracted Min: " << minH.deleteVal() << " (Expected 10)\n";
	return 0;
}
