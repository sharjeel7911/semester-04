#include <iostream>
using namespace std;

// recursive approach
void heapify(int arr[], int n, int i) {
	int maxIndex = i;
	int left = (2 * i) + 1;
	int right = (2 * i) + 2;

	if (left < n && arr[left] > arr[maxIndex]) {
		maxIndex = left;
	}
	if (right < n && arr[right] > arr[maxIndex]) {
		maxIndex = right;
	}
	if (maxIndex != i) {
		swap(arr[i], arr[maxIndex]);
		heapify(arr, n, maxIndex);
	}
}

void heapSort(int arr[], int n) {
	// build max heap in place
	for (int i = (n / 2) - 1; i >= 0; i--) {
		heapify(arr, n, i);
	}
	// ascending order
	for (int i = n - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

int main() {
	int arr[] = {4, 10, 3, 5, 1};
	int n = sizeof(arr) / sizeof(arr[0]);

	heapSort(arr, n);
	cout << "Sorted Array: ";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	return 0;
}

/*
// iterative approach
void heapify(int arr[], int n, int i) {
    while (true) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        // If the largest is not the root, swap and continue down the tree
        if (largest != i) {
            swap(arr[i], arr[largest]);
            i = largest; // Move index down to the swapped child loop
        } else {
            break; // Heap property is satisfied
        }
    }
}
*/