#include <iostream>
#include <stdexcept>
using namespace std;

// ===== PRIORITY QUEUE USING ARRAY =====

template <class T>
class MyPriorityQueue {
private:
    T* qu;
    int currSize;
    int maxSize;
public:
    MyPriorityQueue(int size) : currSize(0), maxSize(size) { qu = new T[size]; }
    ~MyPriorityQueue() { delete[] qu; }

    bool isFull() { return currSize == maxSize; }
    bool isEmpty() { return currSize == 0; }

    T peek() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }

        int maxIndex = 0;
        for (int i = 1; i < currSize; i++) {
            if (qu[i] > qu[maxIndex]) maxIndex = i;
        }
        return qu[maxIndex];
    }

    void enqueue(T val) {
        if (isFull()) { cout << "Queue is full\n"; return; }
        qu[currSize++] = val;
    }

    T dequeue() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }

        int maxIndex = 0;
        for (int i = 1; i < currSize; i++) {
            if (qu[i] > qu[maxIndex]) maxIndex = i;
        }

        T removedVal = qu[maxIndex];
        for (int i = maxIndex; i < currSize - 1; i++) qu[i] = qu[i + 1];

        currSize--;
        return removedVal;
    }

    void display() {
        cout << "Current Size: " << currSize << "\nMax Size: " << maxSize << endl;
        if (isEmpty()) { cout << "Queue is empty\n"; return; }
        for (int i = 0; i < currSize; i++) cout << i << ". " << qu[i] << endl;
    }

    //--------------------------------------------------------------------------

    /* FOR SORTED QUEUE
    T peek() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }
        return qu[0];
    }

    void enqueue(T val) { // for max priority
        if (isFull()) { cout << "Queue is full\n"; return; }

        int i = currSize - 1;
        while (i >= 0 && qu[i] < val) { // qu[i] > val [for min priority in queue]
            qu[i + 1] = qu[i];
            i--;
        }

        qu[i + 1] = val;
        currSize++;
    }

    T dequeue() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }

        T removedVal = qu[0];
        for (int i = 0; i < currSize - 1; i++) qu[i] = qu[i + 1];

        currSize--;
        return removedVal;
    }
    */
};

// ---------------------------------------------------------------------------------------

// ===== PRIORITY QUEUE USING LINKED LIST =====

template <class T>
class Node {
public:
    T data;
    Node* next;

    Node() : data(T()), next(nullptr) {}
    Node(T val) : data(val), next(nullptr) {}
};

template <class T>
class MyPriorityQueueLL {
private:
    Node<T>* front;
public:
    MyPriorityQueueLL() { front = nullptr; }
    ~MyPriorityQueueLL() { while (!isEmpty()) dequeue(); }

    bool isEmpty() { return front == nullptr; }

    T peek() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }
        return front->data;
    }

    void enqueue(T val) {
        // insert in sorted order
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty() || front->data < val) {
            newNode->next = front;
            front = newNode;
            return;
        }

        Node<T>* temp = front;

        while (temp->next != nullptr && temp->next->data >= val) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    T dequeue() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }

        Node<T>* temp = front;
        T val = front->data;
        front = front->next;

        delete temp;
        return val;
    }

    void display() {
        if (isEmpty()) { cout << "Queue is empty\n"; return; }

        Node<T>* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

//--------------------------------------------------------------------------


// ===== PRIORITY QUEUE USING HEAP =====

template <class T>
class MyPriorityQueueH {
private:
    T* qu;
    int currSize;
    int maxSize;

    // helper formulas for heap indexing
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return (2 * i) + 1; }
    int rightChild(int i) { return (2 * i) + 2; }

    // bubbles up the last element to restore max-heap property
    void heapifyUp(int i) {
        while (i > 0 && qu[parent(i)] < qu[i]) {
            swap(qu[parent(i)], qu[i]);
            i = parent(i);
        }
    }

    // bubbles down the root element to restore max-heap property
    void heapifyDown(int i) {
        int maxIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < currSize && qu[left] > qu[maxIndex]) {
            maxIndex = left;
        }
        if (right < currSize && qu[right] > qu[maxIndex]) {
            maxIndex = right;
        }

        if (i != maxIndex) {
            swap(qu[i], qu[maxIndex]);
            heapifyDown(maxIndex);
        }
    }

public:
    MyPriorityQueueH(int size) : currSize(0), maxSize(size) { qu = new T[size]; }
    ~MyPriorityQueueH() { delete[] qu; }

    bool isFull() { return currSize == maxSize; }
    bool isEmpty() { return currSize == 0; }

    T peek() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return T();
        }
        return qu[0];
    }

    // O(log n) time - insert at the end and bubble up
    void enqueue(T val) {
        if (isFull()) {
            cout << "Queue is full\n";
            return;
        }
        qu[currSize] = val;
        currSize++;
        heapifyUp(currSize - 1);
    }

    // O(log n) time - swap root with last element, remove, and bubble down
    T dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return T();
        }

        T removedVal = qu[0];      // target highest priority element
        qu[0] = qu[currSize - 1];  // move last element to root
        currSize--;

        if (currSize > 0) {
            heapifyDown(0);        // restore heap rules
        }

        return removedVal;
    }

    void display() {
        cout << "Current Size: " << currSize << "\nMax Size: " << maxSize << endl;
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        for (int i = 0; i < currSize; i++) {
            cout << i << ". " << qu[i] << endl;
        }
    }

    void printTree(int index, string padding, string edge, bool hasLeftSibling) {
        if (index >= currSize) return;

        cout << "\n" << padding << edge << qu[index];

        string newPadding = padding + (hasLeftSibling ? "|    " : "     ");

        int right = 2 * index + 2;
        int left = 2 * index + 1;

        printTree(right, newPadding, "|----", left < currSize);
        printTree(left, newPadding, "|____", false);
    }

    void visualize() {
        if (currSize == 0) {
            cout << "Empty Heap\n";
            return;
        }
        cout << qu[0];

        printTree(2, "", "|----", currSize > 1);
        printTree(1, "", "|____", false);
        cout << endl;
    }
};

// ---------------------------------------------------------------------------------------

int main() {
    MyPriorityQueueH<int> pq(10);

    cout << "--- Enqueueing Elements ---\n";
    pq.enqueue(10);
    pq.enqueue(30);
    pq.enqueue(20);
    pq.enqueue(5);
    pq.enqueue(15);
    pq.visualize();
    pq.display();

    cout << "\n--- Dequeueing Elements (By Highest Priority) ---\n";
    cout << "Dequeued: " << pq.dequeue() << " (Expected 30)\n";
    cout << "Dequeued: " << pq.dequeue() << " (Expected 20)\n";
    cout << "Dequeued: " << pq.dequeue() << " (Expected 15)\n";
    cout << "Dequeued: " << pq.dequeue() << " (Expected 10)\n";
    cout << "Dequeued: " << pq.dequeue() << " (Expected 5)\n";

    cout << "Peek next: " << pq.peek() << " (Expected 15)\n";
    return 0;
}