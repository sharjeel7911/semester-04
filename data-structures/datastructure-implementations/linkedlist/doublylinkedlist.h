#include <iostream>
using namespace std;

template <class T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;

    // constructor
    Node() : data(T()), prev(nullptr), next(nullptr) {}
    Node(T val) : data(val), prev(nullptr), next(nullptr) {}
};

// =====================================================

// ===== DOUBLY LINKED LIST USING HEAD & TAIL =====

// =====================================================

template <class T>
class DoublyLinkedList {
public:
    Node<T>* head;
    Node<T>* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    ~DoublyLinkedList() { while (!isEmpty()) deleteFromHead(); }

    bool isEmpty() { return head == nullptr && tail == nullptr; }

    bool search(T val) {
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return false; }

        Node<T>* tempPtr = head;
        while (tempPtr != nullptr) {
            if (tempPtr->data == val) return true;
            tempPtr = tempPtr->next;
        }
        return false;
    }

    void display() {
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;
        int k = 0;
        while (tempPtr != nullptr) {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->next;
        }
    }

    void displayReverse() {
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return; }

        Node<T>* tempPtr = tail;
        int k = 0;
        while (tempPtr != nullptr) {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->prev;
        }
    }

    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void insertAtPosition(T val, int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty() && index != 0) { cout << "List is empty. Can only insert at position 0." << endl; return; }

        Node<T>* newNode = new Node<T>(val);

        if (index == 0) {
            if (isEmpty()) {
                head = tail = newNode;
            }
            else {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            cout << "Value inserted at position " << index << endl;
            return;
        }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index - 1 && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        if (tempPtr == nullptr) {
            cout << "Index out of bounds." << endl;
            delete newNode;
            return;
        }

        newNode->next = tempPtr->next;
        newNode->prev = tempPtr;

        if (tempPtr->next != nullptr) {
            tempPtr->next->prev = newNode;
        }
        tempPtr->next = newNode;

        if (newNode->next == nullptr) {
            tail = newNode;
        }
        cout << "Value inserted at position " << index << endl;
    }

    void insertSorted(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = tail = newNode;
            cout << "Value " << val << " inserted at position 0." << endl;
            return;
        }

        if (val < head->data) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            cout << "Value " << val << " inserted at head." << endl;
            return;
        }

        Node<T>* tempPtr = head;
        while (tempPtr->next != nullptr && tempPtr->next->data < val) {
            tempPtr = tempPtr->next;
        }

        newNode->next = tempPtr->next;
        newNode->prev = tempPtr;

        if (tempPtr->next != nullptr) {
            tempPtr->next->prev = newNode;
        }
        tempPtr->next = newNode;

        if (newNode->next == nullptr) {
            tail = newNode;
        }
        cout << "Value " << val << " inserted in sorted order." << endl;
    }

    void updateNode(int index, T newVal) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        if (tempPtr == nullptr) { cout << "Index out of bounds." << endl; return; }

        T oldVal = tempPtr->data;
        tempPtr->data = newVal;
        cout << "Node at index " << index << " updated from " << oldVal << " to " << newVal << endl;
    }

    T deleteFromHead() {
        if (isEmpty()) { cout << "List is empty." << endl; return T(); }

        T returningVal = head->data;

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node<T>* tempPtr = head;
            head = head->next;
            head->prev = nullptr;
            delete tempPtr;
        }

        return returningVal;
    }

    T deleteFromTail() {
        if (isEmpty()) { cout << "Doubly linked list is empty" << endl; return T(); }

        T returningVal = tail->data;

        if (head == tail) {
            delete tail;
            head = tail = nullptr;
        }
        else {
            Node<T>* tempPtr = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete tempPtr;
        }

        return returningVal;
    }

    T deleteFromPosition(int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return T(); }
        if (isEmpty()) { cout << "List is empty." << endl; return T(); }

        if (index == 0) {
            return deleteFromHead();
        }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        if (tempPtr == nullptr) {
            cout << "Index out of bounds." << endl;
            return T();
        }

        T returningVal = tempPtr->data;

        if (tempPtr == tail) {
            tail = tempPtr->prev;
            tail->next = nullptr;
        }
        else {
            tempPtr->prev->next = tempPtr->next;
            tempPtr->next->prev = tempPtr->prev;
        }

        delete tempPtr;
        return returningVal;
    }

    void deleteValue(T val) {
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;

        while (tempPtr != nullptr) {
            if (tempPtr->data == val) {
                T deletedVal = tempPtr->data;

                if (tempPtr == head && tempPtr == tail) {
                    delete head;
                    head = tail = nullptr;
                }
                else if (tempPtr == head) {
                    head = head->next;
                    head->prev = nullptr;
                    delete tempPtr;
                }
                else if (tempPtr == tail) {
                    tail = tail->prev;
                    tail->next = nullptr;
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

        cout << "Value " << val << " not found in list." << endl;
    }
};

//--------------------------------------------------------------------------------

// =====================================================

// ===== DOUBLY LINKED LIST USING HEAD ONLY =====

// =====================================================

template <class T>
class DoublyLinkedListHeadOnly {
public:
    Node<T>* head;

    DoublyLinkedListHeadOnly() : head(nullptr) {}
    ~DoublyLinkedListHeadOnly() { while (!isEmpty()) deleteFromHead(); }

    bool isEmpty() { return head == nullptr; }

    bool search(T val) {
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return false; }

        Node<T>* tempPtr = head;
        while (tempPtr != nullptr) {
            if (tempPtr->data == val) return true;
            tempPtr = tempPtr->next;
        }
        return false;
    }

    void display() {
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;
        int k = 0;
        while (tempPtr != nullptr) {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->next;
        }
    }

    void displayReverse() {
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;
        while (tempPtr->next != nullptr) {
            tempPtr = tempPtr->next;
        }

        int k = 0;
        while (tempPtr != nullptr) {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->prev;
        }
    }

    Node<T>* getTail() {
        if (isEmpty()) return nullptr;
        Node<T>* tempPtr = head;
        while (tempPtr->next != nullptr) {
            tempPtr = tempPtr->next;
        }
        return tempPtr;
    }

    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = newNode;
        }
        else {
            Node<T>* tempPtr = getTail();
            tempPtr->next = newNode;
            newNode->prev = tempPtr;
        }
    }

    void insertAtPosition(T val, int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty() && index != 0) { cout << "List is empty. Can only insert at position 0." << endl; return; }

        Node<T>* newNode = new Node<T>(val);

        if (index == 0) {
            if (isEmpty()) {
                head = newNode;
            }
            else {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            cout << "Value inserted at position " << index << endl;
            return;
        }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index - 1 && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        if (tempPtr == nullptr) {
            cout << "Index out of bounds." << endl;
            delete newNode;
            return;
        }

        newNode->next = tempPtr->next;
        newNode->prev = tempPtr;

        if (tempPtr->next != nullptr) {
            tempPtr->next->prev = newNode;
        }
        tempPtr->next = newNode;
        cout << "Value inserted at position " << index << endl;
    }

    void insertSorted(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = newNode;
            cout << "Value " << val << " inserted at position 0." << endl;
            return;
        }

        if (val < head->data) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            cout << "Value " << val << " inserted at head." << endl;
            return;
        }

        Node<T>* tempPtr = head;
        while (tempPtr->next != nullptr && tempPtr->next->data < val) {
            tempPtr = tempPtr->next;
        }

        newNode->next = tempPtr->next;
        newNode->prev = tempPtr;

        if (tempPtr->next != nullptr) {
            tempPtr->next->prev = newNode;
        }
        tempPtr->next = newNode;
        cout << "Value " << val << " inserted in sorted order." << endl;
    }

    void updateNode(int index, T newVal) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        if (tempPtr == nullptr) { cout << "Index out of bounds." << endl; return; }

        T oldVal = tempPtr->data;
        tempPtr->data = newVal;
        cout << "Node at index " << index << " updated from " << oldVal << " to " << newVal << endl;
    }

    T deleteFromHead() {
        if (isEmpty()) { cout << "Doubly linked list is empty" << endl; return T(); }

        T returningVal = head->data;

        if (head->next == nullptr) {
            delete head;
            head = nullptr;
        }
        else {
            Node<T>* tempPtr = head;
            head = head->next;
            head->prev = nullptr;
            delete tempPtr;
        }

        return returningVal;
    }

    T deleteFromTail() {
        if (isEmpty()) { cout << "Doubly linked list is empty" << endl; return T(); }

        Node<T>* tail = getTail();
        T returningVal = tail->data;

        if (tail->prev == nullptr) {
            delete head;
            head = nullptr;
        }
        else {
            tail->prev->next = nullptr;
            delete tail;
        }

        return returningVal;
    }

    T deleteFromPosition(int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return T(); }
        if (isEmpty()) { cout << "List is empty." << endl; return T(); }

        if (index == 0) {
            return deleteFromHead();
        }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        if (tempPtr == nullptr) {
            cout << "Index out of bounds." << endl;
            return T();
        }

        T returningVal = tempPtr->data;

        if (tempPtr->next == nullptr) {
            tempPtr->prev->next = nullptr;
        }
        else {
            tempPtr->prev->next = tempPtr->next;
            tempPtr->next->prev = tempPtr->prev;
        }

        delete tempPtr;
        return returningVal;
    }

    void deleteValue(T val) {
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;

        while (tempPtr != nullptr) {
            if (tempPtr->data == val) {
                T deletedVal = tempPtr->data;

                if (tempPtr == head) {
                    if (tempPtr->next == nullptr) {
                        delete head;
                        head = nullptr;
                    }
                    else {
                        head = head->next;
                        head->prev = nullptr;
                        delete tempPtr;
                    }
                }
                else {
                    if (tempPtr->next == nullptr) {
                        tempPtr->prev->next = nullptr;
                    }
                    else {
                        tempPtr->prev->next = tempPtr->next;
                        tempPtr->next->prev = tempPtr->prev;
                    }
                    delete tempPtr;
                }

                cout << "Value " << deletedVal << " deleted from list." << endl;
                return;
            }
            tempPtr = tempPtr->next;
        }

        cout << "Value " << val << " not found in list." << endl;
    }
};

//--------------------------------------------------------------------------------

// =====================================================

// ===== DOUBLY LINKED LIST USING TAIL ONLY =====

// =====================================================

template <class T>
class DoublyLinkedListTailOnly {
public:
    Node<T>* tail;

    DoublyLinkedListTailOnly() : tail(nullptr) {}
    ~DoublyLinkedListTailOnly() { while (!isEmpty()) deleteFromHead(); }

    bool isEmpty() { return tail == nullptr; }

    Node<T>* getHead() {
        if (isEmpty()) return nullptr;
        Node<T>* tempPtr = tail;
        while (tempPtr->prev != nullptr) {
            tempPtr = tempPtr->prev;
        }
        return tempPtr;
    }

    bool search(T val) {
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return false; }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        while (tempPtr != nullptr) {
            if (tempPtr->data == val) return true;
            tempPtr = tempPtr->next;
        }
        return false;
    }

    void display() {
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return; }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        int k = 0;
        while (tempPtr != nullptr) {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->next;
        }
    }

    void displayReverse() {
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return; }

        Node<T>* tempPtr = tail;
        int k = 0;
        while (tempPtr != nullptr) {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->prev;
        }
    }

    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            tail = newNode;
        }
        else {
            Node<T>* head = getHead();
            newNode->next = head;
            head->prev = newNode;
        }
    }

    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void insertAtPosition(T val, int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }

        Node<T>* head = getHead();
        if (isEmpty() && index != 0) { cout << "List is empty. Can only insert at position 0." << endl; return; }

        Node<T>* newNode = new Node<T>(val);

        if (index == 0) {
            if (isEmpty()) {
                tail = newNode;
            }
            else {
                newNode->next = head;
                head->prev = newNode;
            }
            cout << "Value inserted at position " << index << endl;
            return;
        }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index - 1 && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        if (tempPtr == nullptr) {
            cout << "Index out of bounds." << endl;
            delete newNode;
            return;
        }

        newNode->next = tempPtr->next;
        newNode->prev = tempPtr;

        if (tempPtr->next != nullptr) {
            tempPtr->next->prev = newNode;
        }
        else {
            tail = newNode;
        }
        tempPtr->next = newNode;
        cout << "Value inserted at position " << index << endl;
    }

    void insertSorted(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            tail = newNode;
            cout << "Value " << val << " inserted at position 0." << endl;
            return;
        }

        Node<T>* head = getHead();

        if (val < head->data) {
            newNode->next = head;
            head->prev = newNode;
            cout << "Value " << val << " inserted at head." << endl;
            return;
        }

        Node<T>* tempPtr = head;
        while (tempPtr->next != nullptr && tempPtr->next->data < val) {
            tempPtr = tempPtr->next;
        }

        newNode->next = tempPtr->next;
        newNode->prev = tempPtr;

        if (tempPtr->next != nullptr) {
            tempPtr->next->prev = newNode;
        }
        else {
            tail = newNode;
        }
        tempPtr->next = newNode;
        cout << "Value " << val << " inserted in sorted order." << endl;
    }

    void updateNode(int index, T newVal) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return; }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        for (int i = 0; i < index && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        if (tempPtr == nullptr) { cout << "Index out of bounds." << endl; return; }

        T oldVal = tempPtr->data;
        tempPtr->data = newVal;
        cout << "Node at index " << index << " updated from " << oldVal << " to " << newVal << endl;
    }

    T deleteFromHead() {
        if (isEmpty()) { cout << "Doubly linked list is empty" << endl; return T(); }

        Node<T>* head = getHead();
        T returningVal = head->data;

        if (head == tail) {
            delete head;
            tail = nullptr;
        }
        else {
            head->next->prev = nullptr;
            delete head;
        }

        return returningVal;
    }

    T deleteFromTail() {
        if (isEmpty()) { cout << "Doubly linked list is empty" << endl; return T(); }

        T returningVal = tail->data;

        if (tail->prev == nullptr) {
            delete tail;
            tail = nullptr;
        }
        else {
            tail = tail->prev;
            tail->next = nullptr;
        }

        return returningVal;
    }

    T deleteFromPosition(int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return T(); }
        if (isEmpty()) { cout << "List is empty." << endl; return T(); }

        Node<T>* head = getHead();

        if (index == 0) {
            return deleteFromHead();
        }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        if (tempPtr == nullptr) {
            cout << "Index out of bounds." << endl;
            return T();
        }

        T returningVal = tempPtr->data;

        if (tempPtr == tail) {
            tail = tempPtr->prev;
            tail->next = nullptr;
        }
        else {
            tempPtr->prev->next = tempPtr->next;
            tempPtr->next->prev = tempPtr->prev;
        }

        delete tempPtr;
        return returningVal;
    }

    void deleteValue(T val) {
        if (isEmpty()) { cout << "Doubly linked list is empty." << endl; return; }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;

        while (tempPtr != nullptr) {
            if (tempPtr->data == val) {
                T deletedVal = tempPtr->data;

                if (tempPtr == head && tempPtr == tail) {
                    delete head;
                    tail = nullptr;
                }
                else if (tempPtr == head) {
                    head = head->next;
                    head->prev = nullptr;
                    delete tempPtr;
                }
                else if (tempPtr == tail) {
                    tail = tail->prev;
                    tail->next = nullptr;
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

        cout << "Value " << val << " not found in list." << endl;
    }
};

//------------------------------------------------------------------------------------------------------------------