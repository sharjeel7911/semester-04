#include "../queue/circularqueue.h"
#include <string>

struct Task {
    int taskID;
    string taskName;
    int estimatedTime;
};

// ===== LAB SCHEDULER CLASS =====

class LabTaskScheduler {
private:
    MyCircularQueue<Task> qu;
    int nextTaskID;

public:
    // constructor
    LabTaskScheduler(int size) : qu(size) {
        nextTaskID = 506;
    }

    // enqueue task
    void addTask(const string& name, int time) {
        if (qu.isFull()) { cout << "Overflow: Lab is full. Cannot add task.\n"; return; }

        Task t;
        t.taskID = nextTaskID++;
        t.taskName = name;
        t.estimatedTime = time;

        qu.enqueue(t);
        cout << "Task Added: " << t.taskID << " | " << t.taskName << " | " << t.estimatedTime << " min\n";
    }

    // dequeue task
    void completeTask() {
        if (qu.isEmpty()) { cout << "Underflow: No tasks to execute.\n"; return; }

        Task t = qu.dequeue();

        cout << "Completed Task:\n";
        cout << "ID: " << t.taskID << " | Name: " << t.taskName << " | Time: " << t.estimatedTime << " min\n";
    }

    // show front task
    void showNextTask() {
        if (qu.isEmpty()) { cout << "No tasks available.\n"; return; }

        Task t = qu.peek();
        cout << "Next Task -> " << t.taskID << " | " << t.taskName << " | " << t.estimatedTime << " min\n";
    }

    void showFrontAndRear() {
        cout << "Front: " << qu.getFront() << endl;
        cout << "Rear: " << qu.getRear() << endl;
    }

    // display all tasks
    void displayAll() {
        if (qu.isEmpty()) { cout << "No tasks in scheduler.\n"; return; }

        cout << "\n--- Lab Task Queue ---\n";
        qu.display();
    }
};

ostream& operator<<(ostream& os, const Task& t) {
    os << "ID: " << t.taskID << " | Name: " << t.taskName << " | Time: " << t.estimatedTime << " min";
    return os;
}

// ===== MAIN FUNCTION =====

int main() {
    LabTaskScheduler lab(11); // 5 + 0 + 6 = 11

    // ===== 5 Sample Tasks =====
    lab.addTask("Run Compiler Test", 15);
    lab.addTask("Execute Sorting Program", 20);
    lab.addTask("Debug Queue Implementation", 25);
    lab.addTask("Compile Lab Report Code", 10);
    lab.addTask("Memory Leak Analysis", 30);

    cout << "\n";

    lab.displayAll();

    cout << "\n";

    lab.showNextTask();

    cout << "\n";

    lab.showFrontAndRear();

    cout << "\n";

    // Complete two tasks
    lab.completeTask(); lab.displayAll();
    lab.completeTask(); lab.displayAll();
    lab.completeTask(); lab.displayAll();
    lab.completeTask(); lab.displayAll();
    lab.completeTask(); lab.displayAll();

    cout << "\nNow after emptying all queue we can again add values in queue proving that empty spaces are reused\n\n";
    lab.showFrontAndRear();
    lab.addTask("Fix System Crash Issue (Custom Debug Task)", 40);
    lab.addTask("Run printer", 27);

    cout << "\nNew Task successfully added:\n";
    lab.displayAll();

    cout << "\n";

    lab.showNextTask();
    return 0;
}
