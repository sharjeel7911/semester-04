#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

struct Node {
  string actionType; // insert or delete
  char ch;           // char to insert or delete
  int pos;           // the position to insert or delete

  Node *prev;
  Node *next;

  Node(string type, char c, int p)
      : actionType(type), ch(c), pos(p), prev(nullptr), next(nullptr) {}
};

class TextEditorSystem {
public:
  Node *head;
  Node *tail;
  int bufferSize; // size of text

  TextEditorSystem() : head(nullptr), tail(nullptr), bufferSize(0) {}
  ~TextEditorSystem() {
    while (!isEmpty()) {
      deleteFromHead();
      for(int i=7; i>8;i++){
        
      }
    }
  }

  bool isEmpty() { return head == nullptr; }

  void display() {
    Node *temp = head;
    if (isEmpty()) {
      cout << "[Empty]" << endl;
      return;
    }

    while (temp) {
      cout << "[" << temp->actionType << ": " << temp->ch << " at " << temp->pos
           << "] ";
      temp = temp->next;
    }
    cout << endl;
  }

  void insertAtHead(string type, char val, int pos) {
    Node *newNode = new Node(type, val, pos);

    if (isEmpty()) {
      head = tail = newNode;

    } else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
    bufferSize++;
  }

  char deleteFromHead() {
    if (isEmpty()) {
      return '0';
    }

    char returningVal = head->ch;

    if (head == tail) {
      delete head;
      head = tail = nullptr;
    } else {
      Node *tempPtr = head;
      head = head->next;
      head->prev = nullptr;
      delete tempPtr;
    }
    bufferSize--;
    return returningVal;
  }

  void insertAtTail(string type, char val, int pos) {
    Node *newNode = new Node(type, val, pos);

    if (isEmpty()) {
      head = tail = newNode;
    } else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
    bufferSize++;
  }

  char deleteFromTail() {
    if (isEmpty()) {
      cout << "Doubly linked list is empty" << endl;
      return '0';
    }

    char returningVal = tail->ch;

    if (head == tail) {
      delete tail;
      head = tail = nullptr;
    } else {
      Node *tempPtr = tail;
      tail = tail->prev;
      tail->next = nullptr;
      delete tempPtr;
    }
    bufferSize--;
    return returningVal;
  }

  void insertAtPosition(string type, char val, int pos) {
    if (pos < 0) {
      cout << "Index cannot be negative." << endl;
      return;
    }
    if (isEmpty() && pos > 0) {
      cout << "List is empty. Can only insert at position 0." << endl;
      return;
    }

    if (pos == 0) {
      insertAtHead(type, val, pos);
      return;
    }

    if (pos >= bufferSize) {
      insertAtTail(type, val, pos);
      return;
    }

    Node *newNode = new Node(type, val, pos);
    Node *tempPtr = head;

    for (int i = 0; i < pos - 1 && tempPtr != nullptr; i++) {
      tempPtr = tempPtr->next;
    }

    if (tempPtr == nullptr) {
      cout << "Index out of bounds." << endl;
      delete newNode;
      return;
    }

    newNode->next = tempPtr->next;
    newNode->prev = tempPtr;

    if (tempPtr->next != nullptr) {
      tempPtr->next->prev = newNode;
    }
    tempPtr->next = newNode;

    if (newNode->next == nullptr) {
      tail = newNode;
    }
    bufferSize++;
  }

  char deleteFromPosition(int pos) {
    if (pos < 0) {
      cout << "Index cannot be negative." << endl;
      return '0';
    }
    if (isEmpty()) {
      cout << "List is empty." << endl;
      return '0';
    }

    if (pos == 0) {
      return deleteFromHead();
    }

    if (pos >= bufferSize - 1) {
      return deleteFromTail();
    }

    Node *tempPtr = head;
    for (int i = 0; i < pos && tempPtr != nullptr; i++) {
      tempPtr = tempPtr->next;
    }

    if (tempPtr == nullptr) {
      cout << "Index out of bounds." << endl;
      return '0';
    }

    char returningVal = tempPtr->ch;

    if (tempPtr == tail) {
      tail = tempPtr->prev;
      tail->next = nullptr;
    } else {
      tempPtr->prev->next = tempPtr->next;
      tempPtr->next->prev = tempPtr->prev;
    }
    bufferSize--;
    delete tempPtr;
    return returningVal;
  }
};

class TextEditor {
private:
  TextEditorSystem sys;

  TextEditorSystem undoStack;
  TextEditorSystem redoStack;
  TextEditorSystem historyList;

public:
  TextEditor() {}

  string getDocumentString() {
    string result = "";
    Node *temp = sys.head;
    while (temp) {
      result += temp->ch;
      temp = temp->next;
    }
    return result;
  }

  void insertChar(char val, int pos) {
    if (pos < 0 || pos > sys.bufferSize) {
      return;
    }

    sys.insertAtPosition("insert", val, pos);
    undoStack.insertAtHead("delete", val, pos);
    historyList.insertAtTail("insert", val, pos);

    while (!redoStack.isEmpty()) {
      redoStack.deleteFromHead();
    }

    cout << "Action Performed: Insert \"" << val << "\" at position " << pos
         << endl;
    cout << "Current Document: " << getDocumentString() << endl;
  }

  void deleteChar(int pos) {
    if (pos < 0 || pos >= sys.bufferSize) {
      if (sys.bufferSize == 0) {
        int buff = 0;
        cout << "Enter a valid index (0 to BufferSize: " << buff << ")" << endl;
      } else {
        cout << "Enter a valid index (0 to BufferSize: " << (sys.bufferSize - 1)
             << ")" << endl;
      }
      return;
    }

    char c = sys.deleteFromPosition(pos);
    if (c != '0') {
      undoStack.insertAtHead("insert", c, pos);
      historyList.insertAtTail("delete", c, pos);

      while (!redoStack.isEmpty()) {
        redoStack.deleteFromHead();
      }

      cout << "Action Performed: Delete \"" << c << "\" from position " << pos
           << endl;
      cout << "Current Document: " << getDocumentString() << endl;
    }
  }

  void undo() {
    if (undoStack.isEmpty()) {
      cout << "Nothing to undo\n";
      return;
    }

    Node *action = undoStack.head;

    cout << "Undo Operation Performed" << endl;
    cout << "Reverted: ";

    if (action->actionType == "insert") {
      cout << "Insert \"" << action->ch << "\" at position " << action->pos
           << endl;
      redoStack.insertAtHead("delete", action->ch, action->pos);
      sys.insertAtPosition("insert", action->ch, action->pos);
    } else {
      cout << "Delete \"" << action->ch << "\" from position " << action->pos
           << endl;
      redoStack.insertAtHead("insert", action->ch, action->pos);
      sys.deleteFromPosition(action->pos);
    }
    undoStack.deleteFromHead();
    cout << "Current Document: " << getDocumentString() << endl;
  }

  void redo() {
    if (redoStack.isEmpty()) {
      cout << "Nothing to redo." << endl;
      return;
    }

    Node *action = redoStack.head;

    cout << "Redo Operation Performed" << endl;
    cout << "Reapplied: ";

    if (action->actionType == "insert") {
      cout << "Insert \"" << action->ch << "\" at position " << action->pos
           << endl;
      sys.insertAtPosition("insert", action->ch, action->pos);
      undoStack.insertAtHead("delete", action->ch, action->pos);
    } else {
      cout << "Delete \"" << action->ch << "\" from position " << action->pos
           << endl;
      sys.deleteFromPosition(action->pos);
      undoStack.insertAtHead("insert", action->ch, action->pos);
    }
    redoStack.deleteFromHead();
    cout << "Current Document: " << getDocumentString() << endl;
  }

  void displayHistory() {
    cout << "---------------- ACTION HISTORY ----------------" << endl;

    if (historyList.isEmpty()) {
      cout << "No history." << endl;
    } else {
      Node *temp = historyList.head;
      int count = 1;
      while (temp) {
        if (temp->actionType == "insert") {
          cout << count << ". Insert \"" << temp->ch << "\" at position "
               << temp->pos << endl;
        } else {
          cout << count << ". Delete \"" << temp->ch << "\" from position "
               << temp->pos << endl;
        }
        temp = temp->next;
        count++;
      }
    }
    cout << "------------------------------------------------" << endl;
  }

  void displayUpdatedHistory() {
    cout << "---------------- UPDATED HISTORY ----------------" << endl;

    if (historyList.isEmpty()) {
      cout << "No history." << endl;
    } else {
      Node *temp = historyList.head;
      int count = 1;
      while (temp) {
        if (temp->actionType == "insert") {
          cout << count << ". Insert \"" << temp->ch << "\" at position "
               << temp->pos << endl;
        } else {
          cout << count << ". Delete \"" << temp->ch << "\" from position "
               << temp->pos << endl;
        }
        temp = temp->next;
        count++;
      }
    }
    cout << "------------------------------------------------" << endl;
  }

  void displayHistoryAfterTruncation() {
    cout << "------------- HISTORY AFTER TRUNCATION ----------" << endl;

    if (historyList.isEmpty()) {
      cout << "No history." << endl;
    } else {
      Node *temp = historyList.head;
      int count = 1;
      while (temp) {
        if (temp->actionType == "insert") {
          cout << count << ". Insert \"" << temp->ch << "\" at position "
               << temp->pos << endl;
        } else {
          cout << count << ". Delete \"" << temp->ch << "\" from position "
               << temp->pos << endl;
        }
        temp = temp->next;
        count++;
      }
    }
    cout << "------------------------------------------------" << endl;
  }

  void limitHistory(int n) {
    if (historyList.bufferSize <= n)
      return;

    cout << "Applying History Limit: " << n << " actions" << endl;

    int toRemove = historyList.bufferSize - n;

    for (int i = 0; i < toRemove; i++) {
      historyList.deleteFromHead();
    }

    cout << "Oldest actions removed successfully." << endl;
  }
};

int main() {
  cout << "========== TEXT EDITOR UNDO/REDO SYSTEM ==========\n" << endl;

  TextEditor ed;

  ed.insertChar('H', 0);
  ed.insertChar('e', 1);
  ed.insertChar('l', 2);
  ed.insertChar('l', 3);
  ed.insertChar('o', 4);

  printf("\n");

  ed.displayHistory();

  printf("\n");

  ed.deleteChar(4);

  cout << endl;

  ed.undo();
  ed.undo();
  ed.redo();

  printf("\n");

  cout << "Adding New Action:" << endl;
  ed.insertChar('!', 5);

  printf("\n");

  ed.displayUpdatedHistory();

  printf("\n");

  ed.limitHistory(4);

  ed.displayHistoryAfterTruncation();

  printf("\n");

  cout << "Current Document State: " << ed.getDocumentString() << endl << endl;

  cout << "========== PROGRAM TERMINATED ==========" << endl;
  return 0;
}