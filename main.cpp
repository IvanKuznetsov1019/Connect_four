#include <iostream>
#include <locale>
#include <string>

#include "Board.h"

using namespace std;

bool isNumber(string& command) {
  for (const char c : command) {
    if (!isdigit(c)) {
      return false;
    }
  }
  return true;
}

int main() {
  setlocale(LC_ALL, "ru_RU.UTF-8");
  Board& gameBoard = Board::instance();
  gameBoard.draw();
  cout << "Ходит игрок №1" << endl;
  int columnIndex;
  string command;
  int playerId = 0;
  while (true) {
    cin >> command;
    if (command == "exit") {
      break;
    } else if (!isNumber(command)) {
      cout << "Некорректная команда: " << command << endl;
      continue;
    }
    columnIndex = stoi(command);
    gameBoard.update(--columnIndex, playerId);
    screenRefresh(gameBoard, playerId);
    if (gameBoard.status == Board::Status::WIN ||
        gameBoard.status == Board::Status::FULL) {
      gameBoard.init();
      gameBoard.draw();
      playerId = 0;
      cout << "Ходит игрок №1" << endl;
    } else if (gameBoard.status == Board::Status::OK) {
      playerId++;
      playerId %= 2;
    }
  }
  return 0;
}