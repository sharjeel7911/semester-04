#include <iostream>
#include <string>
using namespace std;

struct BookNode {
  int isbn;
  string title;
  BookNode *leftChild;
  BookNode *rightChild;

  BookNode(int id, string t)
      : isbn(id), title(t), leftChild(nullptr), rightChild(nullptr) {}
};

struct ListNode {
  int isbn;
  string title;
  ListNode *next;

  ListNode(int id, string t) : isbn(id), title(t), next(nullptr) {}
};

// ----------------------------------------------------------------------

class LibrarySystem {
private:
  BookNode *root;

  ListNode *head;
  ListNode *tail;

  BookNode *insertBook(BookNode *node, int isbn, const string &title) {
    if (node == nullptr) {
      return new BookNode(isbn, title);
    }

    if (isbn < node->isbn) {
      node->leftChild = insertBook(node->leftChild, isbn, title);
    } else if (isbn > node->isbn) {
      node->rightChild = insertBook(node->rightChild, isbn, title);
    } else {
      cout << " [Warning] Book with ISBN " << isbn
           << " already exists. Skipped.\n";
    }
    return node;
  }

  void inorderBST(BookNode *node) {
    if (node == nullptr)
      return;
    inorderBST(node->leftChild);
    cout << "[" << node->isbn << ": " << node->title << "] -> ";
    inorderBST(node->rightChild);
  }

  void convertToLinkedList(BookNode *treeNode) {
    if (treeNode == nullptr)
      return;

    convertToLinkedList(treeNode->leftChild);

    ListNode *newListNode = new ListNode(treeNode->isbn, treeNode->title);

    if (head == nullptr) {
      head = newListNode;
      tail = newListNode;
    } else {
      tail->next = newListNode;
      tail = newListNode;
    }

    convertToLinkedList(treeNode->rightChild);
  }

  void clearTree(BookNode *node) {
    if (node == nullptr)
      return;
    clearTree(node->leftChild);
    clearTree(node->rightChild);
    delete node;
  }

  void clearList(ListNode *node) {
    while (node != nullptr) {
      ListNode *temp = node->next;
      delete node;
      node = temp;
    }
  }

public:
  LibrarySystem() : root(nullptr), head(nullptr), tail(nullptr) {}

  ~LibrarySystem() {
    clearTree(root);
    clearList(head);
    root = nullptr;
    head = nullptr;
    tail = nullptr;
  }

  void insertBook(int isbn, const string &title) {
    root = insertBook(root, isbn, title);
  }

  void printBSTCatalog() {
    if (root == nullptr) {
      cout << "BST is empty.\n";
      return;
    }
    inorderBST(root);
    cout << "NULL\n";
  }

  void generateFlatCatalog() {
    clearList(head);
    head = nullptr;
    tail = nullptr;

    convertToLinkedList(root);
  }

  void printLinkedListCatalog() {
    if (head == nullptr) {
      cout << "Linked List Catalog is empty! Run generation first.\n";
      return;
    }
    ListNode *temp = head;
    while (temp != nullptr) {
      cout << " ISBN: " << temp->isbn << " | Title: \"" << temp->title
           << "\"\n";
      temp = temp->next;
    }
    cout << " End of flat catalog sequential stream.\n";
  }
};

int main() {
  LibrarySystem library;

  cout << "==================================================\n";
  cout << "        LIBRARY DATABASE CATALOG MANAGEMENT       \n";
  cout << "==================================================\n\n";

  // insert books out of order into the bst
  cout << ">> Registering books into the library system storage database...\n";
  library.insertBook(97803, "The C++ Programming Language");
  library.insertBook(97801, "Introduction to Algorithms");
  library.insertBook(97805, "Clean Code");
  library.insertBook(97802, "Design Patterns");
  library.insertBook(97804, "Artificial Intelligence: A Modern Approach");

  // verify the sorting sequence via natural bst paths
  cout << "\nVerification: Verifying structural order via BST Inorder "
          "Traversal:\n   ";
  library.printBSTCatalog();

  // flatten and print out the optimized list structure
  cout << "\n>> Flattening tree storage into an optimized Singly Linked List "
          "catalog...\n";
  library.generateFlatCatalog();

  cout << "\n--------------------------------------------------\n";
  cout << "         FINAL SEQUENTIAL BOOK CATALOG            \n";
  cout << "--------------------------------------------------\n";
  library.printLinkedListCatalog();
  cout << "--------------------------------------------------\n";

  return 0;
}