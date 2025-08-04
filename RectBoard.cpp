#include "RectBoard.h"

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

bool RectBoard::isFull() const {
  for (const char cell : board[NUM_OF_ROWS - 1]) {
    if (cell == '-') {
      return false;
    }
  }
  return true;
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

bool RectBoard::isWin(const int columnIndex) const {
  char symbol = '-';
  int rowIndex = -1;

  for (rowIndex = NUM_OF_ROWS - 1; rowIndex >= 0; rowIndex--) {
    if (board[rowIndex][columnIndex] != '-') {
      symbol = board[rowIndex][columnIndex];
      break;
    }
  }

  auto countConsecutive = [&](int r, int c, const int dr, const int dc) {
    int count = 0;
    while (r >= 0 && r < NUM_OF_ROWS && c >= 0 && c < NUM_OF_COLUMNS &&
           board[r][c] == symbol) {
      count++;
      r += dr;
      c += dc;
    }
    return count;
  };

  int horizontalCheck = countConsecutive(rowIndex, columnIndex, 0, -1) +
                        countConsecutive(rowIndex, columnIndex, 0, 1) - 1;
  if (horizontalCheck >= WIN_SCORE) return true;
  int verticalCheck = countConsecutive(rowIndex, columnIndex, -1, 0) +
                      countConsecutive(rowIndex, columnIndex, 1, 0) - 1;
  if (verticalCheck >= WIN_SCORE) return true;
  int diag1Check = countConsecutive(rowIndex, columnIndex, -1, -1) +
                   countConsecutive(rowIndex, columnIndex, 1, 1) - 1;
  if (diag1Check >= WIN_SCORE) return true;
  int diag2Check = countConsecutive(rowIndex, columnIndex, -1, 1) +
                   countConsecutive(rowIndex, columnIndex, 1, -1) - 1;
  if (diag2Check >= WIN_SCORE) return true;
  return false;
}