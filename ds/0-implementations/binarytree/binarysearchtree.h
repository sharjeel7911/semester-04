#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *leftChild;
  Node *rightChild;

  // constructor
  Node(int val) : data(val), leftChild(nullptr), rightChild(nullptr) {}
};

class BinarySearchTree {
private:
  Node *root;

  Node *insertVal(Node *node, int val) {
    if (node == nullptr) {
      return new Node(val);
    }
    if (val < node->data) {
      node->leftChild = insertVal(node->leftChild, val);
    } else if (val > node->data) {
      node->rightChild = insertVal(node->rightChild, val);
    }
    return node;
  }

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
      // Step 2: Value found! Handle deletion
      if (node->leftChild == nullptr) {
        // FOR ONLY 1 NODE IN TREE temp is assigned nullptr
        // Case 1 & Case 2: No child or only one child
        Node *temp = node->rightChild;
        delete node;
        return temp;
      } else if (node->rightChild == nullptr) {
        Node *temp = node->leftChild;
        delete node;
        return temp;
      }

      else {
        // Case 3: Node has TWO children
        // Find the absolute minimum node in the right subtree

        Node *temp = findMin(node->rightChild);

        // Replace current node's data with the successor's data
        node->data = temp->data;

        // Recursively delete the successor from the right subtree
        node->rightChild = deleteVal(node->rightChild, temp->data);
      }
    }

    return node;
  }

  Node *findMin(Node *node) {
    if (node == nullptr) {
      return nullptr;
    }
    while (node && node->leftChild != nullptr) {
      node = node->leftChild;
    }
    return node;
  }

  Node *findMax(Node *node) {
    while (node && node->rightChild != nullptr) {
      node = node->rightChild;
    }
    return node;
  }

  // dfs
  void preorder(Node *node) {
    // Root -> Left -> Right
    // used to clone or copy a tree
    if (node == nullptr) {
      return;
    }
    cout << node->data << " ";
    preorder(node->leftChild);
    preorder(node->rightChild);
  }
  void inorder(Node *node) {
    // Left -> Root -> Right
    // visits the nodes in ascending (sorted) order
    if (node == nullptr) {
      return;
    }
    inorder(node->leftChild);
    cout << node->data << " ";
    inorder(node->rightChild);
  }
  void postorder(Node *node) {
    // Left -> Right -> Root
    // useful for deletion and memory cleanup (like the clear()
    if (node == nullptr) {
      return;
    }
    postorder(node->leftChild);
    postorder(node->rightChild);
    cout << node->data << " ";
  }

  bool searchVal(Node *node, int val) {
    if (node == nullptr) {
      return false; // Not found
    }

    if (val == node->data) {
      return true; // Found!
    }

    if (val < node->data) {
      return searchVal(node->leftChild, val);
    } else {
      return searchVal(node->rightChild, val);
    }
  }

  int getHeight(Node *node) {
    if (node == nullptr) {
      // Base case: empty tree has height -1 (or 0 depending on definition)
      return 0;
    }

    int leftHeight = getHeight(node->leftChild);
    int rightHeight = getHeight(node->rightChild);

    // Take the larger height and add 1 for the current level
    return max(leftHeight, rightHeight) + 1;
  }

  void clear(Node *node) {
    if (node == nullptr) {
      return; // Base case: nothing to delete
    }

    // 1. Go down the left branch completely
    clear(node->leftChild);
    // 2. Go down the right branch completely
    clear(node->rightChild);
    // 3. Delete the current node safely after its children are gone
    // std::cout << "Deleting node: " << node->data << std::endl; // Optional
    // debug line
    delete node;
  }

  bool isIdentical(Node *root1, Node *root2) {
    // Base Case 1: Both nodes are empty (Identical)
    if (root1 == nullptr && root2 == nullptr) {
      return true;
    }

    // Base Case 2: One node is empty but the other isn't (Not Identical)
    if (root1 == nullptr || root2 == nullptr) {
      return false;
    }

    // Case 3: Both nodes exist. Check current data and recursively check
    // subtrees
    return (root1->data == root2->data) &&
           isIdentical(root1->leftChild, root2->leftChild) &&
           isIdentical(root1->rightChild, root2->rightChild);
  }

  // Utility function to separately print nodes other than the root(
  // recursively)
  void printNodes(const string &padding, const string &edge, Node *node,
                  bool hasLeftSibling) {
    if (node != nullptr) {
      cout << endl << padding << edge << node->data;

      // If the current node is a leaf
      if ((node->leftChild == nullptr) && (node->rightChild == nullptr)) {
        cout << endl << padding;
        if (hasLeftSibling) {
          cout << "|";
        }
      } else {
        // If the current node is not a leaf, extend the spacing
        string newPadding = padding + (hasLeftSibling ? "|    " : "     ");

        // Process right side first (prints higher up on the screen)
        printNodes(newPadding, "|----", node->rightChild,
                   node->leftChild != nullptr);

        // Process left side second (prints lower down on the screen)
        printNodes(newPadding, "|____", node->leftChild, false);
      }
    }
  }

public:
  BinarySearchTree() : root(nullptr) {}
  ~BinarySearchTree() {
    clear(root);    // Passes the root to start the clean-up process
    root = nullptr; // Good practice to avoid a dangling pointer
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
    Node *temp = findMin(root);
    return temp->data;
  }

  int findMax() {
    if (root == nullptr) {
      cout << "Empty tree" << endl;
      return -99;
    }
    Node *temp = findMax(root);
    return temp->data;
  }

  bool searchVal(int val) { return searchVal(root, val); }
  bool isEmpty() { return root == nullptr; }
  int getHeight() { return getHeight(root); }

  bool isIdentical(const BinarySearchTree &otherTree) {
    return isIdentical(this->root, otherTree.root);
  }

  void printTree() {
    if (root == nullptr) {
      cout << "Empty tree" << endl;
      return;
    }

    cout << root->data;
    printNodes("", "|----", root->rightChild, root->leftChild != nullptr);
    printNodes("", "|____", root->leftChild, false);
    cout << endl;
  }
};

/*
        private:
    void printNodesPreorder(const string &padding, const string &edge, Node
*node, bool hasRightSibling) { if (node != nullptr) { cout << endl << padding <<
edge << node->data;

            if ((node->leftChild == nullptr) && (node->rightChild == nullptr)) {
                cout << endl << padding;
                if (hasRightSibling) cout << "|";
            } else {
                string newPadding = padding + (hasRightSibling ? "|    " : " ");

                // 1. Process Left child first (Prints on TOP)
                printNodesPreorder(newPadding, "|----", node->leftChild,
node->rightChild != nullptr);

                // 2. Process Right child second (Prints on BOTTOM)
                printNodesPreorder(newPadding, "|____", node->rightChild,
false);
            }
        }
    }

public:
    void printTreePreorder() {
        if (root == nullptr) return;
        cout << root->data;
        printNodesPreorder("", "|----", root->leftChild, root->rightChild !=
nullptr); printNodesPreorder("", "|____", root->rightChild, false); cout <<
endl;
    }





    private:
        void printNodesInorder(const string &padding, Node *node, bool isLeft) {
            if (node != nullptr) {
                // 1. Traverse Left Subtree completely first (Top of screen)
                printNodesInorder(padding + (isLeft ? "     " : "|    "),
node->leftChild, true);

                // 2. Process Current Node
                cout << padding << (isLeft ? "┌___ " : "└--- ") << node->data <<
endl;

                // 3. Traverse Right Subtree completely last (Bottom of screen)
                printNodesInorder(padding + (isLeft ? "|    " : "     "),
node->rightChild, false);
            }
        }

    public:
        void printTreeInorder() {
            if (root == nullptr) return;
            // Start processing the root in the middle layout
            printNodesInorder("", root->leftChild, true);
            cout << root->data << " (Root)" << endl;
            printNodesInorder("", root->rightChild, false);
        }





        private:
            void printNodesPostorder(const string &padding, const string &edge,
Node *node, bool hasSiblings) { if (node != nullptr) { if ((node->leftChild !=
nullptr) || (node->rightChild != nullptr)) { string newPadding = padding +
(hasSiblings ? "|    " : "     ");
                        // 1. Process Left Subtree
                        printNodesPostorder(newPadding, "|----",
node->leftChild, node->rightChild != nullptr);
                        // 2. Process Right Subtree
                        printNodesPostorder(newPadding, "|____",
node->rightChild, false);
                    }

                    // 3. Process Current Node Last
                    cout << endl << padding << edge << node->data;
                }
            }

        public:
            void printTreePostorder() {
                if (root == nullptr) return;
                printNodesPostorder("", "|----", root->leftChild,
root->rightChild != nullptr); printNodesPostorder("", "|____", root->rightChild,
false); cout << endl << root->data << " (Root)" << endl;
            }
        */
