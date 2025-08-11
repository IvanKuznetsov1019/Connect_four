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

bool RectBoard::mvPlaceChip(const int columnIndex, const char symbol) {
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

bool RectBoard::mvDeleteChip(const int columnIndex) {
  int rowIndex = -1;
  for (int i = NUM_OF_ROWS - 1; i >= 0; i--) {
    if (board[i][columnIndex] != '-') {
      rowIndex = i;
      break;
    }
  }
  if (rowIndex < 0) {
    return false;
  }
  board[rowIndex][columnIndex] = '-';
  return true;
}

bool RectBoard::mvPlaceBobmb(const int columnIndex) {
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

  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if ((rowIndex + i) >= 0 && (columnIndex + j) < NUM_OF_COLUMNS &&
          (columnIndex + j) >= 0 && (rowIndex + i) < NUM_OF_ROWS) {
        board[rowIndex + i][columnIndex + j] = '-';
      }
    }
  }
  return true;
}

bool RectBoard::mvSwapChips(const int columnIndexOne,
                            const int columnIndexTwo) {
  int rowIndexOne = -1;
  int rowIndexTwo = -1;
  for (int i = NUM_OF_ROWS - 1; i >= 0; i--) {
    if (board[i][columnIndexOne] != '-') {
      rowIndexOne = i;
      break;
    }
  }
  for (int i = NUM_OF_ROWS - 1; i >= 0; i--) {
    if (board[i][columnIndexTwo] != '-') {
      rowIndexTwo = i;
      break;
    }
  }
  if (rowIndexOne < 0 || rowIndexTwo < 0) {
    return false;
  }
  char tmpCell = board[rowIndexOne][columnIndexOne];
  board[rowIndexOne][columnIndexOne] = board[rowIndexTwo][columnIndexTwo];
  board[rowIndexTwo][columnIndexTwo] = tmpCell;
  ;
  return true;
}

void RectBoard::mvCyclicShift(const int rowIndex, const std::string& dir) {
  if (dir == "left") {
    char tmpCell = board[rowIndex][0];
    for (int i = 0; i < NUM_OF_COLUMNS - 1; i++) {
      board[rowIndex][i] = board[rowIndex][i + 1];
    }
    board[rowIndex][NUM_OF_COLUMNS - 1] = tmpCell;
  } else {
    char tmpCell = board[rowIndex][NUM_OF_COLUMNS - 1];
    for (int i = NUM_OF_COLUMNS - 1; i > 0; i--) {
      board[rowIndex][i] = board[rowIndex][i - 1];
    }
    board[rowIndex][0] = tmpCell;
  }
  // привести доску в порядок
}

void RectBoard::mvBoardFlip() {  ///???
  char tmpCell;
  for (int i = 0; i < NUM_OF_ROWS / 2; i++) {
    for (int j = 0; j < NUM_OF_COLUMNS; j++) {
      tmpCell = board[i][j];
      board[i][j] = board[NUM_OF_ROWS - 1 - i][j];
      board[NUM_OF_ROWS - 1 - i][j] = tmpCell;
    }
  }
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
