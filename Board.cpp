#include "Board.h"

#include <iostream>

using namespace std;

Board& Board::instance() {
  static Board gameBoard;
  return gameBoard;
}

Board::Board() { init(); }

void Board::init() {
  for (auto& row : board) {
    for (char& cell : row) {
      cell = '-';
    }
  }
  status = OK;
}

void Board::draw() const {
  for (const auto& row : board) {
    for (const char cell : row) {
      cout << '|' << cell;
    }
    cout << '|' << endl;
  }
}

void Board::update(const int columnIndex, const int id) {
  if (columnIndex < 0 || columnIndex > 7) {
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
  if (rowIndex > 5) {
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
  for (const auto& row : board) {
    for (const char cell : row) {
      if (cell == '-') {
        return true;
      }
    }
  }
  return false;
}

bool Board::isWin(const int rowIndex, const int columnIndex) const {
  int scoreCount = 0;
  char c = board[rowIndex][columnIndex];
  for (const char& cell : board[rowIndex]) {
    if (cell == c) {
      scoreCount++;
      if (scoreCount == 4) {
        return true;
      }
    } else {
      scoreCount = 0;
    }
  }
  scoreCount = 0;
  for (int i = rowIndex; i >= 0; i--) {
    if (board[i][columnIndex]) {
      if (board[i][columnIndex] == c) {
        scoreCount++;
        if (scoreCount == 4) {
          return true;
        }
      } else {
        scoreCount = 0;
      }
    }
  }
  scoreCount = 0;
  int currentRowIndex = rowIndex - min(rowIndex, columnIndex);
  int currentColumnIndex = columnIndex - min(rowIndex, columnIndex);
  while (currentRowIndex < 6 && currentColumnIndex < 7) {
    if (board[currentRowIndex][currentColumnIndex] == c) {
      scoreCount++;
      if (scoreCount == 4) {
        return true;
      }
    } else {
      scoreCount = 0;
    }
    currentRowIndex++;
    currentColumnIndex++;
  }
  scoreCount = 0;
  currentRowIndex = rowIndex + min(5 - rowIndex, columnIndex);
  currentColumnIndex = columnIndex - min(5 - rowIndex, columnIndex);
  while (currentRowIndex >= 0 && currentColumnIndex < 7) {
    if (board[currentRowIndex][currentColumnIndex] == c) {
      scoreCount++;
      if (scoreCount == 4) {
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

void screenRefresh(const Board& gameBoard, int id) {
  switch (gameBoard.status) {
    case Board::Status::OK:
      gameBoard.draw();
      cout << "Ходит игрок №" << to_string(2 - id) << endl;
      break;
    case Board::Status::WIN:
      gameBoard.draw();
      cout << "Победил игрок №" << to_string(++id) << endl;
      break;
    case Board::Status::WC:
      cout << "Выбранный столбец не существует" << endl;
      break;
    case Board::Status::WR:
      cout << "В столбце нет свободной клетки" << endl;
      break;
    case Board::Status::FULL:
      gameBoard.draw();
      cout << "Ничья" << endl;
      break;
  }
}