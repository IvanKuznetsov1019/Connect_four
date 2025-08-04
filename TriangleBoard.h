#ifndef TRIANGLE_BOARD_H
#define TRIANGLE_BOARD_H
#include "IBoard.h"
class TriangleBoard : public IBoard {
 public:
  TriangleBoard();
  void reset() override;
  void draw() const override;
  bool isFull() const override;
  bool placeChip(const int columnIndex, const char symbol) override;
  bool isWin(const int columnIndex) const override;

 private:
  char board[TRIANGLE_SIDE][TRIANGLE_SIDE];
};
#endif