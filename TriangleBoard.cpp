#include "TriangleBoard.h"

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

bool TriangleBoard::mvPlaceChip(const int columnIndex, const char symbol) {
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

bool TriangleBoard::mvDeleteChip(const int columnIndex) { return 1; }
bool TriangleBoard::mvPlaceBobmb(const int columnIndex) { return 1; }
bool TriangleBoard::mvSwapChips(const int columnIndexOne, const int rowIndexOne,
                                const int columnIndexTwo,
                                const int rowIndexTwo) {
  return 1;
}
void TriangleBoard::mvCyclicShift(const int rowIndex, const std::string& dir) {}
void TriangleBoard::mvBoardFlip() {}
void TriangleBoard::dropChips() {}
int TriangleBoard::findEmptyCellRowIndex(const int columnIndex) { return 1; }

bool TriangleBoard::isWin(const int columnIndex) const {
  char symbol = '-';
  int rowIndex = -1;

  for (rowIndex = 0; rowIndex < TRIANGLE_SIDE; rowIndex++) {
    if (board[rowIndex][columnIndex] != '-' &&
        board[rowIndex][columnIndex] != '#') {
      symbol = board[rowIndex][columnIndex];
      break;
    }
  }
  cout << symbol << " " << rowIndex << endl;
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
