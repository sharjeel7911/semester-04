#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *leftChild;
  Node *rightChild;
};
class Tree {
protected:
  Node *root;

public:
  Tree();
  virtual void insert(int value) = 0;
  virtual void inorder() = 0;
  virtual void preorder() = 0;
  virtual void postorder() = 0;
  virtual bool deleteValue(int) = 0;
};

Tree::Tree() { root = nullptr; }

//==============================================================================================

class BST : public Tree {
  void INORDER(Node *p);
  void PREORDER(Node *p);
  void POSTORDER(Node *p);
  void TEST(Node *p);

public:
  void insert(int value);
  void inorder();
  void preorder();
  void postorder();
  void test();
  bool deleteValue(int);
};

bool BST::deleteValue(int value) {
  if (root == nullptr)
    return false;

  else if (root->leftChild == nullptr && root->rightChild == nullptr) {
    if (root->data == value) {
      delete root;
      root = nullptr;
      return true;
    }

    else
      return false;
  }

  // else 2 root cases, where either left or right exists, and you have to
  // change the root

  else {
    Node *p = root;
    Node *c = root;

    while (1) {
      if (value < c->data) {
        p = c;
        c = c->leftChild;
      }

      else {
        p = c;
        c = c->rightChild;
      }

      if (c->data == value)
        break;
    }

    cout << endl << endl;
    cout << "p->data = " << p->data << endl;
    cout << "c->data = " << c->data << endl;

    if (c->leftChild != nullptr && c->rightChild != nullptr) {
      cout << " I am inside 2 children case" << endl;
      cout << "The values are not good, first let's create another tree"
           << endl;
      while (1)
        ;
    }

    // leaf case:
    if (c->leftChild == nullptr && c->rightChild == nullptr) {
      if (c->data < p->data) {
        // left child of parent
        delete c;
        c = nullptr;
        p->leftChild = nullptr;
      }

      else {
        // right child of parent
        delete c;
        c = nullptr;
        p->rightChild = nullptr;
      }

      return true;
    }

    else if (c->rightChild != nullptr &&
             c->leftChild == nullptr) // case of 1 of single child
    {
      if (c->data < p->data) {
        // left child of parent
        p->leftChild = c->rightChild;
        delete c;
        c = nullptr;

      }

      else {
        // right child of parent
        p->rightChild = c->rightChild;
        delete c;
        c = nullptr;
      }
      return true;
    }

    else if (c->rightChild == nullptr &&
             c->leftChild != nullptr) // case of 2 of single child
    {
      if (c->data < p->data) {
        // left child of parent
        p->leftChild = c->leftChild;
        delete c;
        c = nullptr;
      }

      else {
        // right child of parent
        p->rightChild = c->leftChild;
        delete c;
        c = nullptr;
      }
      return true;
    }
  }
}

void BST::TEST(Node *p) {
  if (p != nullptr) {
    TEST(p->leftChild); // L
    if (p->data % 2 != 0)
      cout << p->data << endl; // N
    TEST(p->rightChild);       // R
  }
}

void BST::test() {
  if (root == nullptr)
    cout << "Tree is empty" << endl;
  else
    TEST(root);
}

void BST::POSTORDER(Node *p) {
  if (p != nullptr) {
    POSTORDER(p->leftChild);  // L
    POSTORDER(p->rightChild); // R
    cout << p->data << endl;  // N
  }
}

void BST::postorder() {
  if (root == nullptr)
    cout << "Tree is empty" << endl;
  else
    POSTORDER(root);
}

void BST::PREORDER(Node *p) {
  if (p != nullptr) {
    cout << p->data << endl; // N
    PREORDER(p->leftChild);  // L
    PREORDER(p->rightChild); // R
  }
}

void BST::preorder() {
  if (root == nullptr)
    cout << "Tree is empty" << endl;
  else
    PREORDER(root);
}

void BST::INORDER(Node *p) {
  if (p != nullptr) {
    INORDER(p->leftChild);   // L
    cout << p->data << endl; // N
    INORDER(p->rightChild);  // R
  }
}

void BST::inorder() {
  if (root == nullptr)
    cout << "Tree is empty" << endl;
  else
    INORDER(root);
}

void BST::insert(int value) {
  Node *nn = new Node;
  nn->data = value;
  nn->leftChild = nullptr;
  nn->rightChild = nullptr;

  if (root == nullptr)
    root = nn;

  else {
    Node *p = root;
    while (1) {
      if (value < p->data) // left side
      {
        if (p->leftChild == nullptr) {
          // insert at left;
          p->leftChild = nn;
          break;
        }

        p = p->leftChild;

      }

      else // right side
      {
        if (p->rightChild == nullptr) {
          // insert at right;
          p->rightChild = nn;
          break;
        }

        p = p->rightChild;
      }
    }
  }
}