#include "AIPlayer.h"

#include <random>

using std::string;

AIPlayer::AIPlayer(string playerId)
    : IPlayer(), IAIPlayerMixin(), id(playerId) {}

char AIPlayer::getPlayerSymbol() const { return symbol; }

int AIPlayer::getColumnIndex() const { return columnIndex; }

Move AIPlayer::makeMove() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> dis(0, 6);
  columnIndex = dis(gen);
  Move mv;
  mv.type = PLACE_CHIP;
  mv.col = columnIndex;
  return mv;
}

const string& AIPlayer::getId() const { return id; }

int AIPlayer::getDifficultyLevel() const { return difficultyLevel; }

void AIPlayer::setDifficultyLevel(int level) { difficultyLevel = level; }