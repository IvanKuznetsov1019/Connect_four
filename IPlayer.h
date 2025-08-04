#ifndef I_PLAYER_H
#define I_PLAYER_H

#include "IBoard.h"

class IPlayer {
 public:
  virtual char getPlayerSymbol() const = 0;
  virtual int getColumnIndex() const = 0;
  virtual void makeMove(IBoard* gameBoard) = 0;
  virtual const std::string& getId() const = 0;
};
#endif
