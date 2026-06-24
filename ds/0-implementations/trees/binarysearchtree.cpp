#include <iostream>
using namespace std;

struct Node {
  int data;
  Node* leftChild;
  Node* rightChild;

  // constructor
  Node(int val) : data(val), leftChild(nullptr), rightChild(nullptr) {}
};

class BinarySearchTree {
private:
  Node* root;

  // ------------------------------------------

  Node* insertVal(Node* node, int val) {
    if (node == nullptr) {
      return new Node(val);
    }
    if (val < node->data) {
      node->leftChild = insertVal(node->leftChild, val);
    }
    else if (val > node->data) {
      node->rightChild = insertVal(node->rightChild, val);
    }
    return node;
  }
  Node* deleteVal(Node* node, int val) {
    if (node == nullptr) {
      return node;
    }

    if (val < node->data) {
      node->leftChild = deleteVal(node->leftChild, val);
    }
    else if (val > node->data) {
      node->rightChild = deleteVal(node->rightChild, val);
    }

    else {
      // value found
      if (node->leftChild == nullptr) {
        // case 1 & 2: No child or only one child
        Node* temp = node->rightChild;
        delete node;
        return temp;
      }
      else if (node->rightChild == nullptr) {
        Node* temp = node->leftChild;
        delete node;
        return temp;
      }

      // case 3: node has 2 children
      else {
        // find the minimum val in the right subtree and del
        Node* temp = findMin(node->rightChild);
        node->data = temp->data;
        node->rightChild = deleteVal(node->rightChild, temp->data);
      }
    }
    return node;
  }

  // by using dfs
  void preorder(Node* node) {
    // root -> left -> right
    // used to clone or copy a tree
    if (node == nullptr) {
      return;
    }
    cout << node->data << " ";
    preorder(node->leftChild);
    preorder(node->rightChild);
  }
  void inorder(Node* node) {
    // left -> root -> right
    // visits the nodes in ascending (sorted) order
    if (node == nullptr) {
      return;
    }
    inorder(node->leftChild);
    cout << node->data << " ";
    inorder(node->rightChild);
  }
  void postorder(Node* node) {
    // left -> right -> root
    // useful for deletion and memory cleanup
    if (node == nullptr) {
      return;
    }
    postorder(node->leftChild);
    postorder(node->rightChild);
    cout << node->data << " ";
  }

  Node* findMin(Node* node) {
    if (node == nullptr) {
      return node;
    }
    while (node && node->leftChild != nullptr) {
      node = node->leftChild;
    }
    return node;
  }
  Node* findMax(Node* node) {
    if (node == nullptr) {
      return node;
    }
    while (node && node->rightChild != nullptr) {
      node = node->rightChild;
    }
    return node;
  }

  int getHeight(Node* node) {
    // base case
    if (node == nullptr) {
      return 0;
    }

    int leftHeight = getHeight(node->leftChild);
    int rightHeight = getHeight(node->rightChild);

    // take the larger height and add 1 for the current level
    return max(leftHeight, rightHeight) + 1;
  }
  bool searchVal(Node* node, int val) {
    if (node == nullptr) {
      return false;
    }

    if (val == node->data) {
      return true;
    }

    if (val < node->data) {
      return searchVal(node->leftChild, val);
    }
    else {
      return searchVal(node->rightChild, val);
    }
  }
  bool isIdentical(Node* root1, Node* root2) {
    // Base Case 1: Both nodes are empty (Identical)
    if (root1 == nullptr && root2 == nullptr) {
      return true;
    }

    // Base Case 2: One node is empty but the other isn't (Not Identical)
    if (root1 == nullptr || root2 == nullptr) {
      return false;
    }

    // case 3: Both nodes exist. Check current data and recursively check subtrees
    return (root1->data == root2->data) && isIdentical(root1->leftChild, root2->leftChild) && isIdentical(root1->rightChild, root2->rightChild);
  }
  void clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    clear(node->leftChild);
    clear(node->rightChild);
    // delete the current node safely after its children are gone
    // cout << "Deleting node: " << node->data << endl;
    delete node;
  }

  void printTree(const string& padding, const string& edge, Node* node, bool hasLeftSibling) {
    if (node != nullptr) {
      cout << endl << padding << edge << node->data;

      // if the current node is a leaf
      if ((node->leftChild == nullptr) && (node->rightChild == nullptr)) {
        cout << endl << padding;
        if (hasLeftSibling) {
          cout << "|";
        }
      }
      else {
        // if the current node is not a leaf, extend the spacing
        string newPadding = padding + (hasLeftSibling ? "|    " : "     ");

        // process right side first (prints higher up on the screen)
        printTree(newPadding, "|----", node->rightChild,
                  node->leftChild != nullptr);

        // process left side second (prints lower down on the screen)
        printTree(newPadding, "|____", node->leftChild, false);
      }
    }
  }

public:
  BinarySearchTree() : root(nullptr) {}
  ~BinarySearchTree() {
    clear(root);
    root = nullptr;
  }

  void insertVal(int val) { root = insertVal(root, val); }
  void deleteVal(int val) { root = deleteVal(root, val); }

  void preorder() {
    preorder(root);
    cout << endl;
  }
  void inorder() {
    inorder(root);
    cout << endl;
  }
  void postorder() {
    postorder(root);
    cout << endl;
  }

  int findMin() {
    if (root == nullptr) {
      cout << "Empty tree" << endl;
      return -99;
    }
    Node* temp = findMin(root);
    return temp->data;
  }
  int findMax() {
    if (root == nullptr) {
      cout << "Empty tree" << endl;
      return -99;
    }
    Node* temp = findMax(root);
    return temp->data;
  }

  int getHeight() { return getHeight(root); }
  bool searchVal(int val) { return searchVal(root, val); }
  bool isIdentical(const BinarySearchTree& otherTree) {
    return isIdentical(this->root, otherTree.root);
  }
  bool isEmpty() { return root == nullptr; }

  void printTree() {
    if (root == nullptr) {
      cout << "Empty tree" << endl;
      return;
    }

    cout << root->data;
    printTree("", "|----", root->rightChild, root->leftChild != nullptr);
    printTree("", "|____", root->leftChild, false);
    cout << endl;
  }
};

int main() {
  BinarySearchTree bst;

  bst.insertVal(89);
  bst.insertVal(90);

  bst.insertVal(100);
  bst.insertVal(-98);
  bst.insertVal(6);
  bst.insertVal(1000);
  bst.insertVal(7);
  bst.insertVal(-199);

  bst.printTree();

  return 0;
}