#include <iostream>
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
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }
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