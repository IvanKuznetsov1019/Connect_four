#include "Game.h"

#include <iostream>

using namespace std;

bool isNumber(string& command) {
  for (const char c : command) {
    if (!isdigit(c)) {
      return false;
    }
  }
  return true;
}

Game::Game() : playerId(0), columnIndex(0), command(""), gameBoard() {}

void Game::setup() { setlocale(LC_ALL, "ru_RU.UTF-8"); }

void Game::screenRefresh() const {
  switch (gameBoard.status) {
    case Board::Status::OK:
      gameBoard.draw();
      cout << "Ходит игрок №" << to_string(2 - playerId) << endl;
      break;
    case Board::Status::WIN:
      gameBoard.draw();
      cout << "Победил игрок №" << to_string(playerId + 1) << endl;
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

void Game::play() {
  gameBoard.clear();
  gameBoard.draw();
  cout << "Ходит игрок №1" << endl;
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
    screenRefresh();
    if (gameBoard.status == Board::Status::WIN ||
        gameBoard.status == Board::Status::FULL) {
      gameBoard.clear();
      gameBoard.draw();
      playerId = 0;
      cout << "Ходит игрок №1" << endl;
    } else if (gameBoard.status == Board::Status::OK) {
      playerId++;
      playerId %= 2;
    }
  }
}
