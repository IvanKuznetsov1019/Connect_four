#include "RectBoard.h"

using std::cin;
using std::cout;
using std::endl;

RectBoard::RectBoard() : IBoard() { reset(); }

void RectBoard::reset() {
  for (auto& row : board) {
    for (char& cell : row) {
      cell = '-';
    }
  }
}

void RectBoard::display() const {
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

bool RectBoard::mvPlaceChip(int columnIndex, char symbol) {
  int rowIndex = findEmptyCellRowIndex(columnIndex);
  if (rowIndex < NUM_OF_ROWS) {
    board[rowIndex][columnIndex] = symbol;
    return true;
  }
  return false;
}

bool RectBoard::mvPopChip(int columnIndex) {
  int rowIndex = findEmptyCellRowIndex(columnIndex);
  if (rowIndex > 0) {
    board[rowIndex - 1][columnIndex] = '-';
    return true;
  }
  return false;
}

bool RectBoard::mvPlaceBomb(int columnIndex) {
  int rowIndex = findEmptyCellRowIndex(columnIndex);
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
  dropChips();
  return true;
}

bool RectBoard::mvSwapChips(int columnIndexOne, int rowIndexOne,
                            int columnIndexTwo, int rowIndexTwo) {
  if (board[rowIndexOne][columnIndexOne] == '-' ||
      board[rowIndexTwo][columnIndexTwo] == '-') {
    return false;
  }
  char tmpCell = board[rowIndexOne][columnIndexOne];
  board[rowIndexOne][columnIndexOne] = board[rowIndexTwo][columnIndexTwo];
  board[rowIndexTwo][columnIndexTwo] = tmpCell;
  return true;
}

void RectBoard::mvLeftShift(int rowIndex) {
  char tmpCell = board[rowIndex][0];
  for (int i = 0; i < NUM_OF_COLUMNS - 1; i++) {
    board[rowIndex][i] = board[rowIndex][i + 1];
  }
  board[rowIndex][NUM_OF_COLUMNS - 1] = tmpCell;
  dropChips();
}

void RectBoard::mvRightShift(int rowIndex) {
  char tmpCell = board[rowIndex][NUM_OF_COLUMNS - 1];
  for (int i = NUM_OF_COLUMNS - 1; i > 0; i--) {
    board[rowIndex][i] = board[rowIndex][i - 1];
  }
  board[rowIndex][0] = tmpCell;
  dropChips();
}

void RectBoard::mvBoardFlip() {
  for (int i = 0; i < NUM_OF_COLUMNS; i++) {
    int chipsCount = findEmptyCellRowIndex(i);
    if (chipsCount > 1) {
      char tmpCell;
      for (int j = 0; j < chipsCount / 2; j++) {
        tmpCell = board[j][i];
        board[j][i] = board[chipsCount - j - 1][i];
        board[chipsCount - j - 1][i] = tmpCell;
      }
    }
  }
}

void RectBoard::dropChips() {
  int i = 0, j = 0;

  auto dropUpperChips = [&]() {
    if (board[j][i] == '-') {
      int tmpJ = j;
      while (tmpJ < NUM_OF_ROWS && board[tmpJ][i] == '-') {
        tmpJ++;
      }
      if (tmpJ < NUM_OF_ROWS) {
        board[j][i] = board[tmpJ][i];
        board[tmpJ][i] = '-';
      }
    }
  };

  for (i = 0; i < NUM_OF_COLUMNS; i++) {
    for (j = 0; j < NUM_OF_ROWS; j++) {
      dropUpperChips();
    }
  }
}

int RectBoard::findEmptyCellRowIndex(int columnIndex) {
  int rowIndex = 0;
  for (const auto& row : board) {
    if (row[columnIndex] == '-') {
      break;
    }
    rowIndex++;
  }
  return rowIndex;
}

bool RectBoard::isWin(int columnIndex) const {
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
