#include <iostream>

#include "Board.h"

using namespace std;

TriangleBoard::TriangleBoard() : IBoard() { reset(); }

void TriangleBoard::reset() {
  for (int i = 0; i < TRIANGLE_SIDE; i++) {
    for (int j = 0; j < TRIANGLE_SIDE - i; j++) {
      board[i][j] = '-';
    }
  }
}

void TriangleBoard::draw() const {
  for (int i = 0; i < TRIANGLE_SIDE; i++) {
    for (int j = 0; j < TRIANGLE_SIDE - i; j++) {
      cout << '|' << board[i][j];
    }
    cout << '|' << endl;
  }
}
