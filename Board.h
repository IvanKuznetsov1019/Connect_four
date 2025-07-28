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
  //...
};

class RectBoard : public IBoard {
 public:
  RectBoard();
  void draw() const override;
  void reset() override;
  bool placeChip(const int columnIndex, const char symbol);
  bool isWin(const int columnIndex) const;
  bool isFull() const;

 private:
  char board[NUM_OF_ROWS][NUM_OF_COLUMNS];
};

class TriangleBoard : public IBoard {
 public:
  TriangleBoard();
  void draw() const override;
  void reset() override;
  //...
 private:
  char board[TRIANGLE_SIDE][TRIANGLE_SIDE];
};
#endif