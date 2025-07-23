#include <locale>

#include "Game.h"

using namespace std;

int main() {
  setlocale(LC_ALL, "ru_RU.UTF-8");
  Game game;
  game.play();
  return 0;
}