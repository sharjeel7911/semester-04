#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct StudentNode {
    int rollNo;
    string name;
    float marks;
    StudentNode* next;

    StudentNode(int r, string n, float m) : rollNo(r), name(n), marks(m), next(nullptr) {}
};

class StudentManagementSystem {
private:
    StudentNode* head;
    StudentNode* tail;
public:
    StudentManagementSystem() : head(nullptr), tail(nullptr) {}

    ~StudentManagementSystem() {
        while (head != nullptr) {
            StudentNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertAtBeginning(int r, string n, float m) {
        StudentNode* newNode = new StudentNode(r, n, m);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
    }

    void insertAtEnd(int r, string n, float m) {
        StudentNode* newNode = new StudentNode(r, n, m);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void insertAfterRollNo(int afterRoll, int r, string n, float m) {
        StudentNode* temp = head;
        while (temp != nullptr && temp->rollNo != afterRoll) {
            temp = temp->next;
        }
        if (!temp) {
            cout << "Roll number " << afterRoll << " not found!" << endl;
            return;
        }
        StudentNode* newNode = new StudentNode(r, n, m);
        newNode->next = temp->next;
        temp->next = newNode;
        if (temp == tail) tail = newNode;
    }

    void deleteFromBeginning() {
        if (!head) return;
        StudentNode* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
    }

    void deleteFromEnd() {
        if (!head) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }
        StudentNode* temp = head;

        while (temp->next != tail) {
            temp = temp->next;
        }

        delete tail;
        tail = temp;
        tail->next = nullptr;
    }

    void deleteByRollNo(int rollNo) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        if (head->rollNo == rollNo) {
            deleteFromBeginning();
            return;
        }

        StudentNode* temp = head;

        while (temp->next != nullptr && temp->next->rollNo != rollNo) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Roll not found." << endl;
            return;
        }

        StudentNode* nodeToDelete = temp->next;

        temp->next = nodeToDelete->next;

        if (nodeToDelete == tail) {
            tail = temp;
        }
        delete nodeToDelete;
        cout << "Record deleted successfully." << endl;
    }

    void display() {
        if (!head) { cout << "No records." << endl; return; }
        cout << left << setw(10) << "Roll No" << setw(20) << "Name" << "Marks" << endl;
        StudentNode* temp = head;
        while (temp) {
            cout << left << setw(10) << temp->rollNo << setw(20) << temp->name << temp->marks << endl;
            temp = temp->next;
        }
    }

    void search(int rollNo) {
        StudentNode* temp = head;
        while (temp) {
            if (temp->rollNo == rollNo) {
                cout << "Found: " << temp->name << ", Marks: " << temp->marks << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Not found." << endl;
    }

    void update(int rollNo) {
        StudentNode* temp = head;

        while (temp) {
            if (temp->rollNo == rollNo) {

                cin.ignore();

                cout << "Enter new name: ";
                getline(cin, temp->name);

                cout << "Enter new marks: ";
                cin >> temp->marks;

                cout << "Record updated successfully." << endl;
                return;
            }

            temp = temp->next;
        }

        cout << "Not found." << endl;
    }

    void showStats() {
        if (!head) {
            cout << "No records available." << endl;
            return;
        }
        float minM = 101, maxM = -1, sum = 0;
        int count = 0;
        for (StudentNode* temp = head; temp; temp = temp->next) {
            if (temp->marks < minM) minM = temp->marks;
            if (temp->marks > maxM) maxM = temp->marks;
            sum += temp->marks;
            count++;
        }
        cout << "Max: " << maxM << " | Min: " << minM << " | Avg: " << sum / count << endl;
    }
};

int main() {
    StudentManagementSystem sms;

    int choice;
    int rollNo, afterRoll;
    string name;
    float marks;

    do {
        cout << "\n========== Student Record Management System ==========\n";
        cout << "1. Insert at Beginning\n";
        cout << "2. Insert at End\n";
        cout << "3. Insert After Roll Number\n";
        cout << "4. Delete From Beginning\n";
        cout << "5. Delete From End\n";
        cout << "6. Delete By Roll Number\n";
        cout << "7. Display Records\n";
        cout << "8. Search Student\n";
        cout << "9. Update Student\n";
        cout << "10. Show Statistics\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter Roll Number: ";
            cin >> rollNo;

            cin.ignore();

            cout << "Enter Name: ";
            getline(cin, name);

            cout << "Enter Marks: ";
            cin >> marks;

            sms.insertAtBeginning(rollNo, name, marks);

            cout << "Record inserted at beginning.\n";
            break;

        case 2:
            cout << "Enter Roll Number: ";
            cin >> rollNo;

            cin.ignore();

            cout << "Enter Name: ";
            getline(cin, name);

            cout << "Enter Marks: ";
            cin >> marks;

            sms.insertAtEnd(rollNo, name, marks);

            cout << "Record inserted at end.\n";
            break;

        case 3:
            cout << "Enter Roll Number after which to insert: ";
            cin >> afterRoll;

            cout << "Enter New Roll Number: ";
            cin >> rollNo;

            cin.ignore();

            cout << "Enter Name: ";
            getline(cin, name);

            cout << "Enter Marks: ";
            cin >> marks;

            sms.insertAfterRollNo(afterRoll, rollNo, name, marks);
            break;

        case 4:
            sms.deleteFromBeginning();
            cout << "First record deleted.\n";
            break;

        case 5:
            sms.deleteFromEnd();
            cout << "Last record deleted.\n";
            break;

        case 6:
            cout << "Enter Roll Number to delete: ";
            cin >> rollNo;

            sms.deleteByRollNo(rollNo);
            break;

        case 7:
            sms.display();
            break;

        case 8:
            cout << "Enter Roll Number to search: ";
            cin >> rollNo;

            sms.search(rollNo);
            break;

        case 9:
            cout << "Enter Roll Number to update: ";
            cin >> rollNo;

            sms.update(rollNo);
            break;

        case 10:
            sms.showStats();
            break;

        case 0:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
    while (choice != 0);
    return 0;
}