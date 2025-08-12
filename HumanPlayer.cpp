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

int isInRange(const std::string& num, const int min, const int max) {
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

void HumanPlayer::makeMove(IBoard* gameBoard) {
  string command;

  while (true) {
    cin >> command;

    if (command == "bomb") {
      cin >> command;
      if (columnIndex = isInRange(command, 1, NUM_OF_COLUMNS)) {
        if (!gameBoard->mvPlaceBobmb(columnIndex - 1)) {
          cout << "You cant place bomb on this column.." << endl;
          continue;
        }
        break;
      }
    }

    if (command == "delete") {
      cin >> command;
      if (columnIndex = isInRange(command, 1, NUM_OF_COLUMNS)) {
        if (!gameBoard->mvDeleteChip(columnIndex - 1)) {
          cout << "There is no used cell in the column." << endl;
          continue;
        }
        break;
      }
    }

    if (command == "flip") {
      gameBoard->mvBoardFlip();
      break;
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
        if (!gameBoard->mvSwapChips(columnIndexOne - 1, rowIndexOne - 1,
                                    columnIndexTwo - 1, rowIndexTwo - 1)) {
          cout << "You can't use empty cells for this command." << endl;
          continue;
        }
        break;
      }
      cout << "Incorrect command." << endl;
      continue;
    }

    if (command == "shift") {
      cin >> command;
      if (command == "left" || command == "right") {
        string dir = command;
        cin >> command;
        int rowIndex = isInRange(command, 1, NUM_OF_COLUMNS);
        if (rowIndex > 0 && rowIndex < 7) {
          gameBoard->mvCyclicShift(rowIndex - 1, dir);
          break;
        }
      }
      cout << "Incorrect command: " << command << endl;
      continue;
    }

    if (command == "exit") {
      exit(0);
    }

    if (!isNumber(command)) {
      cout << "Incorrect command: " << command << endl;
      continue;
    }
    columnIndex = stoi(command);

    if (columnIndex < 1 || columnIndex > NUM_OF_COLUMNS) {
      cout << "The selected column does not exist." << endl;
      continue;
    }

    if (!gameBoard->mvPlaceChip(columnIndex - 1, getPlayerSymbol())) {
      cout << "There is no free cell in the column." << endl;
      continue;
    }
    break;
  }
}

const string& HumanPlayer::getId() const { return id; }
