#include <iostream>

struct Node {
  int data;
  Node *leftChild;
  Node *rightChild;

  Node(int val) : data(val), leftChild(nullptr), rightChild(nullptr) {}
};

class BinaryTree {
private:
  Node *root;

public:
  BinaryTree() : root(nullptr) {}

  ~BinaryTree();

  void insertVal(int val) {
    Node *newNode = new Node(val);
    if (root == nullptr) {
      root = newNode;
      return;
    }
  }

  bool search(int);

  void preorder();
  void inorder();
  void postorder();
  void levelOrder();

  int height();

  int countNodes();
  int countLeaves();

  bool isEmpty();
};

// -----------------------------------------------

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <class T> struct Node {
  T data;
  Node<T> *leftChild;
  Node<T> *rightChild;

  Node(T val) : data(val), leftChild(nullptr), rightChild(nullptr) {}
};

//------------------------------------------------------------------------------------------------------------------
// ===== BINARY TREE =====
//------------------------------------------------------------------------------------------------------------------

template <class T> class BinaryTree {
private:
  Node<T> *root;

  // Helper function for recursive insertion
  Node<T> *insertHelper(Node<T> *node, T val) {
    if (node == nullptr) {
      return new Node<T>(val);
    }
    if (val < node->data) {
      node->leftChild = insertHelper(node->leftChild, val);
    } else {
      node->rightChild = insertHelper(node->rightChild, val);
    }
    return node;
  }

  void insert(T val) { root = insertHelper(root, val); }

  // Helper function for deletion
  Node<T> *deleteHelper(Node<T> *node, T val) {
    if (node == nullptr)
      return nullptr;

    if (val < node->data) {
      node->leftChild = deleteHelper(node->leftChild, val);
    } else if (val > node->data) {
      node->rightChild = deleteHelper(node->rightChild, val);
    } else {
      // Node with only one child or no child
      if (node->leftChild == nullptr) {
        Node<T> *temp = node->rightChild;
        delete node;
        return temp;
      } else if (node->rightChild == nullptr) {
        Node<T> *temp = node->leftChild;
        delete node;
        return temp;
      }

      // Node with two children: get the inorder successor
      Node<T> *successor = findMinHelper(node->rightChild);
      node->data = successor->data;
      node->rightChild = deleteHelper(node->rightChild, successor->data);
    }
    return node;
  }

  void deleteNode(T val) {
    if (isEmpty()) {
      cout << "Tree is empty." << endl;
      return;
    }
    if (!search(val)) {
      cout << "Value " << val << " not found." << endl;
      return;
    }
    root = deleteHelper(root, val);
    cout << "Value " << val << " deleted." << endl;
  }

  // Helper function for recursive search
  Node<T> *searchHelper(Node<T> *node, T val) {
    if (node == nullptr)
      return nullptr;
    if (node->data == val)
      return node;
    if (val < node->data)
      return searchHelper(node->leftChild, val);
    return searchHelper(node->rightChild, val);
  }

  // Helper function for inorder traversal
  void inorderHelper(Node<T> *node) {
    if (node == nullptr)
      return;
    inorderHelper(node->leftChild);
    cout << node->data << " ";
    inorderHelper(node->rightChild);
  }

  // Helper function for preorder traversal
  void preorderHelper(Node<T> *node) {
    if (node == nullptr)
      return;
    cout << node->data << " ";
    preorderHelper(node->leftChild);
    preorderHelper(node->rightChild);
  }

  // Helper function for postorder traversal
  void postorderHelper(Node<T> *node) {
    if (node == nullptr)
      return;
    postorderHelper(node->leftChild);
    postorderHelper(node->rightChild);
    cout << node->data << " ";
  }

  // Helper function for getting height
  int getHeightHelper(Node<T> *node) {
    if (node == nullptr)
      return 0;
    return 1 + max(getHeightHelper(node->leftChild),
                   getHeightHelper(node->rightChild));
  }

  // Helper function for counting nodes
  int countNodesHelper(Node<T> *node) {
    if (node == nullptr)
      return 0;
    return 1 + countNodesHelper(node->leftChild) +
           countNodesHelper(node->rightChild);
  }

  // Helper function for finding minimum
  Node<T> *findMinHelper(Node<T> *node) {
    if (node == nullptr)
      return nullptr;
    while (node->leftChild != nullptr) {
      node = node->leftChild;
    }
    return node;
  }

  // Helper function for finding maximum
  Node<T> *findMaxHelper(Node<T> *node) {
    if (node == nullptr)
      return nullptr;
    while (node->rightChild != nullptr) {
      node = node->rightChild;
    }
    return node;
  }

  // Helper function for deleting entire tree
  void deleteTreeHelper(Node<T> *node) {
    if (node == nullptr)
      return;
    deleteTreeHelper(node->leftChild);
    deleteTreeHelper(node->rightChild);
    delete node;
  }

  // Helper function to find LCA
  Node<T> *findLCAHelper(Node<T> *node, T val1, T val2) {
    if (node == nullptr)
      return nullptr;
    if (val1 < node->data && val2 < node->data) {
      return findLCAHelper(node->leftChild, val1, val2);
    }
    if (val1 > node->data && val2 > node->data) {
      return findLCAHelper(node->rightChild, val1, val2);
    }
    return node;
  }

  // Helper function to check if tree is balanced
  pair<bool, int> isBalancedHelper(Node<T> *node) {
    if (node == nullptr)
      return {true, 0};

    auto leftResult = isBalancedHelper(node->leftChild);
    if (!leftResult.first)
      return {false, 0};

    auto rightResult = isBalancedHelper(node->rightChild);
    if (!rightResult.first)
      return {false, 0};

    int heightDiff = abs(leftResult.second - rightResult.second);
    if (heightDiff > 1)
      return {false, 0};

    return {true, 1 + max(leftResult.second, rightResult.second)};
  }

public:
  BinaryTree() : root(nullptr) {}

  ~BinaryTree() { deleteTreeHelper(root); }

  bool isEmpty() { return root == nullptr; }

  bool search(T val) { return searchHelper(root, val) != nullptr; }

  void inorder() {
    if (isEmpty()) {
      cout << "Tree is empty." << endl;
      return;
    }
    cout << "Inorder: ";
    inorderHelper(root);
    cout << endl;
  }

  void preorder() {
    if (isEmpty()) {
      cout << "Tree is empty." << endl;
      return;
    }
    cout << "Preorder: ";
    preorderHelper(root);
    cout << endl;
  }

  void postorder() {
    if (isEmpty()) {
      cout << "Tree is empty." << endl;
      return;
    }
    cout << "Postorder: ";
    postorderHelper(root);
    cout << endl;
  }

  void levelorder() {
    if (isEmpty()) {
      cout << "Tree is empty." << endl;
      return;
    }

    queue<Node<T> *> q;
    q.push(root);
    cout << "Level order: ";

    while (!q.empty()) {
      Node<T> *node = q.front();
      q.pop();
      cout << node->data << " ";

      if (node->leftChild != nullptr)
        q.push(node->leftChild);
      if (node->rightChild != nullptr)
        q.push(node->rightChild);
    }
    cout << endl;
  }

  int getHeight() { return getHeightHelper(root); }

  int countNodes() { return countNodesHelper(root); }

  T findMin() {
    if (isEmpty()) {
      cout << "Tree is empty." << endl;
      return T();
    }
    return findMinHelper(root)->data;
  }

  T findMax() {
    if (isEmpty()) {
      cout << "Tree is empty." << endl;
      return T();
    }
    return findMaxHelper(root)->data;
  }

  T findLCA(T val1, T val2) {
    if (isEmpty()) {
      cout << "Tree is empty." << endl;
      return T();
    }
    if (!search(val1) || !search(val2)) {
      cout << "One or both values not found." << endl;
      return T();
    }
    Node<T> *lca = findLCAHelper(root, val1, val2);
    return lca->data;
  }

  bool isBalanced() { return isBalancedHelper(root).first; }

  void displayTreeStructure() {
    if (isEmpty()) {
      cout << "Tree is empty." << endl;
      return;
    }
    cout << "\nTree Structure (Level Order with indentation):" << endl;
    queue<pair<Node<T> *, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
      auto [node, level] = q.front();
      q.pop();

      for (int i = 0; i < level * 4; i++)
        cout << " ";
      cout << node->data << endl;

      if (node->leftChild != nullptr)
        q.push({node->leftChild, level + 1});
      if (node->rightChild != nullptr)
        q.push({node->rightChild, level + 1});
    }
  }
};
