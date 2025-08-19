#ifndef I_PLAYER_H
#define I_PLAYER_H

#include "IBoard.h"

enum MoveType {
  PLACE_CHIP,
  POP_CHIP,
  LEFT_SHIFT,
  RIGHT_SHIFT,
  PLACE_BOMB,
  SWAP_CHIPS,
  BOARD_FLIP,
  EXIT,
  INCORRECT
};

typedef struct Move {
  MoveType type = INCORRECT;
  std::string incorrectCommand;
  int row = -1, col = -1, targetRow = -1, targetCol = -1;
} Move;

class IPlayer {
 public:
  virtual char getPlayerSymbol() const = 0;
  virtual int getColumnIndex() const = 0;
  virtual Move makeMove() = 0;
  virtual const std::string& getId() const = 0;
};

#endif
