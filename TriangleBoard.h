#ifndef TRIANGLE_BOARD_H
#define TRIANGLE_BOARD_H
#include "IBoard.h"
class TriangleBoard : public IBoard {
 public:
  TriangleBoard();
  void reset() override;
  void draw() const override;
  bool isFull() const override;
  bool isWin(const int columnIndex) const override;
  bool mvPlaceChip(const int columnIndex, const char symbol) override;
  bool mvDeleteChip(const int columnIndex) override;
  bool mvPlaceBobmb(const int columnIndex) override;
  bool mvSwapChips(const int columnIndexOne, const int columnIndexTwo) override;
  void mvCyclicShift(const int rowIndex, const std::string& dir) override;
  void mvBoardFlip() override;

 private:
  char board[TRIANGLE_SIDE][TRIANGLE_SIDE];
};
#endif