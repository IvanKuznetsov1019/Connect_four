#ifndef RECT_BOARD_H
#define RECT_BOARD_H
#include "IBoard.h"
class RectBoard : public IBoard {
 public:
  RectBoard();
  void reset() override;
  void draw() const override;
  bool isFull() const override;
  bool isWin(const int columnIndex) const override;
  bool mvPlaceChip(const int columnIndex, const char symbol) override;
  bool mvDeleteChip(const int columnIndex) override;
  bool mvPlaceBobmb(const int columnIndex) override;
  bool mvSwapChips(const int columnIndexOne, const int rowIndexOne,
                   const int columnIndexTwo, const int rowIndexTwo) override;
  void mvCyclicShift(const int rowIndex, const std::string& dir) override;
  void mvBoardFlip() override;

 protected:
  void dropChips() override;
  int findEmptyCellRowIndex(const int columnIndex) override;

 private:
  char board[NUM_OF_ROWS][NUM_OF_COLUMNS];
};
#endif