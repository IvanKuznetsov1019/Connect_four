#ifndef GAME_H
#define GAME_H

#include "IPlayer.h"

#define NUM_OF_PLAYERS 2

class Game {
 public:
  Game(IBoard* gbPtr, IPlayer* p1, IPlayer* p2);
  void play();
  void setup();

 private:
  IBoard* gameBoard;
  IPlayer* players[NUM_OF_PLAYERS];
};
#endif