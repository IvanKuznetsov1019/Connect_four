#include <string.h>

#include <iostream>

#include "Board.h"

using std::string;

class Game {
 public:
  Game();
  void play();

 private:
  void screenRefresh() const;
  Board gameBoard;
  string command;
  int columnIndex;
  int playerId;
};
