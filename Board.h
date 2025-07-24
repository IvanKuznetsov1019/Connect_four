#ifndef BOARD_H
#define BOARD_H
#define WIN_SCORE 4
#define NUM_OF_COLUMNS 7
#define NUM_OF_ROWS 6

class Board {
 public:
  enum Status { OK, WIN, FULL, WC, WR };
  Status status;
  void update(const int columnIndex, const int id);
  void draw() const;
  void clear();

 private:
  bool isWin(const int rowIndex, const int columnIndex) const;
  bool hasEmptyCells() const;
  char board[NUM_OF_ROWS][NUM_OF_COLUMNS];
};
#endif