#include "Game.h"
#include "RectBoard.H"
#include "TriangleBoard.h"

int main() {
  Game game(new RectBoard());
  // Game game(new TriangleBoard());
  game.setup();
  game.play();
  return 0;
}