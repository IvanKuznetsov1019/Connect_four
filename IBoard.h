#ifndef I_BOARD_H
#define I_BOARD_H
#define WIN_SCORE 4
#define NUM_OF_COLUMNS 7
#define NUM_OF_ROWS 6
#define TRIANGLE_SIDE 7

#include <iostream>

class IBoard {
 public:
  virtual void reset() = 0;
  virtual void display() const = 0;
  virtual bool isFull() const = 0;
  virtual bool mvPlaceChip(int columnIndex, char symbol) = 0;
  virtual bool mvPopChip(int columnIndex) = 0;
  virtual bool mvPlaceBomb(int columnIndex) = 0;
  virtual bool mvSwapChips(int columnIndexOne, int rowIndexOne,
                           int columnIndexTwo, int rowIndexTwo) = 0;
  virtual bool mvLeftShift(int rowIndex) = 0;
  virtual bool mvRightShift(int rowIndex) = 0;
  virtual void mvBoardFlip() = 0;
  virtual bool isWin(int columnIndex) const = 0;

 protected:
  virtual void dropChips() = 0;
  virtual bool isInBounds(int rowIndex, int columnIndex) = 0;
  virtual int findEmptyCellRowIndex(int columnIndex) = 0;
};
#endif