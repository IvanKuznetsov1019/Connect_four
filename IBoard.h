#ifndef BOARD_H
#define BOARD_H
#define WIN_SCORE 4
#define NUM_OF_COLUMNS 7
#define NUM_OF_ROWS 6
#define TRIANGLE_SIDE 7

class IBoard {
 public:
  virtual void reset() = 0;
  virtual void draw() const = 0;
  virtual bool isFull() const = 0;
  virtual bool placeChip(const int columnIndex, const char symbol) = 0;
  virtual bool isWin(const int columnIndex) const = 0;
};
#endif