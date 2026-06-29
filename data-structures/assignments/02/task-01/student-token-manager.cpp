#include "../queue/linearqueue.h"
#include <string>

struct Student {
    int tokenID;
    string name;
    string serviceType;
};

// ===== STUDENT TOKEN CLASS =====

class StudentTokenManager {
private:
    MyLinearQueue<Student> qu;
    int nextToken;
public:
    // constructor
    StudentTokenManager(int size) : qu(size) {
        nextToken = 506;
    }

    // add student
    void addStudent(const string& name, const string& serviceType) {
        if (qu.isFull()) { cout << "Queue is full. Can't add more students.\n"; return; }

        Student s;
        s.tokenID = nextToken;
        s.name = name;
        s.serviceType = serviceType;
        qu.enqueue(s);
        nextToken++;
        cout << "Token Issued: " << s.tokenID << endl;
    }

    // serve student
    void serveStudent() {
        if (qu.isEmpty()) { cout << "No students in queue\n"; return; }

        Student s = qu.dequeue();
        cout << "Serving Token: " << s.tokenID << " | Name: " << s.name << " | Service: " << s.serviceType << endl;
    }

    // show front
    void showNext() {
        if (qu.isEmpty()) { cout << "No students in queue\n"; return; }

        Student s = qu.peek();
        if (!qu.isEmpty()) {
            cout << "Next Token: " << s.tokenID << " | Name: " << s.name << " | Service: " << s.serviceType << endl;
        }
    }

    // display all
    void displayAll() {
        if (qu.isEmpty()) { cout << "Queue is empty\n"; return; }

        cout << "\n--- Current Queue ---\n";

        for (int i = 0; i < qu.getCurrSize(); i++) {
            Student s = qu[i];
            cout << "Token: " << s.tokenID << " | Name: " << s.name << " | Service: " << s.serviceType << endl;
        }
    }

    // count students
    void countStudents() { cout << "Total Waiting Students: " << qu.getCurrSize() << endl; }

    // searches a student in queue
    void searchStudent(int tokenID, string name) {
        if (qu.isEmpty()) { cout << "Queue is empty\n"; return; }

        bool found = false;

        for (int i = 0; i < qu.getCurrSize(); i++) {
            Student s = qu[i];

            if (s.tokenID == tokenID || s.name == name) {
                cout << "\nStudent Found:\n";
                cout << "Token ID: " << s.tokenID << endl;
                cout << "Name: " << s.name << endl;
                cout << "Service Type: " << s.serviceType << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Student not found in queue.\n";
        }
    }
};

ostream& operator<<(ostream& os, const Student& s) {
    os << "Token: " << s.tokenID << " | Name: " << s.name << " | Service: " << s.serviceType;
    return os;
}

// ===== MAIN FUNCTION =====

int main() {
    StudentTokenManager stm(10);

    // ===== Adding at least 5 sample student records =====
    stm.addStudent("Alice", "Fee Payment Issue");
    stm.addStudent("Bob", "Library Fine Issue");
    stm.addStudent("Charlie", "IT Support Request");
    stm.addStudent("David", "Transcript Issue");
    stm.addStudent("Emma", "Exam Registration Issue");

    // ===== Custom issue type (extra requirement) =====
    stm.addStudent("Frank", "Transport Card Activation Issue");

    cout << "\n";

    // Show all students in queue
    stm.displayAll();

    cout << "\n";

    // Show next student to be served
    stm.showNext();

    cout << "\n";

    // Search for a student
    stm.searchStudent(508, "Charlie");

    cout << "\n";

    // Serve two students
    stm.serveStudent();
    stm.serveStudent();

    cout << "\nAfter serving two students:\n";
    stm.displayAll();

    cout << "\n";

    // Count remaining students
    stm.countStudents();

    return 0;
}
