#include <iostream>
using namespace std;

// ===== CIRCULAR QUEUE USING ARRAY =====

template <class T>
class MyCircularQueue {
private:
    T* qu;
    int front;
    int rear;
    int currSize;  // currSize = rear - front; 
    int maxSize;
public:
    MyCircularQueue(int size) : front(0), rear(0), currSize(0), maxSize(size) { qu = new T[size]; }
    ~MyCircularQueue() { delete[] qu; }

    int getFront() { return front; }
    int getRear() { return rear; }
    bool isFull() { return currSize == maxSize; }
    bool isEmpty() { return currSize == 0; }

    T peek() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }
        return qu[front];
    }

    void enqueue(T val) {
        if (isFull()) { cout << "Queue is full\n"; return; }

        qu[rear] = val;
        rear = (rear + 1) % maxSize;
        currSize++;
    }

    T dequeue() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }

        T removedVal = qu[front];
        front = (front + 1) % maxSize;
        currSize--;
        return removedVal;
    }

    void display() {
        cout << "Current Size: " << currSize << "\nMax Size: " << maxSize << "\nFront: " << front << "\nRear: " << rear << endl;
        if (isEmpty()) { cout << "Queue is empty\n"; return; }

        for (int i = 0; i < currSize; i++) {
            int index = (front + i) % maxSize;
            cout << index << ". " << qu[index] << endl;
        }
    }
};

// ---------------------------------------------------------------------------------------

// ===== CIRCULAR QUEUE USING LINKED LIST =====

template <class T>
class Node {
public:
    T data;
    Node* next;

    Node() : data(T()), next(nullptr) {}
    Node(T val) : data(val), next(nullptr) {}
};

template <class T>
class MyCircularQueueLL {
private:
    Node<T>* front;
    Node<T>* rear;

public:
    MyCircularQueueLL() { front = rear = nullptr; }
    ~MyCircularQueueLL() { while (!isEmpty()) dequeue(); }

    bool isEmpty() { return front == nullptr; }

    T peek() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }
        return front->data;
    }


    void enqueue(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            front = rear = newNode;
            rear->next = front;   // circular link
        }
        else {
            rear->next = newNode;
            rear = newNode;
            rear->next = front;   // maintain circle
        }
    }

    T dequeue() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }

        Node<T>* temp = front;
        T val = front->data;

        // if only one node
        if (front == rear) {
            front = rear = nullptr;
        }
        else {
            front = front->next;
            rear->next = front;
        }

        delete temp;
        return val;
    }

    void display() {
        if (isEmpty()) { cout << "Queue is empty\n"; return; }

        Node<T>* temp = front;
        do {
            cout << temp->data << " ";
            temp = temp->next;
        }
        while (temp != front);
        cout << endl;
    }
};