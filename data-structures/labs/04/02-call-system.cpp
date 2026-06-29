#include "stack/stack.h"

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

//---------------------------------------------------------------------------

class CallSystem {
private:
    MyStack<string> callStack;
public:
    CallSystem(int maxSize) : callStack(maxSize) {}

    void newCall(string caller) {
        callStack.push(caller);
        cout << "Incoming call: " << caller << endl;
    }

    void endCall() {
        if (!callStack.isEmpty()) {
            string ended = callStack.pop();
            cout << "Call ended: " << ended << endl;
        }
        else {
            cout << "No active call to end.\n";
        }
    }

    void currentCall() {
        if (!callStack.isEmpty()) {
            cout << "Current call: " << callStack.top() << endl;
        }
        else {
            cout << "No active call.\n";
        }
    }

    void showCalls() {
        cout << "=== Active Call Stack ===\n";
        callStack.display();
    }

    bool isEmpty() {
        return callStack.isEmpty();
    }
};

//---------------------------------------------------------------------------

int main() {
    int maxCalls;
    cout << "Enter maximum number of calls the phone can handle: ";
    cin >> maxCalls;
    cin.ignore();

    CallSystem cs(maxCalls);

    int choice;
    string caller;

    do {
        clearScreen();

        cout << "\n==== Mobile Call Stack ====\n";
        cout << "1. New Call (Push)\n";
        cout << "2. End Current Call (Pop)\n";
        cout << "3. Check Current Call (Top)\n";
        cout << "4. Display All Calls\n";
        cout << "5. Check if Call Stack is Empty\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {

        case 1:
            cout << "Enter caller name: ";
            getline(cin, caller);
            cs.newCall(caller);
            break;

        case 2:
            cs.endCall();
            break;

        case 3:
            cs.currentCall();
            break;

        case 4:
            cs.showCalls();
            break;

        case 5:
            if (cs.isEmpty())
                cout << "No ongoing calls.\n";
            else
                cout << "There are ongoing calls.\n";
            break;

        case 0:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

        pauseScreen();

    } while (choice != 0);

    return 0;
}
