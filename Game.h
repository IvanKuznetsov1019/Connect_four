#ifndef GAME_H
#define GAME_H
#include <iostream>

#include "Board.h"

class Game {
 public:
  Game();
  void play();
  void setup();

 private:
  void screenRefresh() const;
  Board gameBoard;
  std::string command;
  int columnIndex;
  int playerId;
};
#endif