#ifndef RECT_BOARD_H
#define RECT_BOARD_H
#include "IBoard.h"
class RectBoard : public IBoard {
 public:
  RectBoard();
  void reset() override;
  void display() const override;
  bool isFull() const override;
  bool isWin(int columnIndex) const override;
  bool mvPlaceChip(int columnIndex, char symbol) override;
  bool mvPopChip(int columnIndex) override;
  bool mvPlaceBomb(int columnIndex) override;
  bool mvSwapChips(int columnIndexOne, int rowIndexOne, int columnIndexTwo,
                   int rowIndexTwo) override;
  bool mvLeftShift(int rowIndex) override;
  bool mvRightShift(int rowIndex) override;
  void mvBoardFlip() override;

 protected:
  void dropChips() override;
  int findEmptyCellRowIndex(int columnIndex) override;
  bool isInBounds(int rowIndex, int columnIndex) override;

 private:
  char board[NUM_OF_ROWS][NUM_OF_COLUMNS];
};
#endif