#ifndef RECT_BOARD_H
#define RECT_BOARD_H
#include "IBoard.h"
class RectBoard : public IBoard {
 public:
  RectBoard();
  void reset() override;
  void draw() const override;
  bool isFull() const override;
  bool placeChip(const int columnIndex, const char symbol) override;
  bool isWin(const int columnIndex) const override;

 private:
  char board[NUM_OF_ROWS][NUM_OF_COLUMNS];
};
#endif