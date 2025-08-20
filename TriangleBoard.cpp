#include "TriangleBoard.h"

using std::cin;
using std::cout;
using std::endl;

TriangleBoard::TriangleBoard() : IBoard() { reset(); }

void TriangleBoard::reset() {
  for (int i = 0; i < TRIANGLE_SIDE; i++) {
    for (int j = 0; j < TRIANGLE_SIDE; j++) {
      board[i][j] = (j <= i) ? '-' : '#';
    }
  }
}

void TriangleBoard::display() const {
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

bool TriangleBoard::mvPlaceChip(int columnIndex, char symbol) {
  if (!isInBounds(0, columnIndex)) {
    return false;
  }
  int rowIndex = findEmptyCellRowIndex(columnIndex);
  if (rowIndex < 0) {
    return false;
  }
  board[rowIndex][columnIndex] = symbol;
  return true;
}

bool TriangleBoard::mvPopChip(int columnIndex) {
  if (!isInBounds(0, columnIndex)) {
    return false;
  }
  int rowIndex = findEmptyCellRowIndex(columnIndex);
  if (rowIndex < 0) {
    rowIndex = columnIndex;
    board[rowIndex][columnIndex] = '-';
    return true;
  } else if (rowIndex < TRIANGLE_SIDE - 1) {
    board[++rowIndex][columnIndex] = '-';
    return true;
  }
  return false;
}

bool TriangleBoard::mvPlaceBomb(int columnIndex) {
  if (!isInBounds(0, columnIndex)) {
    return false;
  }
  int rowIndex = findEmptyCellRowIndex(columnIndex);
  if (rowIndex < 0) {
    return false;
  }
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if ((rowIndex + i) >= 0 && (columnIndex + j) < TRIANGLE_SIDE &&
          (columnIndex + j) >= 0 && (rowIndex + i) < TRIANGLE_SIDE &&
          board[rowIndex + i][columnIndex + j] != '#') {
        board[rowIndex + i][columnIndex + j] = '-';
      }
    }
  }
  dropChips();
  return true;
}

bool TriangleBoard::mvSwapChips(int columnIndexOne, int rowIndexOne,
                                int columnIndexTwo, int rowIndexTwo) {
  if (!isInBounds(rowIndexOne, columnIndexOne) ||
      !isInBounds(rowIndexTwo, columnIndexTwo)) {
    return false;
  }

  rowIndexOne = TRIANGLE_SIDE - 1 - rowIndexOne;
  rowIndexTwo = TRIANGLE_SIDE - 1 - rowIndexTwo;

  if (board[rowIndexOne][columnIndexOne] == '-' ||
      board[rowIndexTwo][columnIndexTwo] == '-' ||
      board[rowIndexOne][columnIndexOne] == '#' ||
      board[rowIndexTwo][columnIndexTwo] == '#') {
    return false;
  }

  char tmpCell = board[rowIndexOne][columnIndexOne];
  board[rowIndexOne][columnIndexOne] = board[rowIndexTwo][columnIndexTwo];
  board[rowIndexTwo][columnIndexTwo] = tmpCell;
  return true;
}

bool TriangleBoard::mvLeftShift(int rowIndex) {
  if (!isInBounds(rowIndex, 0)) {
    return false;
  }
  int newRowIndex = TRIANGLE_SIDE - rowIndex - 1;
  char tmpCell = board[newRowIndex][0];
  for (int i = 0; i < TRIANGLE_SIDE - 1; i++) {
    if (board[newRowIndex][i + 1] != '#') {
      board[newRowIndex][i] = board[newRowIndex][i + 1];
      continue;
    } else {
      board[newRowIndex][i] = tmpCell;
      break;
    }
  }
  int endIndex = TRIANGLE_SIDE - 1;
  while (board[newRowIndex][endIndex] == '#' && endIndex >= 0) {
    endIndex--;
  }
  board[newRowIndex][endIndex] = tmpCell;
  dropChips();
  return true;
}

bool TriangleBoard::mvRightShift(int rowIndex) {
  if (!isInBounds(rowIndex, 0)) {
    return false;
  }
  int newRowIndex = TRIANGLE_SIDE - rowIndex - 1;
  int startIndex = TRIANGLE_SIDE - 1;
  while (board[newRowIndex][startIndex] == '#' && startIndex >= 0) {
    startIndex--;
  }
  char tmpCell = board[newRowIndex][startIndex];
  for (int i = startIndex; i > 0; i--) {
    board[newRowIndex][i] = board[newRowIndex][i - 1];
  }
  board[newRowIndex][0] = tmpCell;
  dropChips();
  return true;
}

void TriangleBoard::mvBoardFlip() {
  for (int i = 0; i < TRIANGLE_SIDE; i++) {
    int chipsCount = findEmptyCellRowIndex(i);
    if (chipsCount == -1) {
      chipsCount = i - 1;
    }
    for (int j = chipsCount + 1;
         j <= chipsCount + ((TRIANGLE_SIDE - chipsCount - 1) / 2); j++) {
      char tmpCell = board[j][i];
      board[j][i] = board[TRIANGLE_SIDE - 1 - (j - 1 - chipsCount)][i];
      board[TRIANGLE_SIDE - 1 - (j - 1 - chipsCount)][i] = tmpCell;
    }
  }
}

void TriangleBoard::dropChips() {
  int i = 0, j = 0;

  auto dropUpperChips = [&]() {
    if (board[j][i] == '-') {
      int tmpJ = j;
      while (tmpJ >= 0 && board[tmpJ][i] == '-') {
        tmpJ--;
      }
      if (tmpJ >= 0 && board[tmpJ][i] != '#') {
        board[j][i] = board[tmpJ][i];
        board[tmpJ][i] = '-';
      }
    }
  };

  for (i = 0; i < TRIANGLE_SIDE; i++) {
    for (j = TRIANGLE_SIDE - 1; j >= 0; j--) {
      dropUpperChips();
    }
  }
}

int TriangleBoard::findEmptyCellRowIndex(int columnIndex) {
  int rowIndex = 0;
  for (rowIndex = TRIANGLE_SIDE - 1; rowIndex >= 0; rowIndex--) {
    if (board[rowIndex][columnIndex] == '-') {
      break;
    }
  }
  return rowIndex;
}

bool TriangleBoard::isWin(int columnIndex) const {
  char symbol = '-';
  int rowIndex = -1;

  for (rowIndex = 0; rowIndex < TRIANGLE_SIDE; rowIndex++) {
    if (board[rowIndex][columnIndex] != '-' &&
        board[rowIndex][columnIndex] != '#') {
      symbol = board[rowIndex][columnIndex];
      break;
    }
  }

  auto countConsecutive = [&](int r, int c, int dr, int dc) {
    int count = 0;
    while (r >= 0 && r < TRIANGLE_SIDE && c >= 0 && c < TRIANGLE_SIDE &&
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

bool TriangleBoard::isInBounds(int rowIndex, int columnIndex) {
  return (rowIndex < TRIANGLE_SIDE && columnIndex >= 0 &&
          columnIndex < TRIANGLE_SIDE && rowIndex >= 0 &&
          (rowIndex + columnIndex) < TRIANGLE_SIDE)
             ? true
             : false;
}