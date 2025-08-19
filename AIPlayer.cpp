#include "AIPlayer.h"

using std::string;

AIPlayer::AIPlayer(string playerId)
    : IPlayer(), IAIPlayerMixin(), id(playerId) {}

char AIPlayer::getPlayerSymbol() const { return symbol; }

int AIPlayer::getColumnIndex() const { return columnIndex; }

Move AIPlayer::makeMove() {
  srand(time({}));
  columnIndex = rand() % 7;
  Move mv;
  mv.type = PLACE_CHIP;
  mv.col = columnIndex;
  return mv;
}

const string& AIPlayer::getId() const { return id; }

int AIPlayer::getDifficultyLevel() const { return difficultyLevel; }

void AIPlayer::setDifficultyLevel(int level) { difficultyLevel = level; }