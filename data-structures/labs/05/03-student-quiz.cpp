#include "queue/linearqueue.h"
#include <string>
#include <cstdlib>   // for rand()
#include <ctime>     // for srand(time(0))

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

//---------------- Student Struct ----------------

class Student {
private:
    string name;
    int score;
    int timeTaken;
public:
    // constructor
    Student(const string& n = "", int s = 0, int t = 0) : name(n), score(s), timeTaken(t) {}

    // set student name (for adding to waiting queue)
    void setName(const string& n) {
        name = n;
        score = 0;
        timeTaken = 0;
    }

    // input function
    void read() {
        cout << "Enter student name: ";
        getline(cin, name);
        score = 0;
        timeTaken = 0;
    }

    // Generate random score and time
    void generateResults() {
        score = rand() % 101;              // score 0 – 100
        timeTaken = 30 + rand() % 271;     // time 30 – 300 seconds
    }

    // display student info
    void display() const {
        cout << "Name: " << name << ", Score: " << score << ", Time Taken: " << timeTaken << "s";
    }

    // overload << 
    friend ostream& operator<<(ostream& out, const Student& s) {
        s.display(); return out;
    }
};

//---------------- Main ----------------

int main() {
    srand(time(0));

    int quSize;
    cout << "Enter maximum number of students in the queue: ";
    cin >> quSize; cin.ignore();

    Queue<Student>* waitingQueue = new MyLinearQueue<Student>(quSize);
    Queue<Student>* completedQueue = new MyLinearQueue<Student>(quSize);

    int choice;
    do {
        clearScreen();
        cout << "\n=== Quiz Competition Menu ===\n";
        cout << "1. Add a student to the waiting queue\n";
        cout << "2. Start the quiz and generate scores\n";
        cout << "3. Display completed students\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; cin.ignore();

        switch (choice) {
        case 1: {
            if (waitingQueue->isFull()) {
                cout << "Waiting queue is full! Cannot add more students.\n"; pauseScreen();
                break;
            }
            Student s;
            s.read();
            waitingQueue->enqueue(s);
            cout << "Student added to the waiting queue.\n"; pauseScreen();
            break;
        }
        case 2: {
            if (waitingQueue->isEmpty()) {
                cout << "No students in the waiting queue! Quiz ended.\n"; pauseScreen();
                break;
            }
            Student s = waitingQueue->dequeue();
            s.generateResults(); // generate score and time
            completedQueue->enqueue(s);
            cout << "Student " << s << " has completed the quiz.\n"; pauseScreen();
            break;
        }
        case 3:
            if (completedQueue->isEmpty()) {
                cout << "No students have completed the quiz yet.\n"; pauseScreen();
            }
            else {
                cout << "\n=== Completed Students ===\n";
                completedQueue->display(); pauseScreen();
            }
            break;
        case 4:
            cout << "Exiting program.\n"; pauseScreen();
            break;
        default:
            cout << "Invalid choice! Try again.\n"; pauseScreen();
        }
    }
    while (choice != 4);

    delete waitingQueue;
    delete completedQueue;
    return 0;
}
