#ifndef GAME_H
#define GAME_H
#include <iostream>

#include "IBoard.h"

class Game {
 public:
  Game(IBoard* gbPtr);
  void play();
  void setup();

 private:
  IBoard* gameBoard;
  std::string command;
  int columnIndex;
  int playerId;
};
#endif