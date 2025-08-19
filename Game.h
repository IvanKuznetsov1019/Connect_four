#ifndef GAME_H
#define GAME_H

#include "IPlayer.h"

#define NUM_OF_PLAYERS 2

class Game {
 public:
  Game(IBoard* gbPtr, IPlayer* p1, IPlayer* p2);
  ~Game();
  void play();
  void setup();

 private:
  bool executeMove(const Move move, char simbol);
  IBoard* gameBoard;
  IPlayer* players[NUM_OF_PLAYERS];
};
#endif