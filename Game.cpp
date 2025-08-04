#include "Game.h"

using namespace std;

Game::Game(IBoard* gbPtr, IPlayer* p1, IPlayer* p2)
    : gameBoard(gbPtr), players{p1, p2} {}

void Game::setup() { setlocale(LC_ALL, "ru_RU.UTF-8"); }

void Game::play() {
  IPlayer* player;
  int playerNumber = 0;
  gameBoard->draw();

  auto gameRestart = [&]() {
    gameBoard->reset();
    gameBoard->draw();
    playerNumber = 0;
  };

  while (true) {
    player = players[playerNumber];
    cout << "Ходит игрок " << player->getId() << endl;
    player->makeMove(gameBoard);
    gameBoard->draw();

    if (gameBoard->isWin(player->getColumnIndex() - 1)) {
      cout << "Победил игрок " << player->getId() << endl;
      gameRestart();
      continue;
    }

    if (gameBoard->isFull()) {
      cout << "Ничья" << endl;
      gameRestart();
      continue;
    }

    playerNumber = (playerNumber == NUM_OF_PLAYERS - 1) ? 0 : playerNumber + 1;
  }
}
