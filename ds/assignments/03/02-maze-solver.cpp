#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
const int MAX = 100;

void readFile(ifstream &file, char maze[MAX][MAX], int &rows, int &cols) {
  string line;
  rows = 0;
  while (getline(file, line) && rows < MAX) {
    cols = line.length();
    for (int i = 0; i < cols; i++) {
      maze[rows][i] = line[i];
    }
    rows++;
  }
}

// using dfs algorithm

bool mazeSolver(char maze[MAX][MAX], int r, int c, int rows, int cols,
                int &calls) {
  calls++;
  if (r < 0 || r >= rows || c < 0 || c >= cols || maze[r][c] == '#' ||
      maze[r][c] == '*') {
    return false;
  }

  if (maze[r][c] == 'D')
    return true;

  if (maze[r][c] == '.') {
    maze[r][c] = '*';
  }

  if (mazeSolver(maze, r, c + 1, rows, cols, calls) ||
      mazeSolver(maze, r, c - 1, rows, cols, calls) ||
      mazeSolver(maze, r + 1, c, rows, cols, calls) ||
      mazeSolver(maze, r - 1, c, rows, cols, calls)) {
    return true;
  }

  maze[r][c] = '.';
  return false;
}

int main() {
  char maze[MAX][MAX];
  int rows = 0, cols = 0, calls = 0;

  ifstream file("maze.txt");
  if (file.is_open()) {
    readFile(file, maze, rows, cols);
    file.close();
  }

  if (mazeSolver(maze, 0, 0, rows, cols, calls)) {
    cout << "Solution found!" << endl;
  } else {
    cout << "No solution found." << endl;
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << maze[i][j] << " ";
    }
    printf("\n");
  }

  cout << "\nTotal Recursive calls: " << calls << endl;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (maze[i][j] == '*') {
        cout << "(" << i << ", " << j << ")";
        if (i == rows - 1) {
        } else {
          printf(", ");
        }
      }
    }
  }
  printf("\n");
  return 0;
}
