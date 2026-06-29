#include <iostream>
#include <string>
using namespace std;

struct ProductNode {
    int id;
    string name;
    ProductNode* next;

    ProductNode(int i, string n) : id(i), name(n), next(nullptr) {}
};

class ProductManagement {
private:
    ProductNode* head;
    ProductNode* tail;
public:
    ProductManagement() : head(nullptr), tail(nullptr) {}

    ~ProductManagement() {
        while (head != nullptr) {
            ProductNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertAtTail(int id, string name) {
        ProductNode* newNode = new ProductNode(id, name);

        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void display() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        ProductNode* temp = head;

        cout << "Linked List:" << endl;

        while (temp != nullptr) {
            cout << "ID: " << temp->id
                << ", Name: " << temp->name << endl;

            temp = temp->next;
        }
    }

    int searchRecord(int id) {
        ProductNode* temp = head;
        int position = 0;

        while (temp != nullptr) {
            if (temp->id == id) {
                return position;
            }

            temp = temp->next;
            position++;
        }

        return -1;
    }

    void deleteProductAtPosition(int pos) {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        // Delete first node
        if (pos == 0) {
            ProductNode* temp = head;
            head = head->next;

            if (!head) {
                tail = nullptr;
            }

            delete temp;
            return;
        }

        ProductNode* temp = head;

        for (int i = 0; temp != nullptr && i < pos - 1; i++) {
            temp = temp->next;
        }

        if (temp == nullptr || temp->next == nullptr) {
            cout << "Invalid position." << endl;
            return;
        }

        ProductNode* nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;

        if (nodeToDelete == tail) {
            tail = temp;
        }

        delete nodeToDelete;
    }
};

int main() {

    ProductManagement pm;

    pm.insertAtTail(101, "Laptop");
    pm.insertAtTail(102, "Mouse");
    pm.insertAtTail(103, "Keyboard");
    pm.insertAtTail(104, "Monitor");

    cout << "Initial List:" << endl;
    pm.display();

    int idToDelete;

    cout << "\nEnter the product ID to search and delete: ";
    cin >> idToDelete;

    int position = pm.searchRecord(idToDelete);

    if (position != -1) {
        pm.deleteProductAtPosition(position);
        cout << "Product with ID " << idToDelete << " deleted successfully." << endl;
    }
    else {
        cout << "Product with ID " << idToDelete << " not found." << endl;
    }

    cout << "\nUpdated List:" << endl;
    pm.display();

    return 0;
}
