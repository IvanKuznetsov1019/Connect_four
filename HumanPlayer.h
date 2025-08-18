#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "IPlayer.h"

class HumanPlayer : public IPlayer {
 public:
  HumanPlayer(std::string playerId);
  char getPlayerSymbol() const override;
  int getColumnIndex() const override;
  Move makeMove() override;
  const std::string& getId() const override;

 private:
  char symbol = 'o';
  int columnIndex;
  std::string id;
};

bool isNumber(const std::string& command);
int isInRange(const std::string& command, int min, int max);

#endif