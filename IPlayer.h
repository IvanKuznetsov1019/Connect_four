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
  MoveType type;
  std::string incorrectCommand;
  int row, col, targetRow, targetCol;
  Move() {
    type = INCORRECT;
    row = -1;
    col = -1;
    targetRow = -1;
    targetCol = -1;
    incorrectCommand = "";
  };
  Move(MoveType t, int p) : type(t) {
    if (t == RIGHT_SHIFT || t == LEFT_SHIFT) {
      row = p;
    } else {
      col = p;
    }
  };
  Move(MoveType t, int c, int r, int tc, int tr)
      : type(t),
        col(c),
        row(r),
        targetCol(tc),
        targetRow(tr),
        incorrectCommand("") {};
} Move;

class IPlayer {
 public:
  virtual char getPlayerSymbol() const = 0;
  virtual int getColumnIndex() const = 0;
  virtual Move makeMove() = 0;
  virtual const std::string& getId() const = 0;
};

#endif
