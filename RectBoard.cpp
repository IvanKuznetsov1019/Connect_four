#include "RectBoard.h"

#include <iostream>

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

// bool RectBoard::isWin(const int columnIndex) const {
//   char c = '-';
//   int rowIndex;
//   for (rowIndex = NUM_OF_ROWS - 1; rowIndex >= 0; rowIndex--) {
//     if (board[rowIndex][columnIndex] != '-') {
//       c = board[rowIndex][columnIndex];
//       break;
//     }
//   }

//   int scoreCount = 0;
//   for (const char& cell : board[rowIndex]) {
//     if (cell == c) {
//       scoreCount++;
//       if (scoreCount == WIN_SCORE) {
//         return true;
//       }
//     } else {
//       scoreCount = 0;
//     }
//   }

//   scoreCount = 0;
//   for (int i = rowIndex; i >= 0; i--) {
//     if (board[i][columnIndex] == c) {
//       scoreCount++;
//       if (scoreCount == WIN_SCORE) {
//         return true;
//       }
//     } else {
//       scoreCount = 0;
//     }
//   }

//   scoreCount = 0;
//   int offset = min(rowIndex, columnIndex);
//   int currentRowIndex = rowIndex - offset;
//   int currentColumnIndex = columnIndex - offset;
//   while (currentRowIndex < NUM_OF_ROWS && currentColumnIndex <
//   NUM_OF_COLUMNS) {
//     if (board[currentRowIndex][currentColumnIndex] == c) {
//       scoreCount++;
//       if (scoreCount == WIN_SCORE) {
//         return true;
//       }
//     } else {
//       scoreCount = 0;
//     }
//     currentRowIndex++;
//     currentColumnIndex++;
//   }

//   scoreCount = 0;
//   offset = min(NUM_OF_ROWS - 1 - rowIndex, columnIndex);
//   currentRowIndex = rowIndex + offset;
//   currentColumnIndex = columnIndex - offset;
//   while (currentRowIndex >= 0 && currentColumnIndex < NUM_OF_COLUMNS) {
//     if (board[currentRowIndex][currentColumnIndex] == c) {
//       scoreCount++;
//       if (scoreCount == WIN_SCORE) {
//         return true;
//       }
//     } else {
//       scoreCount = 0;
//     }
//     currentRowIndex--;
//     currentColumnIndex++;
//   }

//   return false;
// }

// bool RectBoard::isWin(const int columnIndex) const {
//   char c = '-';
//   int rowIndex;
//   for (rowIndex = NUM_OF_ROWS - 1; rowIndex >= 0; rowIndex--) {
//     if (board[rowIndex][columnIndex] != '-') {
//       c = board[rowIndex][columnIndex];
//       break;
//     }
//   }
//   int scoreCount = 0;
//   int currentRowIndex;
//   int currentColumnIndex;
//   auto checkDir{[&](const int r, const int c, const int dr, const int dc) {
//     int offset =
//         (dr != 0 && dc != 0)
//             ? min(static_cast<int>(
//                       (r * dr) + (NUM_OF_ROWS / 2 - ((NUM_OF_ROWS / 2) * dr))
//                       - (0.5 - (0.5 * dr))),
//                   c)
//             : r * dr;
//     currentRowIndex = r - offset;
//     currentColumnIndex = c - offset;
//     cout << offset << "  " << currentRowIndex << "  " << currentColumnIndex
//          << endl;
//     while (currentRowIndex >= 0 && currentColumnIndex < NUM_OF_COLUMNS &&
//            currentRowIndex < NUM_OF_ROWS) {
//       if (board[currentRowIndex][currentColumnIndex] == c) {
//         scoreCount++;
//         if (scoreCount == WIN_SCORE) {
//           return true;
//           break;
//         }
//       } else {
//         scoreCount = 0;
//       }
//       currentRowIndex += dr;
//       currentColumnIndex += dc;
//     }
//     return false;
//   }};
//   return checkDir(rowIndex, columnIndex, 1, 0) ||
//          checkDir(rowIndex, columnIndex, 0, 1) ||
//          checkDir(rowIndex, columnIndex, 1, 1) ||
//          checkDir(rowIndex, columnIndex, 1, -1);
// }

bool RectBoard::isWin(const int columnIndex) const {
  char c = '-';
  int rowIndex = -1;

  for (rowIndex = NUM_OF_ROWS - 1; rowIndex >= 0; rowIndex--) {
    if (board[rowIndex][columnIndex] != '-') {
      c = board[rowIndex][columnIndex];
      break;
    }
  }

  auto countConsecutive = [&](int r, int c, int dr, int dc) {
    int count = 0;
    while (r >= 0 && r < NUM_OF_ROWS && c >= 0 && c < NUM_OF_COLUMNS &&
           board[r][c] == c) {
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