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

class BinarySearchTree {
private:
  Node *root1;
  Node *root2;

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

  void inorder(Node *node) {
    if (node == nullptr)
      return;
    inorder(node->leftChild);
    cout << node->data << " ";
    inorder(node->rightChild);
  }

  bool isIdentical(Node *root1, Node *root2) {
    if (root1 == nullptr && root2 == nullptr) {
      return true;
    }

    if (root1 == nullptr || root2 == nullptr) {
      return false;
    }

    return (root1->data == root2->data) &&
           isIdentical(root1->leftChild, root2->leftChild) &&
           isIdentical(root1->rightChild, root2->rightChild);
  }

  void clear(Node *node) {
    if (node == nullptr)
      return;
    clear(node->leftChild);
    clear(node->rightChild);
    delete node;
  }

public:
  BinarySearchTree() : root1(nullptr), root2(nullptr) {}

  ~BinarySearchTree() {
    clear(root1);
    clear(root2);
    root1 = nullptr;
    root2 = nullptr;
  }

  void insertTree1(int val) { root1 = insertVal(root1, val); }
  void insertTree2(int val) { root2 = insertVal(root2, val); }

  void displayInorderTree1() {
    inorder(root1);
    cout << endl;
  }
  void displayInorderTree2() {
    inorder(root2);
    cout << endl;
  }

  bool checkIdentical() { return isIdentical(root1, root2); }
};

int main() {
  BinarySearchTree bst;
  string inputLine1, inputLine2;

  cout << "==================================================\n";
  cout << "       BST STRUCTURAL IDENTICALITY CHECKER        \n";
  cout << "==================================================\n\n";

  // build Tree 1
  cout << "Enter values for Binary Search Tree 1 (separated by spaces):\n--> ";
  getline(cin, inputLine1);
  stringstream ss1(inputLine1);
  int number;
  while (ss1 >> number) {
    bst.insertTree1(number);
  }

  // build Tree 2
  cout
      << "\nEnter values for Binary Search Tree 2 (separated by spaces):\n--> ";
  getline(cin, inputLine2);
  stringstream ss2(inputLine2);
  while (ss2 >> number) {
    bst.insertTree2(number);
  }

  // display both bst
  cout << "\n--------------------------------------------------\n";
  cout << "                  INORDER REPORT            \n";
  cout << "--------------------------------------------------\n";
  cout << "Tree 1 Inorder Sorted: ";
  bst.displayInorderTree1();
  cout << "Tree 2 Inorder Sorted: ";
  bst.displayInorderTree2();
  cout << "--------------------------------------------------\n\n";

  // display the message
  cout << ">> Running deep recursive analysis...\n";
  if (bst.checkIdentical()) {
    cout << ">> Result: The two BSTs are IDENTICAL (Structure & Values "
            "Match).\n";
  } else {
    cout << ">> Result: The two BSTs are NOT IDENTICAL (Shape or Data "
            "Mismatch).\n";
  }

  cout << "\nClosing validation system. Memory successfully cleared.\n";
  return 0;
}