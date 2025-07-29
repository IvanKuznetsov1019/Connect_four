#include "TriangleBoard.h"

#include <iostream>

using namespace std;

TriangleBoard::TriangleBoard() : IBoard() { reset(); }

void TriangleBoard::reset() {
  for (int i = 0; i < TRIANGLE_SIDE; i++) {
    for (int j = 0; j < TRIANGLE_SIDE; j++) {
      board[i][j] = (j <= i) ? '-' : '#';
    }
  }
}

void TriangleBoard::draw() const {
  for (int i = 0; i < TRIANGLE_SIDE; i++) {
    for (int j = 0; j < TRIANGLE_SIDE; j++) {
      cout << '|' << board[i][j];
    }
    cout << '|' << endl;
  }
}

bool TriangleBoard::isFull() const {
  for (int i = 0; i < TRIANGLE_SIDE; i++) {
    if (board[i][i] == '-') {
      return false;
    }
  }
  return true;
}

bool TriangleBoard::placeChip(const int columnIndex, const char symbol) {
  int rowIndex;
  for (rowIndex = TRIANGLE_SIDE - 1; rowIndex >= 0; rowIndex--) {
    if (board[rowIndex][columnIndex] == '-') {
      break;
    }
  }
  if (rowIndex < 0) {
    return false;
  }
  board[rowIndex][columnIndex] = symbol;
  return true;
}

bool TriangleBoard::isWin(const int columnIndex) const {
  char c = '-';
  int rowIndex;
  for (rowIndex = 0; rowIndex < TRIANGLE_SIDE; rowIndex++) {
    if (board[rowIndex][columnIndex] != '-' &&
        board[rowIndex][columnIndex] != '#') {
      c = board[rowIndex][columnIndex];
      break;
    }
  }

  int scoreCount = 0;
  for (const char& cell : board[rowIndex]) {
    if (cell == c) {
      scoreCount++;
      if (scoreCount == WIN_SCORE) {
        return true;
      }
    } else {
      scoreCount = 0;
    }
  }

  scoreCount = 0;
  for (int i = rowIndex; i < TRIANGLE_SIDE; i++) {
    if (board[i][columnIndex] == c) {
      scoreCount++;
      if (scoreCount == WIN_SCORE) {
        return true;
      }
    } else {
      scoreCount = 0;
    }
  }

  scoreCount = 0;
  int offset = min(rowIndex, columnIndex);
  int currentRowIndex = rowIndex - offset;
  int currentColumnIndex = columnIndex - offset;
  while (currentRowIndex < TRIANGLE_SIDE &&
         currentColumnIndex < TRIANGLE_SIDE) {
    if (board[currentRowIndex][currentColumnIndex] == c) {
      scoreCount++;
      if (scoreCount == WIN_SCORE) {
        return true;
      }
    } else {
      scoreCount = 0;
    }
    currentRowIndex++;
    currentColumnIndex++;
  }

  scoreCount = 0;
  offset = min(TRIANGLE_SIDE - 1 - rowIndex, columnIndex);
  currentRowIndex = rowIndex + offset;
  currentColumnIndex = columnIndex - offset;
  while (currentRowIndex >= 0 && currentColumnIndex < TRIANGLE_SIDE) {
    if (board[currentRowIndex][currentColumnIndex] == c) {
      scoreCount++;
      if (scoreCount == WIN_SCORE) {
        return true;
      }
    } else {
      scoreCount = 0;
    }
    currentRowIndex--;
    currentColumnIndex++;
  }

  return false;
}
