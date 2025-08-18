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

int isInRange(const std::string& num, int min, int max) {
  if (!isNumber(num)) {
    return 0;
  }
  int n = stoi(num);
  if (n > max || n < min) {
    return 0;
  }
  return n;
}

HumanPlayer::HumanPlayer(string playerId) : IPlayer(), id(playerId) {}

char HumanPlayer::getPlayerSymbol() const { return symbol; }

int HumanPlayer::getColumnIndex() const { return columnIndex; }

Move HumanPlayer::makeMove() {
  string command;
  Move currentMove;
  cin >> command;

  if (command == "bomb") {
    cin >> command;
    if (columnIndex = isInRange(command, 1, NUM_OF_COLUMNS)) {
      currentMove.type = PLACE_BOMB;
      currentMove.col = columnIndex - 1;
      return currentMove;
    }
    currentMove.type = INCORRECT;
    return currentMove;
  }

  if (command == "pop") {
    cin >> command;
    if (columnIndex = isInRange(command, 1, NUM_OF_COLUMNS)) {
      currentMove.type = POP_CHIP;
      currentMove.col = columnIndex - 1;
      return currentMove;
    }
    currentMove.type = INCORRECT;
    return currentMove;
  }

  if (command == "flip") {
    currentMove.type = BOARD_FLIP;
    return currentMove;
  }

  if (command == "swap") {
    cin >> command;
    int columnIndexOne = isInRange(command, 1, NUM_OF_COLUMNS);
    cin >> command;
    int rowIndexOne = isInRange(command, 1, NUM_OF_COLUMNS);
    cin >> command;
    int columnIndexTwo = isInRange(command, 1, NUM_OF_COLUMNS);
    cin >> command;
    int rowIndexTwo = isInRange(command, 1, NUM_OF_COLUMNS);
    if (columnIndexOne && columnIndexTwo && rowIndexOne && rowIndexTwo) {
      currentMove.type = SWAP_CHIPS;
      currentMove.col = columnIndexOne - 1;
      currentMove.row = rowIndexOne - 1;
      currentMove.targetCol = columnIndexTwo - 1;
      currentMove.targetRow = rowIndexTwo - 1;
      return currentMove;
    }
    currentMove.type = INCORRECT;
    return currentMove;
  }

  if (command == "shift") {
    cin >> command;
    if (command == "left") {
      string dir = command;
      cin >> command;
      int rowIndex = isInRange(command, 1, NUM_OF_COLUMNS);
      currentMove.type = LEFT_SHIFT;
      currentMove.row = rowIndex - 1;
      return currentMove;
    } else if (command == "right") {
      string dir = command;
      cin >> command;
      int rowIndex = isInRange(command, 1, NUM_OF_COLUMNS);
      currentMove.type = RIGHT_SHIFT;
      currentMove.row = rowIndex - 1;
      return currentMove;
    }
    currentMove.type = INCORRECT;
    return currentMove;
  }

  if (command == "exit") {
    currentMove.type = EXIT;
    return currentMove;
  }

  if (!isNumber(command)) {
    currentMove.type = INCORRECT;
    return currentMove;
  }

  columnIndex = stoi(command);

  currentMove.type = PLACE_CHIP;
  currentMove.col = columnIndex - 1;
  return currentMove;
}

const string& HumanPlayer::getId() const { return id; }
