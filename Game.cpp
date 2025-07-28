#include "Game.h"

#include <iostream>
#include <map>

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

void Game::setup() {
  setlocale(LC_ALL, "ru_RU.UTF-8");
  // cout << "Выберите тип доски. 'T' - треугольная, 'R' - прямоугольная." <<
  // endl; char boardType; cin >> boardType; if (boardType == 'T') {
  //   //...
  // } else {
  //   //...
  // }
}

void Game::play() {
  map<int, char> idToSymbol = {{0, 'o'}, {1, 'x'}};

  while (true) {
    gameBoard.draw();
    cout << "Ходит игрок №" << to_string(playerId + 1) << endl;
    cin >> command;

    if (command == "exit") {
      break;
    } else if (!isNumber(command)) {
      cout << "Некорректная команда: " << command << endl;
      continue;
    }
    columnIndex = stoi(command);

    if (columnIndex < 1 || columnIndex > NUM_OF_COLUMNS) {
      cout << "Выбранный столбец не существует" << endl;
      continue;
    }
    columnIndex--;

    if (!gameBoard.placeChip(columnIndex, idToSymbol[playerId])) {
      cout << "В столбце нет свободной клетки" << endl;
      continue;
    }

    if (gameBoard.isWin(columnIndex)) {
      gameBoard.draw();
      cout << "Победил игрок №" << to_string(playerId + 1) << endl;
      gameBoard.reset();
      playerId = 0;
      continue;
    }

    if (gameBoard.isFull()) {
      cout << "Ничья" << endl;
      gameBoard.reset();
      playerId = 0;
      continue;
    }

    playerId++;
    playerId %= 2;
  }
}