#include "AIPlayer.h"

using std::string;

AIPlayer::AIPlayer(string playerId) : id(playerId) {}

char AIPlayer::getPlayerSymbol() const { return symbol; }

int AIPlayer::getColumnIndex() const { return columnIndex; }

void AIPlayer::makeMove(IBoard* gameBoard) {
  srand(time({}));
  columnIndex = rand() % 7 + 1;
  while (!gameBoard->placeChip(getColumnIndex() - 1, getPlayerSymbol())) {
    columnIndex = rand() % 7 + 1;
  }
}

const string& AIPlayer::getId() const { return id; }

int AIPlayer::getDifficultyLevel() const { return difficultyLevel; }

void AIPlayer::setDifficultyLevel(const int level) { difficultyLevel = level; }