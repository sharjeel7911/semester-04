#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

struct Node {
  int data;
  Node* leftChild;
  Node* rightChild;

  Node(int val) : data(val), leftChild(nullptr), rightChild(nullptr) {}
};

class BinaryTree {
private:
  Node* root;

  // ------------------------------------------

  void preorder(Node* node) {
    if (!node) return;
    cout << node->data << " ";
    preorder(node->leftChild);
    preorder(node->rightChild);
  }

  void inorder(Node* node) {
    if (!node) return;
    inorder(node->leftChild);
    cout << node->data << " ";
    inorder(node->rightChild);
  }

  void postorder(Node* node) {
    if (!node) return;
    postorder(node->leftChild);
    postorder(node->rightChild);
    cout << node->data << " ";
  }

  int getHeight(Node* node) {
    if (node == nullptr) {
      return 0;
    }
    int leftHeight = getHeight(node->leftChild);
    int rightHeight = getHeight(node->rightChild);

    // take the larger height and add 1 for the current level
    return max(leftHeight, rightHeight) + 1;
  }

  bool searchVal(Node* node, int val) {
    if (!node) return false;
    if (node->data == val) return true;
    return searchVal(node->leftChild, val) || searchVal(node->rightChild, val);
  }

  int findMin(Node* node) {
    if (!node) return INT_MAX;
    int nodeVal = node->data;
    int leftVal = findMin(node->leftChild);
    int rightVal = findMin(node->rightChild);
    return  min({ nodeVal, leftVal, rightVal });
  }

  int findMax(Node* node) {
    if (!node) return INT_MIN;
    int nodeVal = node->data;
    int leftVal = findMax(node->leftChild);
    int rightVal = findMax(node->rightChild);
    return  max({ nodeVal, leftVal, rightVal });
  }

  bool isIdentical(Node* root1, Node* root2) {
    if (root1 == nullptr && root2 == nullptr) {
      return true;
    }
    if (root1 == nullptr || root2 == nullptr) {
      return false;
    }
    return (root1->data == root2->data) && isIdentical(root1->leftChild, root2->leftChild) && isIdentical(root1->rightChild, root2->rightChild);
  }

  void clear(Node* node) {
    if (!node) return;
    clear(node->leftChild);
    clear(node->rightChild);
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

  // Helper to delete the deepest rightChildmost node
  void deleteDeepest(Node* deleteNode) {
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
      Node* temp = q.front();
      q.pop();

      if (temp == deleteNode) {
        temp = nullptr;
        delete deleteNode;
        return;
      }
      if (temp->rightChild) {
        if (temp->rightChild == deleteNode) {
          delete temp->rightChild;
          temp->rightChild = nullptr;
          return;
        }
        else q.push(temp->rightChild);
      }
      if (temp->leftChild) {
        if (temp->leftChild == deleteNode) {
          delete temp->leftChild;
          temp->leftChild = nullptr;
          return;
        }
        else q.push(temp->leftChild);
      }
    }
  }

public:
  BinaryTree() : root(nullptr) {}
  ~BinaryTree() { clear(); }

  // 1. Insert (Level-order insertion)
  void insert(int val) {
    Node* newNode = new Node(val);
    if (!root) {
      root = newNode;
      return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
      Node* temp = q.front();
      q.pop();

      if (!temp->leftChild) {
        temp->leftChild = newNode;
        return;
      }
      else q.push(temp->leftChild);

      if (!temp->rightChild) {
        temp->rightChild = newNode;
        return;
      }
      else q.push(temp->rightChild);
    }
  }

  // 2. Delete Node (Replaces target value with deepest node value, then deletes deepest node)
  void deleteNode(int val) {
    if (!root) return;

    if (!root->leftChild && !root->rightChild) {
      if (root->data == val) {
        delete root;
        root = nullptr;
      }
      return;
    }

    queue<Node*> q;
    q.push(root);
    Node* targetNode = nullptr;
    Node* temp = nullptr;

    while (!q.empty()) {
      temp = q.front();
      q.pop();

      if (temp->data == val) targetNode = temp;
      if (temp->leftChild) q.push(temp->leftChild);
      if (temp->rightChild) q.push(temp->rightChild);
    }

    if (targetNode) {
      int deepestVal = temp->data; // 'temp' points to deepest node after BFS ends
      deleteDeepest(temp);
      targetNode->data = deepestVal;
    }
    else {
      cout << "Value " << val << " not found for deletion.\n";
    }
  }

  // 3. Traversal wrappers
  void preorder() { preorder(root);  cout << "\n"; }
  void inorder() { inorder(root);  cout << "\n"; }
  void postorder() { postorder(root);  cout << "\n"; }

  // 4. Utility operations
  int getHeight() { return getHeight(root); }
  bool searchVal(int val) { return searchVal(root, val); }

  int findMin() {
    if (!root) throw  runtime_error("Tree is empty!");
    return findMin(root);
  }

  int findMax() {
    if (!root) throw  runtime_error("Tree is empty!");
    return findMax(root);
  }

  // 5. Compare with another tree
  bool isIdentical(BinaryTree& other) {
    return isIdentical(this->root, other.root);
  }

  // 6. Memory cleanup
  void clear() {
    clear(root);
    root = nullptr;
  }

  // 7. Visual Print (Rotated 90 degrees)
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
  BinaryTree tree1;

  // Populate tree
  tree1.insert(10);
  tree1.insert(20);
  tree1.insert(30);
  tree1.insert(40);
  tree1.insert(5);
  tree1.insert(15);

  cout << "--- Visual Tree Structure ---\n";
  tree1.printTree();

  cout << "Inorder Traversal:   "; tree1.inorder();
  cout << "Preorder Traversal:  "; tree1.preorder();
  cout << "Postorder Traversal: "; tree1.postorder();

  cout << "\nTree Height: " << tree1.getHeight() << "\n";
  cout << "Minimum Value: " << tree1.findMin() << "\n";
  cout << "Maximum Value: " << tree1.findMax() << "\n";
  cout << "Search for 5: " << (tree1.searchVal(5) ? "Found" : "Not Found") << "\n";
  cout << "Search for 100: " << (tree1.searchVal(100) ? "Found" : "Not Found") << "\n";

  // Test Identity check
  BinaryTree tree2;
  tree2.insert(10); tree2.insert(20); tree2.insert(30);
  tree2.insert(40); tree2.insert(5);  tree2.insert(15);
  cout << "Is Tree1 identical to Tree2? " << (tree1.isIdentical(tree2) ? "Yes" : "No") << "\n";

  // Delete elements
  cout << "\nDeleting Node 20...\n";
  tree1.deleteNode(20);
  tree1.printTree();

  return 0;
}