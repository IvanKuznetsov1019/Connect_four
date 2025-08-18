#include "AIPlayer.h"

using std::string;

AIPlayer::AIPlayer(string playerId)
    : IPlayer(), IAIPlayerMixin(), id(playerId) {}

char AIPlayer::getPlayerSymbol() const { return symbol; }

int AIPlayer::getColumnIndex() const { return columnIndex; }

Move AIPlayer::makeMove() {
  srand(time({}));
  columnIndex = rand() % 7;
  return Move(PLACE_CHIP, columnIndex);
}

const string& AIPlayer::getId() const { return id; }

int AIPlayer::getDifficultyLevel() const { return difficultyLevel; }

void AIPlayer::setDifficultyLevel(int level) { difficultyLevel = level; }