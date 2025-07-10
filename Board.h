class Board {
 public:
  enum Status { OK, WIN, FULL, WC, WR };
  Status status;
  static Board& instance();
  void update(const int columnIndex, const int id);
  void draw() const;
  void init();

 private:
  Board();
  Board(const Board&) = delete;
  Board& operator=(const Board&) = delete;
  bool isWin(const int rowIndex, const int columnIndex) const;
  bool hasEmptyCells() const;
  char board[6][7];
};

void screenRefresh(Board& gameBoard, int id);
