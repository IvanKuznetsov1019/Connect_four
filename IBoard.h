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
  virtual void draw() const = 0;
  virtual bool isFull() const = 0;
  virtual bool mvPlaceChip(const int columnIndex, const char symbol) = 0;
  virtual bool mvDeleteChip(const int columnIndex) = 0;
  virtual bool mvPlaceBobmb(const int columnIndex) = 0;
  virtual bool mvSwapChips(const int columnIndexOne, const int rowIndexOne,
                           const int columnIndexTwo, const int rowIndexTwo) = 0;
  virtual void mvCyclicShift(const int rowIndex, const std::string& dir) = 0;
  virtual void mvBoardFlip() = 0;
  virtual bool isWin(const int columnIndex) const = 0;

 protected:
  virtual void dropChips() = 0;
  virtual int findEmptyCellRowIndex(const int columnIndex) = 0;
};
#endif