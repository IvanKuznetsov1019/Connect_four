#ifndef TRIANGLE_BOARD_H
#define TRIANGLE_BOARD_H
#include "IBoard.h"
class TriangleBoard : public IBoard {
 public:
  TriangleBoard();
  void reset() override;
  void display() const override;
  bool isFull() const override;
  bool isWin(int columnIndex) const override;
  bool mvPlaceChip(int columnIndex, char symbol) override;
  bool mvPopChip(int columnIndex) override;
  bool mvPlaceBomb(int columnIndex) override;
  bool mvSwapChips(int columnIndexOne, int rowIndexOne, int columnIndexTwo,
                   int rowIndexTwo) override;
  void mvLeftShift(int rowIndex) override;
  void mvRightShift(int rowIndex) override;
  void mvBoardFlip() override;

 protected:
  void dropChips() override;
  int findEmptyCellRowIndex(int columnIndex) override;

 private:
  char board[TRIANGLE_SIDE][TRIANGLE_SIDE];
};
#endif