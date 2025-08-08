#include "AIPlayer.h"
#include "Game.h"
#include "HumanPlayer.h"
#include "RectBoard.H"
#include "TriangleBoard.h"

int main() {
  HumanPlayer humanPlayer("Chelovek");
  AIPlayer aiPlayer("Terminator3000");
  Game game(new RectBoard(), &humanPlayer, &aiPlayer);
  game.play();
  return 0;
}