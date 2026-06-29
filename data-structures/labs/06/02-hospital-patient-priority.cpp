#include "queue/priorityqueue.h"
#include "queue/circularqueue.h"

//---------------- Utility Functions ----------------

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

//---------------- Patient Struct ----------------

struct Patient {
    string name;
    int severity;      // 1 = Critical, 2 = Serious, 3 = Normal
    int arrivalTime, waitingTime;

    Patient() : name(""), severity(3), arrivalTime(0), waitingTime(0) {}

    Patient(string n, int s, int a = 0) : name(n), severity(s), arrivalTime(a), waitingTime(0) {}

    // For comparison in priority queue (lower severity = higher priority)
    bool operator>(const Patient& obj) const { return severity > obj.severity; }
};

ostream& operator<<(ostream& out, const Patient& p) {
    out << p.name << " (Severity: " << p.severity << ", Waiting: " << p.waitingTime << ")";
    return out;
}

//---------------- PatientQueueCircular class ----------------

class PatientQueueCircular {
private:
    MyCircularQueue<Patient> critical;
    MyCircularQueue<Patient> serious;
    MyCircularQueue<Patient> normal;

public:
    PatientQueueCircular(int maxSize) : critical(maxSize), serious(maxSize), normal(maxSize) {}

    void enqueue(Patient p) {
        switch (p.severity) {
        case 1: critical.enqueue(p); break;
        case 2: serious.enqueue(p); break;
        case 3: normal.enqueue(p); break;
        default: cout << "Invalid severity\n";
        }
    }

    Patient dequeue() {
        if (!critical.isEmpty()) return critical.dequeue();
        if (!serious.isEmpty()) return serious.dequeue();
        if (!normal.isEmpty()) return normal.dequeue();
        cout << "All queues are empty\n";
        return Patient();
    }

    void display() {
        cout << "\n--- Critical Queue ---\n";
        critical.display();
        cout << "\n--- Serious Queue ---\n";
        serious.display();
        cout << "\n--- Normal Queue ---\n";
        normal.display();
    }
};

//---------------- PatientQueuePriority class ----------------

class PatientQueuePriority {
private:
    MyCircularQueue<Patient> critical;
    MyCircularQueue<Patient> serious;
    MyCircularQueue<Patient> normal;

    int totalPatients;
    int totalWaitingTime;
    const int threshold = 5;

public:
    PatientQueuePriority(int maxSize) : critical(maxSize), serious(maxSize), normal(maxSize), totalPatients(0), totalWaitingTime(0) {}

    void enqueue(Patient p) {
        p.waitingTime = 0;
        switch (p.severity) {
        case 1: critical.enqueue(p); break;
        case 2: serious.enqueue(p); break;
        case 3: normal.enqueue(p); break;
        }
    }

    void updateWaitingTime() {
        auto incrementWaiting = [](MyCircularQueue<Patient>& q) {
            int sz = q.getCurrSize();
            for (int i = 0; i < sz; i++) {
                Patient p = q.dequeue();
                p.waitingTime++;
                q.enqueue(p);
            }
            };
        incrementWaiting(critical);
        incrementWaiting(serious);
        incrementWaiting(normal);
    }

    void escalatePriority() {
        int sz = normal.getCurrSize();
        for (int i = 0; i < sz; i++) {
            Patient p = normal.dequeue();
            if (p.waitingTime > threshold) {
                p.severity = 2;
                serious.enqueue(p);
            }
            else normal.enqueue(p);
        }

        sz = serious.getCurrSize();
        for (int i = 0; i < sz; i++) {
            Patient p = serious.dequeue();
            if (p.waitingTime > threshold) {
                p.severity = 1;
                critical.enqueue(p);
            }
            else serious.enqueue(p);
        }
    }

    void dequeue() {
        updateWaitingTime();
        escalatePriority();
        Patient next;
        if (!critical.isEmpty()) next = critical.dequeue();
        else if (!serious.isEmpty()) next = serious.dequeue();
        else if (!normal.isEmpty()) next = normal.dequeue();
        else {
            cout << "No patients in queue\n";
            return;
        }

        totalPatients++;
        totalWaitingTime += next.waitingTime;
        cout << "Doctor sees: " << next << endl;
    }

    void displayQueues() {
        cout << "\n--- Critical Queue ---\n"; critical.display();
        cout << "\n--- Serious Queue ---\n"; serious.display();
        cout << "\n--- Normal Queue ---\n"; normal.display();
    }

    void statistics() {
        cout << "Total patients processed: " << totalPatients << endl;
        if (totalPatients > 0)
            cout << "Average waiting time: " << (double)totalWaitingTime / totalPatients << " mins\n";
        else cout << "No patients processed yet\n";
    }
};

//---------------- MAIN FUNCTION ----------------

int main() {
    int mode;
    clearScreen();
    cout << "Select mode:\n1 = Simple (Circular Queue)\n2 = Extended (Priority + Waiting Time)\nChoice: ";
    cin >> mode;
    cin.ignore();

    int maxSize = 100;
    string name;
    int severity;
    int arrival;

    if (mode == 1) {
        PatientQueueCircular pq(maxSize);
        int choice;
        do {
            clearScreen();
            cout << "\n1. Add a patient\n2. Doctor sees next patient\n3. Display all waiting patients\n0. Exit\nChoice: ";
            cin >> choice;
            cin.ignore();
            switch (choice) {
            case 1:
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter severity (1-Critical,2-Serious,3-Normal): ";
                cin >> severity;
                cin.ignore();
                pq.enqueue(Patient(name, severity));
                break;
            case 2:
            {
                Patient next = pq.dequeue();
                if (next.name != "") cout << "Doctor sees: " << next << endl;
                break;
            }
            case 3: clearScreen();
                pq.display();
                pauseScreen();
                break;
            case 0:
                cout << "Exiting simple mode...\n";
                break;
            default:
                cout << "Invalid choice\n";
            }
        }
        while (choice != 0);
    }
    else if (mode == 2) {
        PatientQueuePriority pq(maxSize);
        int choice;
        do {
            clearScreen();
            cout << "\n1. Add a patient\n2. Doctor sees next patient\n3. Display all waiting patients\n4. Show statistics\n0. Exit\nChoice: ";
            cin >> choice;
            cin.ignore();
            switch (choice) {
            case 1:
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter severity (1 - Critical, 2 - Serious, 3 - Normal) and arrivalTime: ";
                cin >> severity >> arrival;
                cin.ignore();
                pq.enqueue(Patient(name, severity, arrival));
                break;
            case 2:
                pq.dequeue();
                break;
            case 3: clearScreen();
                pq.displayQueues();
                pauseScreen();
                break;
            case 4:
                pq.statistics();
                break;
            case 0:
                cout << "Exiting extended mode...\n";
                break;
            default:
                cout << "Invalid choice\n";
            }
        }
        while (choice != 0);
    }
    else {
        cout << "Invalid mode selected!\n";
    }
    return 0;
}
