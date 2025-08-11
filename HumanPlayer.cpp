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

void HumanPlayer::makeMove(IBoard* gameBoard) {  /////////////
  string command;

  while (true) {
    cin >> command;

    if (command == "bomb") {
      cin >> command;
      if (columnIndex = isCorrectNum(command)) {
        gameBoard->mvPlaceBobmb(columnIndex - 1);
        break;
      }
    }

    if (command == "delete") {
      cin >> command;
      if (columnIndex = isCorrectNum(command)) {
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
      int columnIndexOne = isCorrectNum(command);
      cin >> command;
      int columnIndexTwo = isCorrectNum(command);
      if (columnIndexOne && columnIndexTwo) {
        gameBoard->mvSwapChips(columnIndexOne - 1, columnIndexTwo - 1);
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
        int rowIndex = isCorrectNum(command);
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

int HumanPlayer::isCorrectNum(const string& command) {
  if (!isNumber(command)) {
    return 0;
  }
  int col = stoi(command);
  if (col > 7 || col < 1) {
    return 0;
  }
  return col;
}
