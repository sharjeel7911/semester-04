#include <iostream>
#include <unordered_set>
using std::cout;
using std::endl;
using std::unordered_set;

// ----------------------------------------------

struct Node {
  int data;
  Node *next;
  Node *prev;

  Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// find all pairs in a doubly linked list that sum up to specific target
void findTwoSum(Node *head, int target) {
  unordered_set<int> seen;

  Node *curr = head;

  while (curr != nullptr) {
    int num = target - curr->data;

    if (seen.find(num) != seen.end()) {
      cout << "(" << num << ", " << curr->data << ")" << endl;
      seen.erase(num);
    } else {
      seen.insert(curr->data);
    }
    curr = curr->next;
  }
}

// ----------------------------------------------

// print stars one by one in recursive manner
void printStars(int n) {
  if (n == 0)
    return;

  cout << "* ";
  printStars(n - 1);
}

// print star pattern using recursion
void starPattern(int n) {
  if (n == 0)
    return;

  printStars(n);
  cout << endl;
  starPattern(n - 1);
}

// ----------------------------------------------

int main() {

  /*
   * * * * *
   * * * *
   * * *
   * *
   *
   */

  cout << "Star Pattern \n";
  starPattern(5);

  cout << "------------------------------";

  // Input Linked List: [10, -5, 7, -2, 2, 3] with target sum = 5

  Node *head = new Node(10);
  Node *curr = head;
  int arr[] = {-5, 7, -2, 2, 3};

  for (int val : arr) {
    curr->next = new Node(val);
    curr->next->prev = curr;
    curr = curr->next;
  }

  int target = 5;
  cout << "\nPairs that sum to " << target << ":" << endl;

  findTwoSum(head, target);

  return 0;
}

/*

Question # 1: Given a doubly linked list of integers (negative or positive), write a function to
find all pairs of nodes whose values add up to a given sum. Each node can be part of only one
pair. The function should display all such pairs.
Note: The doubly linked list is not circular, but we have both head and tail pointers.
Example 1:
Input Linked List: [1, 2, 3, 4, 5, 6] with target sum = 7
Output: (1, 6), (2, 5), (3, 4)
Example 2:
Input Linked List: [10, -5, 7, -2, 2, 3] with target sum = 5
Output: (10, -5), (7, -2), (2, 3)
Question # 2: Implement the following recursive method. Do not use any local variables or
loops.
void starPattern(int n)
The output consists of lines of asterisks (*).
The first line contains n asterisks.
The following line contains n-1 asterisks.
The following line contains n-2 asterisks, and so on, until you reach 1 asterisk.
Example Output with n = 5
*****
****
***
**
*

*/
