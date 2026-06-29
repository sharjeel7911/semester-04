#include "queue/circularqueue.h"

struct Process {
    string processId;
    int burstTime;

    // constructor
    Process() : processId(""), burstTime(0) {}
    Process(string pid, int bt) : processId(pid), burstTime(bt) {}
};


// functions
void addProcess(MyCircularQueue<Process>& qu, const Process&);
void executeNext(MyCircularQueue<Process>&, int);
ostream& operator<<(ostream&, const Process&);


// MAIN 
int main() {
    MyCircularQueue<Process> qu(10);

    Process p1("P1", 10);
    Process p2("P2", 4);
    Process p3("P3", 2);

    int timeSlice = 3;

    addProcess(qu, p1);
    addProcess(qu, p2);
    addProcess(qu, p3);

    cout << "Round Robin Scheduling:\n";

    while (!qu.isEmpty()) {
        executeNext(qu, timeSlice);
    }

    cout << "All processes completed.\n";
    return 0;
}

void addProcess(MyCircularQueue<Process>& qu, const Process& pr) { qu.enqueue(pr); }

void executeNext(MyCircularQueue<Process>& qu, int timeSlice) {
    if (qu.isEmpty()) return;

    Process pr = qu.dequeue();

    cout << "Executing: " << pr.processId << endl;

    if (pr.burstTime <= timeSlice) {
        cout << "Process Finished\n";
    }
    else {
        pr.burstTime -= timeSlice;
        cout << "Process Remaining time: " << pr.burstTime << endl;
        qu.enqueue(pr);
    }
}

ostream& operator<<(ostream& out, const Process& pr) {
    out << pr.processId << " ( Burst: " << pr.burstTime << ")" << endl;
    return out;
}
