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


int main() {
    int maxSize = 100;
    string text = "";
    MyStack<char> undoStack(maxSize);
    MyStack<char> redoStack(maxSize);

    int choice;
    char ch;

    do {
        clearScreen();
        cout << "\nCurrent Text: " << text << endl;
        cout << "=== Undo Stack === " << endl; undoStack.display(); cout << endl;
        cout << "=== Redo Stack === " << endl; redoStack.display(); cout << endl;

        cout << "\n=== Menu ===\n";
        cout << "1. Type character\n";
        cout << "2. Undo\n";
        cout << "3. Redo\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter character to type: ";
            cin >> ch;
            text += ch;
            undoStack.push(ch);
            while (!redoStack.isEmpty()) redoStack.pop();
            break;

        case 2:
            if (!undoStack.isEmpty()) {
                char last = undoStack.pop();
                text.pop_back();  // remove last character
                redoStack.push(last);
            }
            else {
                cout << "Nothing to undo.\n";
            }
            break;

        case 3:
            if (!redoStack.isEmpty()) {
                char last = redoStack.pop();
                text += last;      // reapply character
                undoStack.push(last);
            }
            else {
                cout << "Nothing to redo.\n";
            }
            break;

        case 0:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    }
    while (choice != 0);

    cout << "\nFinal Text: " << text << endl;
    cout << "=== Final Undo Stack === " << endl; undoStack.display(); cout << endl;
    cout << "=== FInal Redo Stack === " << endl; redoStack.display(); cout << endl;
    return 0;
}
