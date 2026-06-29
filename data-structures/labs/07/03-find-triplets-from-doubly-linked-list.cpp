#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int d) : data(d), prev(nullptr), next(nullptr) {}
};

class TripletList {
private:
    Node* head;
    Node* tail;
public:

    TripletList() : head(nullptr), tail(nullptr) {}

    ~TripletList() {
        Node* temp = head;

        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }

    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void printList() {
        Node* temp = head;

        cout << "Doubly Linked List: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void findTriplets(int targetSum) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        bool found = false;

        for (Node* first = head; first != nullptr; first = first->next) {
            for (Node* second = first->next; second != nullptr; second = second->next) {
                for (Node* third = second->next; third != nullptr; third = third->next) {
                    int sum = first->data + second->data + third->data;
                    if (sum == targetSum) {
                        cout << "Triplet: " << first->data << ", " << second->data << ", " << third->data << endl;
                        found = true;
                    }
                }
            }
        }
        if (!found) cout << "No triplets found." << endl;
    }
};

int main() {
    TripletList list;

    list.insertAtEnd(1);
    list.insertAtEnd(2);
    list.insertAtEnd(3);
    list.insertAtEnd(4);
    list.insertAtEnd(5);

    list.printList();

    int target = 9;

    cout << "Target Sum: " << target << endl << endl;

    list.findTriplets(target);

    return 0;
}