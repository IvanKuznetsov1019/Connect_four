#include "Board.h"

#include <iostream>

using namespace std;

void Board::clear() {
  for (auto& row : board) {
    for (char& cell : row) {
      cell = '-';
    }
  }
  status = OK;
}

void Board::draw() const {
  for (auto row = rbegin(board); row != rend(board); row++) {
    for (auto cell = begin(*row); cell != end(*row); cell++) {
      cout << '|' << *cell;
    }
    cout << '|' << endl;
  }
}

void Board::update(const int columnIndex, const int id) {
  if (columnIndex < 0 || columnIndex > NUM_OF_COLUMNS - 1) {
    status = WC;
    return;
  }
  int rowIndex = 0;
  for (const auto& row : board) {
    if (row[columnIndex] == '-') {
      break;
    }
    rowIndex++;
  }
  if (rowIndex > NUM_OF_ROWS - 1) {
    status = WR;
    return;
  }
  board[rowIndex][columnIndex] = (id == 0) ? 'o' : 'x';
  if (isWin(rowIndex, columnIndex)) {
    status = WIN;
    return;
  }
  if (!hasEmptyCells()) {
    status = FULL;
    return;
  }
  status = OK;
}

bool Board::hasEmptyCells() const {
  for (const char cell : board[NUM_OF_ROWS - 1]) {
    if (cell == '-') {
      return true;
    }
  }
  return false;
}

bool Board::isWin(const int rowIndex, const int columnIndex) const {
  char c = board[rowIndex][columnIndex];

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
  offset = min(5 - rowIndex, columnIndex);
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
