class Board {
 public:
  Board();
  enum Status { OK, WIN, FULL, WC, WR };
  Status status;
  void update(const int columnIndex, const int id);
  void draw() const;
  void clear();

 private:
  bool isWin(const int rowIndex, const int columnIndex) const;
  bool hasEmptyCells() const;
  char board[6][7];
};
