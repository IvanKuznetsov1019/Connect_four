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
  RectBoard gameBoard;
  std::string command;
  int columnIndex;
  int playerId;
};
#endif