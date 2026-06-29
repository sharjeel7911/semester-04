#include "queue/linearqueue.h"
#include <string>

//----------------------------------------------------------------------

inline void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[1;1H";
#endif
}

inline void pauseScreen() {
    cout << "Press Enter to continue..." << endl;
    cin.get();
}

//----------------------------------------------------------------------

struct Customer {
    string name;
    string transaction;

    Customer(const string& n = "", const string& t = "") : name(n), transaction(t) {}
};

ostream& operator<<(ostream& out, const Customer& customer) {
    out << "Name: " << customer.name << "\nTransaction: " << customer.transaction; cout << endl;
    return out;
}

istream& operator>>(istream& in, Customer& customer) {
    cout << "Enter customer name: "; getline(in, customer.name);
    cout << "Enter transaction type: "; getline(in, customer.transaction);
    return in;
}

//----------------------------------------------------------------------

int main() {
    int quSize;
    cout << "Enter maximum number of customers in the queue: ";
    cin >> quSize; cin.ignore();

    Queue<Customer>* qu = new MyLinearQueue<Customer>(quSize);

    int choice;

    do {
        clearScreen();
        cout << "\n=== Bank Queue Menu ===\n";
        cout << "1. Add a customer (enqueue)\n";
        cout << "2. Serve a customer (dequeue)\n";
        cout << "3. Display all waiting customers\n";
        cout << "4. Show total number of customers waiting\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; cin.ignore();

        switch (choice) {
        case 1: {
            if (qu->isFull()) {
                cout << "Queue is full! Cannot add more customers.\n"; pauseScreen();
                break;
            }

            Customer c;
            cin >> c;
            qu->enqueue(c);
            cout << "Customer added to the queue.\n"; pauseScreen();
            break;
        }
        case 2: {
            if (qu->isEmpty()) {
                cout << "Queue is empty! No customer to serve.\n"; pauseScreen();
                break;
            }
            Customer served = qu->dequeue();
            cout << "Served Customer -> " << served << endl; pauseScreen();
            break;
        }
        case 3:
            qu->display();
            pauseScreen();
            break;
        case 4:
            cout << "Total customers waiting: " << qu->Queue<Customer>::getSize() << endl; pauseScreen();
            break;
        case 5:
            cout << "Exiting program.\n"; pauseScreen();
            break;
        default:
            cout << "Invalid choice! Try again.\n"; pauseScreen();
        }
    }
    while (choice != 5);

    delete qu;
    return 0;
}
