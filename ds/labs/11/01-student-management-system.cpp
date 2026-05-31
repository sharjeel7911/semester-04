#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Node {
  int data;
  Node *leftChild;
  Node *rightChild;

  Node(int val) : data(val), leftChild(nullptr), rightChild(nullptr) {}
};

class DataManagementSystem {
private:
  Node *root;

  // insert helper
  Node *insertVal(Node *node, int val) {
    if (node == nullptr) {
      return new Node(val);
    }

    if (val < node->data) {
      node->leftChild = insertVal(node->leftChild, val);
    } else if (val > node->data) {
      node->rightChild = insertVal(node->rightChild, val);
    } else {
      cout << " [Warning] Duplicate value " << val << " omitted.\n";
    }
    return node;
  }

  // deletion helper
  Node *deleteVal(Node *node, int val) {
    if (node == nullptr) {
      return node;
    }

    if (val < node->data) {
      node->leftChild = deleteVal(node->leftChild, val);
    } else if (val > node->data) {
      node->rightChild = deleteVal(node->rightChild, val);
    }

    else {
      // case 1 & 2: leaf node (no children) OR node with only one child
      if (node->leftChild == nullptr) {
        Node *temp = node->rightChild;
        delete node;
        return temp;
      } else if (node->rightChild == nullptr) {
        Node *temp = node->leftChild;
        delete node;
        return temp;
      }
      // case 3: node has 2 children
      else {
        // find smallest value in the right subtree
        Node *temp = findMin(node->rightChild);

        node->data = temp->data;

        // delete the successor from the right subtree
        node->rightChild = deleteVal(node->rightChild, temp->data);
      }
    }
    return node;
  }

  // find min in tree
  Node *findMin(Node *node) {
    while (node && node->leftChild != nullptr) {
      node = node->leftChild;
    }
    return node;
  }

  // in-order traversal (left -> root -> right)
  void inorder(Node *node) {
    if (node == nullptr)
      return;
    inorder(node->leftChild);
    cout << node->data << " ";
    inorder(node->rightChild);
  }

  // pre-order traversal (root -> left -> right)
  void preorder(Node *node) {
    if (node == nullptr)
      return;
    cout << node->data << " ";
    preorder(node->leftChild);
    preorder(node->rightChild);
  }

  // post-order traversal (left -> right -> root)
  void postorder(Node *node) {
    if (node == nullptr)
      return;
    postorder(node->leftChild);
    postorder(node->rightChild);
    cout << node->data << " ";
  }

  // searching a key
  bool searchVal(Node *node, int key) {
    if (node == nullptr) {
      return false;
    }
    if (node->data == key) {
      return true;
    }

    if (key < node->data) {
      return searchVal(node->leftChild, key);
    } else {
      return searchVal(node->rightChild, key);
    }
  }

  // cleanup helper
  void clear(Node *node) {
    if (node == nullptr)
      return;
    clear(node->leftChild);
    clear(node->rightChild);
    delete node;
  }

public:
  // constructor
  DataManagementSystem() : root(nullptr) {}

  // destructor
  ~DataManagementSystem() {
    clear(root);
    root = nullptr;
  }

  void insertVal(int val) { root = insertVal(root, val); }

  void deleteVal(int val) { root = deleteVal(root, val); }

  void displayInorder() {
    inorder(root);
    cout << endl;
  }

  void displayPreorder() {
    preorder(root);
    cout << endl;
  }

  void displayPostorder() {
    postorder(root);
    cout << endl;
  }

  bool searchVal(int key) { return searchVal(root, key); }
};

// main
int main() {
  DataManagementSystem systemBST;
  string inputLine;

  cout << "==================================================\n";
  cout << "      NUMERIC DATA MANAGEMENT SYSTEM (BST)        \n";
  cout << "==================================================\n\n";

  // insert a sequence of numbers
  cout << "Enter a sequence of integers separated by spaces: \n--> ";
  getline(cin, inputLine);

  stringstream ss(inputLine);
  int number;
  while (ss >> number) {
    systemBST.insertVal(number);
  }

  // display the bst
  cout << "\n--------------------------------------------------\n";
  cout << "                TREE TRAVERSAL REPORTS             \n";
  cout << "--------------------------------------------------\n";

  cout << "Inorder Traversal (Sorted Data): \n   ";
  systemBST.displayInorder();

  cout << "\nPreorder Traversal (Structural View): \n   ";
  systemBST.displayPreorder();

  cout << "\nPostorder Traversal (Cleanup Order): \n   ";
  systemBST.displayPostorder();
  cout << "--------------------------------------------------\n\n";

  // delete a node functionality
  char deleteChoice;
  cout << "Would you like to delete any keys from the BST? (y/n): ";
  cin >> deleteChoice;

  while (deleteChoice == 'y' || deleteChoice == 'Y') {
    int deleteKey;
    cout << "Enter the numeric key to delete: ";
    cin >> deleteKey;

    systemBST.deleteVal(deleteKey);
    cout << ">> Node processed. Updated Inorder Traversal: \n   ";
    systemBST.displayInorder();

    cout << "\nDelete another key? (y/n): ";
    cin >> deleteChoice;
  }
  cout << endl;

  // search for a key
  char choice;
  do {
    int searchKey;
    cout << "Enter a numeric key to look up in the database: ";
    cin >> searchKey;

    if (systemBST.searchVal(searchKey)) {
      cout << ">> Result: Key found in BST\n";
    } else {
      cout << ">> Result: Key not found in BST\n";
    }

    cout << "\nWould you like to search for another key? (y/n): ";
    cin >> choice;
    cout << endl;
  } while (choice == 'y' || choice == 'Y');

  cout << "Closing system. Thank you for using the Data Management Tool!\n";
  return 0;
}