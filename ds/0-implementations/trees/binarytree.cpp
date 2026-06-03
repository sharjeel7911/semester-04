// #include <iostream>
// using namespace std;

// // struct Node {
// //   int data;
// //   Node *leftChild;
// //   Node *rightChild;

// //   Node(int val) : data(val), leftChild(nullptr), rightChild(nullptr) {}
// // };

// // class BinaryTree {
// // private:
// //   Node *root;

// // public:
// //   BinaryTree() : root(nullptr) {}

// //   ~BinaryTree();

// //   void insertVal(int val) {
// //     Node *newNode = new Node(val);
// //     if (root == nullptr) {
// //       root = newNode;
// //       return;
// //     }
// //   }

// //   bool search(int);

// //   void preorder();
// //   void inorder();
// //   void postorder();
// //   void levelOrder();

// //   int height();

// //   int countNodes();
// //   int countLeaves();

// //   bool isEmpty();
// // };

// // -----------------------------------------------

// #include <iostream>
// #include <queue>

// using namespace std;

// struct Node {
//   int data;
//   Node *leftChild;
//   Node *rightChild;

//   // constructor
//   Node(int val) : data(val), leftChild(nullptr), rightChild(nullptr) {}
// };

// class BinaryTree {
// private:
//   Node *root;

//   // ------------------------------------------

//   Node *insertVal(Node *node, int val) {
//     if (node == nullptr) {
//       return new Node(val);
//     }

//     // Level-order insertion to maintain a complete binary tree
//     queue<Node *> q;
//     q.push(node);

//     while (!q.empty()) {
//       Node *current = q.front();
//       q.pop();

//       if (current->leftChild == nullptr) {
//         current->leftChild = new Node(val);
//         return root;
//       } else {
//         q.push(current->leftChild);
//       }

//       if (current->rightChild == nullptr) {
//         current->rightChild = new Node(val);
//         return root;
//       } else {
//         q.push(current->rightChild);
//       }
//     }
//     return root;
//   }

//   Node *deleteVal(Node *node, int val) {
//     if (node == nullptr) {
//       return node;
//     }

//     // Find the node to delete using level-order traversal
//     queue<Node *> q;
//     q.push(node);

//     Node *targetNode = nullptr;
//     Node *parentNode = nullptr;

//     while (!q.empty()) {
//       Node *current = q.front();
//       q.pop();
//       if (current->data == val) {
//         targetNode = current;
//         break;
//       }

//       if (current->leftChild != nullptr) {
//         q.push(current->leftChild);
//       }

//       if (current->rightChild != nullptr) {
//         q.push(current->rightChild);
//       }
//     }

//     if (targetNode == nullptr) {
//       return node;
//     }

//     // Find the deepest rightmost node
//     queue<Node *> q2;
//     q2.push(node);

//     Node *lastNode = nullptr;

//     while (!q2.empty()) {
//       lastNode = q2.front();
//       q2.pop();

//       if (lastNode->leftChild != nullptr) {
//         q2.push(lastNode->leftChild);
//       }

//       if (lastNode->rightChild != nullptr) {
//         q2.push(lastNode->rightChild);
//       }
//     }

//     // Replace target node data with last node data and delete last node
//     targetNode->data = lastNode->data;
//     deleteDeepest(node, lastNode);
//     return node;
//   }

//   void deleteDeepest(Node *node, Node *targetNode) {
//     if (node == nullptr) {
//       return;
//     }

//     queue<Node *> q;

//     q.push(node);

//     while (!q.empty()) {

//       Node *current = q.front();

//       q.pop();

//       if (current->leftChild == targetNode) {

//         delete current->leftChild;

//         current->leftChild = nullptr;

//         return;
//       }

//       if (current->rightChild == targetNode) {

//         delete current->rightChild;

//         current->rightChild = nullptr;

//         return;
//       }

//       if (current->leftChild != nullptr) {

//         q.push(current->leftChild);
//       }

//       if (current->rightChild != nullptr) {

//         q.push(current->rightChild);
//       }
//     }
//   }

//   // by using dfs

//   void preorder(Node *node) {

//     // root -> left -> right

//     // used to clone or copy a tree

//     if (node == nullptr) {

//       return;
//     }

//     cout << node->data << " ";

//     preorder(node->leftChild);

//     preorder(node->rightChild);
//   }

//   void inorder(Node *node) {

//     // left -> root -> right

//     if (node == nullptr) {

//       return;
//     }

//     inorder(node->leftChild);

//     cout << node->data << " ";

//     inorder(node->rightChild);
//   }

//   void postorder(Node *node) {

//     // left -> right -> root

//     // useful for deletion and memory cleanup

//     if (node == nullptr) {

//       return;
//     }

//     postorder(node->leftChild);

//     postorder(node->rightChild);

//     cout << node->data << " ";
//   }

//   void levelorder(Node *node) {

//     // level by level traversal (breadth-first)

//     if (node == nullptr) {

//       return;
//     }

//     queue<Node *> q;

//     q.push(node);

//     while (!q.empty()) {

//       Node *current = q.front();

//       q.pop();

//       cout << current->data << " ";

//       if (current->leftChild != nullptr) {

//         q.push(current->leftChild);
//       }

//       if (current->rightChild != nullptr) {

//         q.push(current->rightChild);
//       }
//     }
//   }

//   int getHeight(Node *node) {

//     // base case

//     if (node == nullptr) {

//       return 0;
//     }

//     int leftHeight = getHeight(node->leftChild);

//     int rightHeight = getHeight(node->rightChild);

//     // take the larger height and add 1 for the current level

//     return max(leftHeight, rightHeight) + 1;
//   }

//   bool searchVal(Node *node, int val) {

//     if (node == nullptr) {

//       return false;
//     }

//     if (val == node->data) {

//       return true;
//     }

//     return searchVal(node->leftChild, val) ||

//            searchVal(node->rightChild, val);
//   }

//   bool isIdentical(Node *root1, Node *root2) {

//     // Base Case 1: Both nodes are empty (Identical)

//     if (root1 == nullptr && root2 == nullptr) {

//       return true;
//     }

//     // Base Case 2: One node is empty but the other isn't (Not Identical)

//     if (root1 == nullptr || root2 == nullptr) {

//       return false;
//     }

//     // Case 3: Both nodes exist. Check current data and recursively check

//     // subtrees

//     return (root1->data == root2->data) &&

//            isIdentical(root1->leftChild, root2->leftChild) &&

//            isIdentical(root1->rightChild, root2->rightChild);
//   }

//   void clear(Node *node) {

//     if (node == nullptr) {

//       return;
//     }

//     clear(node->leftChild);

//     clear(node->rightChild);

//     // delete the current node safely after its children are gone

//     // cout << "Deleting node: " << node->data << endl;

//     delete node;
//   }

//   void printTree(const string &padding, const string &edge, Node *node,

//                  bool hasLeftSibling) {

//     if (node != nullptr) {

//       cout << endl << padding << edge << node->data;

//       // if the current node is a leaf

//       if ((node->leftChild == nullptr) && (node->rightChild == nullptr)) {

//         cout << endl << padding;

//         if (hasLeftSibling) {

//           cout << "|";
//         }

//       } else {

//         // if the current node is not a leaf, extend the spacing

//         string newPadding = padding + (hasLeftSibling ? "|    " : "     ");

//         // process right side first (prints higher up on the screen)

//         printTree(newPadding, "|----", node->rightChild,

//                   node->leftChild != nullptr);

//         // process left side second (prints lower down on the screen)

//         printTree(newPadding, "|____", node->leftChild, false);
//       }
//     }
//   }

// public:
//   BinaryTree() : root(nullptr) {}

//   ~BinaryTree() {

//     clear(root);

//     root = nullptr;
//   }

//   void insertVal(int val) {

//     if (root == nullptr) {

//       root = new Node(val);

//     } else {

//       insertVal(root, val);
//     }
//   }

//   void deleteVal(int val) { root = deleteVal(root, val); }

//   void preorder() {

//     preorder(root);

//     cout << endl;
//   }

//   void inorder() {

//     inorder(root);

//     cout << endl;
//   }

//   void postorder() {

//     postorder(root);

//     cout << endl;
//   }

//   void levelorder() {

//     levelorder(root);

//     cout << endl;
//   }

//   int getHeight() { return getHeight(root); }

//   bool searchVal(int val) { return searchVal(root, val); }

//   bool isIdentical(const BinaryTree &otherTree) {

//     return isIdentical(this->root, otherTree.root);
//   }

//   bool isEmpty() { return root == nullptr; }

//   void printTree() {

//     if (root == nullptr) {

//       cout << "Empty tree" << endl;

//       return;
//     }

//     cout << root->data;

//     printTree("", "|----", root->rightChild, root->leftChild != nullptr);

//     printTree("", "|____", root->leftChild, false);

//     cout << endl;
//   }
// };

// int main() {

//   BinaryTree bt;

//   bt.insertVal(89);
//   bt.insertVal(90);
//   bt.insertVal(100);
//   bt.insertVal(-98);
//   bt.insertVal(6);
//   bt.insertVal(1000);
//   bt.insertVal(7);
//   bt.insertVal(-199);

//   bt.printTree();

//   cout << "Preorder: ";

//   bt.preorder();

//   cout << "Levelorder: ";

//   bt.levelorder();

//   return 0;
// }

#include <iostream>
using namespace std;
struct Node {
  int data;
  Node *left;
  Node *right;

  Node(int value) {
    data = value;
    left = nullptr;
    right = nullptr;
  }
};

// Function to create binary tree from array
Node *createTree(int arr[], int n, int i) {
  // Base condition
  if (i >= n)
    return nullptr;
  // Create node
  Node *root = new Node(arr[i]);
  // Create left child
  root->left = createTree(arr, n, 2 * i + 1);
  // Create right child
  root->right = createTree(arr, n, 2 * i + 2);
  return root;
}
// Preorder Traversal
void preorder(Node *root) {
  if (root == nullptr)
    return;
  cout << root->data << " ";
  preorder(root->left);
  preorder(root->right);
}

// Inorder Traversal
void inorder(Node *root) {
  if (root == nullptr)
    return;
  inorder(root->left);
  cout << root->data << " ";
  inorder(root->right);
}

// Postorder Traversal
void postorder(Node *root) {
  if (root == nullptr)
    return;
  postorder(root->left);
  postorder(root->right);
  cout << root->data << " ";
}
int main() {
  int arr[] = {10, 20, 30, 40, 50};
  int n = 5;
  // Create tree
  Node *root = createTree(arr, n, 0);
  cout << "Preorder: ";
  preorder(root);
  cout << "\nInorder: ";
  inorder(root);
  cout << "\nPostorder: ";
  postorder(root);
  return 0;
}