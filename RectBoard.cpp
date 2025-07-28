#include <iostream>

#include "Board.h"

using namespace std;

RectBoard::RectBoard() : IBoard() { reset(); }

void RectBoard::reset() {
  for (auto& row : board) {
    for (char& cell : row) {
      cell = '-';
    }
  }
}

void RectBoard::draw() const {
  for (int i = NUM_OF_ROWS - 1; i >= 0; i--) {
    for (int j = 0; j < NUM_OF_COLUMNS; j++) {
      cout << '|' << board[i][j];
    }
    cout << '|' << endl;
  }
}

bool RectBoard::placeChip(const int columnIndex, const char symbol) {
  int rowIndex = 0;
  for (const auto& row : board) {
    if (row[columnIndex] == '-') {
      break;
    }
    rowIndex++;
  }
  if (rowIndex >= NUM_OF_ROWS) {
    return false;
  }
  board[rowIndex][columnIndex] = symbol;
  return true;
}

bool RectBoard::isFull() const {
  for (const char cell : board[NUM_OF_ROWS - 1]) {
    if (cell == '-') {
      return false;
    }
  }
  return true;
}

bool RectBoard::isWin(const int columnIndex) const {
  char c = '-';
  int rowIndex;
  for (rowIndex = NUM_OF_ROWS - 1; rowIndex >= 0; rowIndex--) {
    if (board[rowIndex][columnIndex] != '-') {
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
  for (int i = rowIndex; i >= 0; i--) {
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
  while (currentRowIndex < NUM_OF_ROWS && currentColumnIndex < NUM_OF_COLUMNS) {
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
  offset = min(NUM_OF_ROWS - 1 - rowIndex, columnIndex);
  currentRowIndex = rowIndex + offset;
  currentColumnIndex = columnIndex - offset;
  while (currentRowIndex >= 0 && currentColumnIndex < NUM_OF_COLUMNS) {
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
