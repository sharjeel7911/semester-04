#include <iostream>
using namespace std;

struct TowerNode {
  char data;
  TowerNode *leftChild;
  TowerNode *rightChild;

  TowerNode(char val) : data(val), leftChild(nullptr), rightChild(nullptr) {}
};

class CommunicationNetwork {
private:
  TowerNode *root;

  // find vulnerable towers (non-leaf nodes)
  void displayVulnerableTowers(TowerNode *node) {
    if (node == nullptr) {
      return;
    }
    // if it has at least one child, its failure disconnects a region
    if (node->leftChild != nullptr || node->rightChild != nullptr) {
      cout << node->data << " ";
    }
    displayVulnerableTowers(node->leftChild);
    displayVulnerableTowers(node->rightChild);
  }

  // find all possible routes from HQ to local towers
  void displayRoutes(TowerNode *node, char path[], int pathLen,
                     char longestPath[], int &maxLen) {
    if (node == nullptr) {
      return;
    }

    // add current node to the path
    path[pathLen] = node->data;
    pathLen++;

    // if it is a leaf node (local tower), print the complete route
    if (node->leftChild == nullptr && node->rightChild == nullptr) {
      for (int i = 0; i < pathLen; i++) {
        cout << path[i] << (i == pathLen - 1 ? "" : " ");
      }
      cout << endl;

      // track the longest path found so far
      if (pathLen > maxLen) {
        maxLen = pathLen;
        for (int i = 0; i < pathLen; i++) {
          longestPath[i] = path[i];
        }
      }
      return;
    }

    displayRoutes(node->leftChild, path, pathLen, longestPath, maxLen);
    displayRoutes(node->rightChild, path, pathLen, longestPath, maxLen);
  }

  // calculate height of a given sub-tree node
  int getHeight(TowerNode *node) {
    if (node == nullptr) {
      return 0;
    }
    int leftHeight = getHeight(node->leftChild);
    int rightHeight = getHeight(node->rightChild);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
  }

  // level-order density counter using raw recursive level scanning
  int countTowerNodesAtLevel(TowerNode *node, int targetLevel,
                             int currentLevel) {
    if (node == nullptr) {
      return 0;
    }
    if (currentLevel == targetLevel) {
      return 1;
    }
    return countTowerNodesAtLevel(node->leftChild, targetLevel,
                                  currentLevel + 1) +
           countTowerNodesAtLevel(node->rightChild, targetLevel,
                                  currentLevel + 1);
  }

  // kocate a specific node safely
  TowerNode *findTowerNode(TowerNode *node, char val) {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->data == val) {
      return node;
    }
    TowerNode *leftSearch = findTowerNode(node->leftChild, val);
    if (leftSearch != nullptr) {
      return leftSearch;
    }
    return findTowerNode(node->rightChild, val);
  }

  // preorder printing sequence for the isolated region
  void preorder(TowerNode *node) {
    if (node == nullptr) {
      return;
    }
    cout << node->data << " ";
    preorder(node->leftChild);
    preorder(node->rightChild);
  }

  // safely deallocate dynamic allocations
  void clear(TowerNode *node) {
    if (node == nullptr) {
      return;
    }
    clear(node->leftChild);
    clear(node->rightChild);
    delete node;
  }

public:
  CommunicationNetwork() : root(nullptr) {}

  ~CommunicationNetwork() {
    clear(root);
    root = nullptr;
  }

  void buildSampleNetwork() {
    root = new TowerNode('A');
    root->leftChild = new TowerNode('B');
    root->rightChild = new TowerNode('C');

    root->leftChild->leftChild = new TowerNode('D');
    root->leftChild->rightChild = new TowerNode('E');

    root->rightChild->leftChild = new TowerNode('F');
    root->rightChild->rightChild = new TowerNode('G');

    root->leftChild->rightChild->leftChild = new TowerNode('H');
    root->leftChild->rightChild->rightChild = new TowerNode('I');
  }

  // identify vulnerable points
  void displayVulnerableTowers() {
    cout << "Vulnerable Towers:\n";
    displayVulnerableTowers(root);
    cout << "\n\n";
  }

  // path calculations
  void displayRoutesAndLongestChain() {
    char path[100];
    char longestPath[100];
    int maxLen = 0;

    cout << "Communication Routes:\n";
    displayRoutes(root, path, 0, longestPath, maxLen);
    cout << "\n";

    cout << "Longest Communication Chain:\n";
    for (int i = 0; i < maxLen; i++) {
      cout << longestPath[i] << (i == maxLen - 1 ? "" : " ");
    }
    cout << "\n\n";
  }

  // calculate maximum capacity level using tree height iterations
  void displayMaxTowersLevel() {
    int totalHeight = getHeight(root);
    int maxTowers = 0;
    int targetLevel = 0;

    for (int i = 0; i <totalHeight; i++) {
      int currentLevelCount = countTowerNodesAtLevel(root, i, 0);
      if (currentLevelCount > maxTowers) {
        maxTowers = currentLevelCount;
        targetLevel = i;
      }
    }
    cout << "Level with Maximum Towers = " << targetLevel << " (" << maxTowers << " towers)\n\n";
  }

  // track down the isolation cluster sequence
  void displayIsolatedRegion(char failedTowerId) {
    cout << "Tower Failed: " << failedTowerId << "\n";
    cout << "Isolated Communication Region:\n";

    TowerNode *failedTowerNode = findTowerNode(root, failedTowerId);
    if (failedTowerNode != nullptr) {
      preorder(failedTowerNode);
    }
    cout << "\n";
  }
};

int main() {
  CommunicationNetwork net;

  net.buildSampleNetwork();
  net.displayVulnerableTowers();
  net.displayRoutesAndLongestChain();
  net.displayMaxTowersLevel();
  net.displayIsolatedRegion('E');

  return 0;
}