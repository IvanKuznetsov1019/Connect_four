#include "HumanPlayer.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

bool isNumber(const string& command) {
  for (const char c : command) {
    if (!isdigit(c)) {
      return false;
    }
  }
  return true;
}

HumanPlayer::HumanPlayer(string playerId) : IPlayer(), id(playerId) {}

char HumanPlayer::getPlayerSymbol() const { return symbol; }

int HumanPlayer::getColumnIndex() const { return columnIndex; }

Move HumanPlayer::makeMove() {
  string command;
  Move currentMove;
  cin >> command;

  if (isNumber(command)) {
    columnIndex = stoi(command);
    currentMove.type = PLACE_CHIP;
    currentMove.col = columnIndex - 1;
    return currentMove;
  }

  if (command == "exit") {
    currentMove.type = EXIT;
    return currentMove;
  }

  if (command == "bomb") {
    cin >> command;
    if (isNumber(command)) {
      columnIndex = stoi(command);
      currentMove.type = PLACE_BOMB;
      currentMove.col = columnIndex - 1;
      return currentMove;
    }
    currentMove.type = INCORRECT;
    currentMove.incorrectCommand = command;
    // тут проблемы
    return currentMove;
  }

  if (command == "pop") {
    cin >> command;
    if (isNumber(command)) {
      columnIndex = stoi(command);
      currentMove.type = POP_CHIP;
      currentMove.col = columnIndex - 1;
      return currentMove;
    }
    currentMove.type = INCORRECT;
    currentMove.incorrectCommand = command;
    return currentMove;
  }

  if (command == "flip") {
    currentMove.type = BOARD_FLIP;
    return currentMove;
    // columnIndex = ?;
    // IBoard::isWin() тут тоже не работает по человечески:
    //  |o|-|-|-|
    //  |x|-|-|-|
    //  |x|o|o|o|
    //  <BOARD_FLIP>
    //  |X|-|-|-|
    //  |x|-|-|-|
    //  |O|o|o|o|
    //  возможно может случится ничья, когда одновременно
    // сложаться победные комбинации обоих игроков, но это не точно
  }

  if (command == "swap") {
    int params[4] = {0, 0, 0, 0};
    for (int& p : params) {
      cin >> command;
      if (isNumber(command)) {
        p = stoi(command);
      }
    }
    if (!params[0] || !params[1] || !params[2] || !params[3]) {
      currentMove.type = INCORRECT;
      return currentMove;
    }
    currentMove.type = SWAP_CHIPS;
    currentMove.col = params[0] - 1;
    currentMove.row = params[1] - 1;
    currentMove.targetCol = params[2] - 1;
    currentMove.targetRow = params[3] - 1;
    // columnIndex = ?;
    // IBoard::isWin() тут не работает по человечески тоже, как и проверка на
    // ничью:
    //  |o|-|-|-|
    //  |x|-|-|-|
    //  |x|o|o|o|
    //  <SWAP_CHIPS> <1, 1, 1, 3>
    //  |X|-|-|-|
    //  |x|-|-|-|
    //  |o|o|o|o|
    return currentMove;
  }

  if (command == "shift") {
    cin >> command;
    if (command == "left") {
      cin >> command;
      if (isNumber(command)) {
        int rowIndex = stoi(command);
        currentMove.type = LEFT_SHIFT;
        currentMove.row = rowIndex - 1;
        return currentMove;
      }
    } else if (command == "right") {
      cin >> command;
      if (isNumber(command)) {
        int rowIndex = stoi(command);
        currentMove.type = RIGHT_SHIFT;
        currentMove.row = rowIndex - 1;
        return currentMove;
      }
    }
    currentMove.type = INCORRECT;
    currentMove.incorrectCommand = command;
    // ну и тут тоже самое, но ещё хуже:
    // columnIndex = ?;
    // IBoard::isWin() тут не работает, ничья тоже:
    //  |-|-|-|-|
    //  |x|o|-|-|
    //  |o|o|-|o|
    //  <SHIFT_RIGHT> <2>
    //  |-|-|-|-|
    //  |-|x|-|-|
    //  |o|o|o|o|
    //  или
    //  |-|-|-|-|-|-|-|
    //  |x|-|-|-|-|-|-|
    //  |x|-|-|-|-|-|-|
    //  |x|-|-|-|-|-|-|
    //  |o|-|-|-|-|-|-|
    //  |x|-|o|o|o|-|-|
    //  <SHIFT_RIGHT> <2>
    //  |-|-|-|-|-|-|-|
    //  |-|-|-|-|-|-|-|
    //  |x|-|-|-|-|-|-|
    //  |x|-|-|-|-|-|-|
    //  |x|-|-|-|-|-|-|
    //  |x|o|o|o|o|-|-|
    return currentMove;
  }

  currentMove.type = INCORRECT;
  currentMove.incorrectCommand = command;
  return currentMove;
}

const string& HumanPlayer::getId() const { return id; }
