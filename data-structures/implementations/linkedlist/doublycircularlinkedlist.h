#include <iostream>
using namespace std;

template <class T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    // constructor
    Node() : data(T()), next(nullptr), prev(nullptr) {}
    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

// ==========================================================

// ===== DOUBLY CIRCULAR LINKED LIST USING HEAD & TAIL =====

// ==========================================================

template <class T>
class DoublyCircularLinkedList {
public:
    Node<T>* head;
    Node<T>* tail;

    DoublyCircularLinkedList() : head(nullptr), tail(nullptr) {}
    ~DoublyCircularLinkedList() { while (!isEmpty()) deleteFromHead(); }

    bool isEmpty() { return head == nullptr && tail == nullptr; }

    int getSize() {
        if (isEmpty()) return 0;
        Node<T>* tempPtr = head;
        int count = 0;
        do {
            count++;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);
        return count;
    }

    bool search(T val) {
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return false; }

        Node<T>* tempPtr = head;
        do {
            if (tempPtr->data == val) return true;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);
        return false;
    }

    void display() {
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;
        int k = 0;
        do {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);
    }

    void displayReverse() {
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return; }

        Node<T>* tempPtr = tail;
        int k = 0;
        do {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->prev;
        }
        while (tempPtr != tail);
    }

    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        }
        else {
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            head = newNode;
        }
    }

    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
            tail = newNode;
        }
    }

    void insertAtPosition(T val, int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }

        int size = getSize();
        if (isEmpty() && index != 0) { cout << "List is empty. Can only insert at position 0." << endl; return; }
        if (index > size) { cout << "Index out of bounds." << endl; return; }

        Node<T>* newNode = new Node<T>(val);

        if (index == 0) {
            insertAtHead(val);
            cout << "Value inserted at position " << index << endl;
            return;
        }

        if (index == size) {
            insertAtTail(val);
            cout << "Value inserted at position " << index << endl;
            return;
        }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index - 1; i++) {
            tempPtr = tempPtr->next;
        }

        newNode->next = tempPtr->next;
        newNode->prev = tempPtr;
        tempPtr->next->prev = newNode;
        tempPtr->next = newNode;
        cout << "Value inserted at position " << index << endl;
    }

    void insertSorted(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
            cout << "Value " << val << " inserted at position 0." << endl;
            return;
        }

        if (val < head->data) {
            insertAtHead(val);
            cout << "Value " << val << " inserted at head." << endl;
            return;
        }

        Node<T>* tempPtr = head;
        do {
            if (tempPtr->next == head || tempPtr->next->data >= val) break;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != tail);

        newNode->next = tempPtr->next;
        newNode->prev = tempPtr;
        tempPtr->next->prev = newNode;
        tempPtr->next = newNode;

        if (newNode->next == head) {
            tail = newNode;
        }
        cout << "Value " << val << " inserted in sorted order." << endl;
    }

    void updateNode(int index, T newVal) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return; }

        int size = getSize();
        if (index >= size) { cout << "Index out of bounds." << endl; return; }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index; i++) {
            tempPtr = tempPtr->next;
        }

        T oldVal = tempPtr->data;
        tempPtr->data = newVal;
        cout << "Node at index " << index << " updated from " << oldVal << " to " << newVal << endl;
    }

    T deleteFromHead() {
        if (isEmpty()) { cout << "Doubly circular linked list is empty" << endl; return T(); }

        T returningVal = head->data;

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            head->next->prev = tail;
            tail->next = head->next;
            Node<T>* tempPtr = head;
            head = head->next;
            delete tempPtr;
        }

        return returningVal;
    }

    T deleteFromTail() {
        if (isEmpty()) { cout << "Doubly circular linked list is empty" << endl; return T(); }

        T returningVal = tail->data;

        if (head == tail) {
            delete tail;
            head = tail = nullptr;
        }
        else {
            tail->prev->next = head;
            head->prev = tail->prev;
            Node<T>* tempPtr = tail;
            tail = tail->prev;
            delete tempPtr;
        }

        return returningVal;
    }

    T deleteFromPosition(int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return T(); }
        if (isEmpty()) { cout << "List is empty." << endl; return T(); }

        int size = getSize();
        if (index >= size) { cout << "Index out of bounds." << endl; return T(); }

        if (index == 0) {
            return deleteFromHead();
        }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index; i++) {
            tempPtr = tempPtr->next;
        }

        T returningVal = tempPtr->data;

        if (tempPtr == tail) {
            return deleteFromTail();
        }

        tempPtr->prev->next = tempPtr->next;
        tempPtr->next->prev = tempPtr->prev;
        delete tempPtr;

        return returningVal;
    }

    void deleteValue(T val) {
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;

        do {
            if (tempPtr->data == val) {
                T deletedVal = tempPtr->data;

                if (tempPtr == head && tempPtr == tail) {
                    delete head;
                    head = tail = nullptr;
                }
                else if (tempPtr == head) {
                    head = head->next;
                    head->prev = tail;
                    tail->next = head;
                    delete tempPtr;
                }
                else if (tempPtr == tail) {
                    tail = tail->prev;
                    tail->next = head;
                    head->prev = tail;
                    delete tempPtr;
                }
                else {
                    tempPtr->prev->next = tempPtr->next;
                    tempPtr->next->prev = tempPtr->prev;
                    delete tempPtr;
                }

                cout << "Value " << deletedVal << " deleted from list." << endl;
                return;
            }
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);

        cout << "Value " << val << " not found in list." << endl;
    }
};

//---------------------------------------------------------------------

// ==========================================================

// ===== DOUBLY CIRCULAR LINKED LIST USING HEAD ONLY =====

// ==========================================================

template <class T>
class DoublyCircularLinkedListHeadOnly {
public:
    Node<T>* head;

    DoublyCircularLinkedListHeadOnly() : head(nullptr) {}
    ~DoublyCircularLinkedListHeadOnly() { while (!isEmpty()) deleteFromHead(); }

    bool isEmpty() { return head == nullptr; }

    Node<T>* getTail() {
        if (isEmpty()) return nullptr;
        return head->prev;
    }

    int getSize() {
        if (isEmpty()) return 0;
        Node<T>* tempPtr = head;
        int count = 0;
        do {
            count++;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);
        return count;
    }

    bool search(T val) {
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return false; }

        Node<T>* tempPtr = head;
        do {
            if (tempPtr->data == val) return true;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);
        return false;
    }

    void display() {
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;
        int k = 0;
        do {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);
    }

    void displayReverse() {
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return; }

        Node<T>* tail = getTail();
        Node<T>* tempPtr = tail;
        int k = 0;
        do {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->prev;
        }
        while (tempPtr != tail);
    }

    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        }
        else {
            Node<T>* tail = getTail();
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            head = newNode;
        }
    }

    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        }
        else {
            Node<T>* tail = getTail();
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
    }

    void insertAtPosition(T val, int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }

        int size = getSize();
        if (isEmpty() && index != 0) { cout << "List is empty. Can only insert at position 0." << endl; return; }
        if (index > size) { cout << "Index out of bounds." << endl; return; }

        Node<T>* newNode = new Node<T>(val);

        if (index == 0) {
            insertAtHead(val);
            cout << "Value inserted at position " << index << endl;
            return;
        }

        if (index == size) {
            insertAtTail(val);
            cout << "Value inserted at position " << index << endl;
            return;
        }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index - 1; i++) {
            tempPtr = tempPtr->next;
        }

        newNode->next = tempPtr->next;
        newNode->prev = tempPtr;
        tempPtr->next->prev = newNode;
        tempPtr->next = newNode;
        cout << "Value inserted at position " << index << endl;
    }

    void insertSorted(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
            cout << "Value " << val << " inserted at position 0." << endl;
            return;
        }

        if (val < head->data) {
            insertAtHead(val);
            cout << "Value " << val << " inserted at head." << endl;
            return;
        }

        Node<T>* tempPtr = head;
        Node<T>* tail = getTail();
        do {
            if (tempPtr->next == head || tempPtr->next->data >= val) break;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != tail);

        newNode->next = tempPtr->next;
        newNode->prev = tempPtr;
        tempPtr->next->prev = newNode;
        tempPtr->next = newNode;

        cout << "Value " << val << " inserted in sorted order." << endl;
    }

    void updateNode(int index, T newVal) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return; }

        int size = getSize();
        if (index >= size) { cout << "Index out of bounds." << endl; return; }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index; i++) {
            tempPtr = tempPtr->next;
        }

        T oldVal = tempPtr->data;
        tempPtr->data = newVal;
        cout << "Node at index " << index << " updated from " << oldVal << " to " << newVal << endl;
    }

    T deleteFromHead() {
        if (isEmpty()) { cout << "Doubly circular linked list is empty" << endl; return T(); }

        T returningVal = head->data;

        if (head->next == head) {
            delete head;
            head = nullptr;
        }
        else {
            Node<T>* tail = getTail();
            head->next->prev = tail;
            tail->next = head->next;
            Node<T>* tempPtr = head;
            head = head->next;
            delete tempPtr;
        }

        return returningVal;
    }

    T deleteFromTail() {
        if (isEmpty()) { cout << "Doubly circular linked list is empty" << endl; return T(); }

        Node<T>* tail = getTail();
        T returningVal = tail->data;

        if (head->next == head) {
            delete head;
            head = nullptr;
        }
        else {
            tail->prev->next = head;
            head->prev = tail->prev;
            delete tail;
        }

        return returningVal;
    }

    T deleteFromPosition(int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return T(); }
        if (isEmpty()) { cout << "List is empty." << endl; return T(); }

        int size = getSize();
        if (index >= size) { cout << "Index out of bounds." << endl; return T(); }

        if (index == 0) {
            return deleteFromHead();
        }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index; i++) {
            tempPtr = tempPtr->next;
        }

        T returningVal = tempPtr->data;

        if (tempPtr->next == head) {
            return deleteFromTail();
        }

        tempPtr->prev->next = tempPtr->next;
        tempPtr->next->prev = tempPtr->prev;
        delete tempPtr;

        return returningVal;
    }

    void deleteValue(T val) {
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;

        do {
            if (tempPtr->data == val) {
                T deletedVal = tempPtr->data;

                if (tempPtr->next == head && tempPtr->prev == head) {
                    delete head;
                    head = nullptr;
                }
                else if (tempPtr == head) {
                    head = head->next;
                    head->prev = tempPtr->prev;
                    tempPtr->prev->next = head;
                    delete tempPtr;
                }
                else {
                    tempPtr->prev->next = tempPtr->next;
                    tempPtr->next->prev = tempPtr->prev;
                    delete tempPtr;
                }

                cout << "Value " << deletedVal << " deleted from list." << endl;
                return;
            }
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);

        cout << "Value " << val << " not found in list." << endl;
    }
};

//---------------------------------------------------------------------

// ==========================================================

// ===== DOUBLY CIRCULAR LINKED LIST USING TAIL ONLY =====

// ==========================================================

template <class T>
class DoublyCircularLinkedListTailOnly {
public:
    Node<T>* tail;

    DoublyCircularLinkedListTailOnly() : tail(nullptr) {}
    ~DoublyCircularLinkedListTailOnly() { while (!isEmpty()) deleteFromHead(); }

    bool isEmpty() { return tail == nullptr; }

    Node<T>* getHead() {
        if (isEmpty()) return nullptr;
        return tail->next;
    }

    int getSize() {
        if (isEmpty()) return 0;
        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        int count = 0;
        do {
            count++;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);
        return count;
    }

    bool search(T val) {
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return false; }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        do {
            if (tempPtr->data == val) return true;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);
        return false;
    }

    void display() {
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return; }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        int k = 0;
        do {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);
    }

    void displayReverse() {
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return; }

        Node<T>* tempPtr = tail;
        int k = 0;
        do {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->prev;
        }
        while (tempPtr != tail);
    }

    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        }
        else {
            Node<T>* head = getHead();
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
        }
    }

    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        }
        else {
            Node<T>* head = getHead();
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
            tail = newNode;
        }
    }

    void insertAtPosition(T val, int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }

        int size = getSize();
        if (isEmpty() && index != 0) { cout << "List is empty. Can only insert at position 0." << endl; return; }
        if (index > size) { cout << "Index out of bounds." << endl; return; }

        Node<T>* newNode = new Node<T>(val);

        if (index == 0) {
            insertAtHead(val);
            cout << "Value inserted at position " << index << endl;
            return;
        }

        if (index == size) {
            insertAtTail(val);
            cout << "Value inserted at position " << index << endl;
            return;
        }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        for (int i = 0; i < index - 1; i++) {
            tempPtr = tempPtr->next;
        }

        newNode->next = tempPtr->next;
        newNode->prev = tempPtr;
        tempPtr->next->prev = newNode;
        tempPtr->next = newNode;
        cout << "Value inserted at position " << index << endl;
    }

    void insertSorted(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
            cout << "Value " << val << " inserted at position 0." << endl;
            return;
        }

        Node<T>* head = getHead();

        if (val < head->data) {
            insertAtHead(val);
            cout << "Value " << val << " inserted at head." << endl;
            return;
        }

        Node<T>* tempPtr = head;
        do {
            if (tempPtr->next == head || tempPtr->next->data >= val) break;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != tail);

        newNode->next = tempPtr->next;
        newNode->prev = tempPtr;
        tempPtr->next->prev = newNode;
        tempPtr->next = newNode;

        if (newNode->next == head) {
            tail = newNode;
        }
        cout << "Value " << val << " inserted in sorted order." << endl;
    }

    void updateNode(int index, T newVal) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return; }

        int size = getSize();
        if (index >= size) { cout << "Index out of bounds." << endl; return; }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        for (int i = 0; i < index; i++) {
            tempPtr = tempPtr->next;
        }

        T oldVal = tempPtr->data;
        tempPtr->data = newVal;
        cout << "Node at index " << index << " updated from " << oldVal << " to " << newVal << endl;
    }

    T deleteFromHead() {
        if (isEmpty()) { cout << "Doubly circular linked list is empty" << endl; return T(); }

        Node<T>* head = getHead();
        T returningVal = head->data;

        if (head->next == head) {
            delete head;
            tail = nullptr;
        }
        else {
            head->next->prev = tail;
            tail->next = head->next;
            delete head;
        }

        return returningVal;
    }

    T deleteFromTail() {
        if (isEmpty()) { cout << "Doubly circular linked list is empty" << endl; return T(); }

        T returningVal = tail->data;

        if (tail->next == tail) {
            delete tail;
            tail = nullptr;
        }
        else {
            tail->prev->next = tail->next;
            tail->next->prev = tail->prev;
            tail = tail->prev;
        }

        return returningVal;
    }

    T deleteFromPosition(int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return T(); }
        if (isEmpty()) { cout << "List is empty." << endl; return T(); }

        int size = getSize();
        if (index >= size) { cout << "Index out of bounds." << endl; return T(); }

        if (index == 0) {
            return deleteFromHead();
        }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        for (int i = 0; i < index; i++) {
            tempPtr = tempPtr->next;
        }

        T returningVal = tempPtr->data;

        if (tempPtr == tail) {
            return deleteFromTail();
        }

        tempPtr->prev->next = tempPtr->next;
        tempPtr->next->prev = tempPtr->prev;
        delete tempPtr;

        return returningVal;
    }

    void deleteValue(T val) {
        if (isEmpty()) { cout << "Doubly circular linked list is empty." << endl; return; }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;

        do {
            if (tempPtr->data == val) {
                T deletedVal = tempPtr->data;

                if (tempPtr->next == head && tempPtr->prev == head) {
                    delete head;
                    tail = nullptr;
                }
                else if (tempPtr == head) {
                    Node<T>* newHead = head->next;
                    newHead->prev = tail;
                    tail->next = newHead;
                    delete head;
                }
                else if (tempPtr == tail) {
                    tail = tail->prev;
                    tail->next = head;
                    head->prev = tail;
                    delete tempPtr;
                }
                else {
                    tempPtr->prev->next = tempPtr->next;
                    tempPtr->next->prev = tempPtr->prev;
                    delete tempPtr;
                }

                cout << "Value " << deletedVal << " deleted from list." << endl;
                return;
            }
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);

        cout << "Value " << val << " not found in list." << endl;
    }
};

//------------------------------------------------------------------------------------------------------------------