#include "HumanPlayer.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

bool isNumber(string& command) {
  for (const char c : command) {
    if (!isdigit(c)) {
      return false;
    }
  }
  return true;
}

HumanPlayer::HumanPlayer(string playerId) : id(playerId) {}

char HumanPlayer::getPlayerSymbol() const { return symbol; }

int HumanPlayer::getColumnIndex() const { return columnIndex; }

void HumanPlayer::makeMove(IBoard* gameBoard) {
  string command;
  while (true) {
    cin >> command;
    if (command == "exit") {
      exit(0);
    } else if (!isNumber(command)) {
      cout << "Некорректная команда: " << command << endl;
      continue;
    }
    columnIndex = stoi(command);

    if (columnIndex < 1 || columnIndex > NUM_OF_COLUMNS) {
      cout << "Выбранный столбец не существует" << endl;
      continue;
    }

    if (!gameBoard->placeChip(columnIndex - 1, getPlayerSymbol())) {
      cout << "В столбце нет свободной клетки" << endl;
      continue;
    }
    break;
  }
}

const string& HumanPlayer::getId() const { return id; }