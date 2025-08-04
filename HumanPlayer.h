#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "IPlayer.h"

class HumanPlayer : public IPlayer {
 public:
  HumanPlayer(std::string playerId);
  char getPlayerSymbol() const override;
  int getColumnIndex() const override;
  void makeMove(IBoard* gameBoard) override;
  const std::string& getId() const override;

 private:
  char symbol = 'o';
  int columnIndex;
  std::string id;
};

bool isNumber(std::string& command);

#endif