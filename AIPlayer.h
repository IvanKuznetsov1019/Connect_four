#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "IAIPlayerMixin.h"
#include "IPlayer.h"

class AIPlayer : public IPlayer, public IAIPlayerMixin {
 public:
  AIPlayer(std::string playerId);
  char getPlayerSymbol() const override;
  int getColumnIndex() const override;
  void makeMove(IBoard* gameBoard) override;
  const std::string& getId() const override;
  int getDifficultyLevel() const override;
  void setDifficultyLevel(const int level) override;

 private:
  char symbol = 'x';
  int columnIndex;
  std::string id;
};
#endif