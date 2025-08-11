#include "Game.h"

using namespace std;

Game::Game(IBoard* gbPtr, IPlayer* p1, IPlayer* p2)
    : gameBoard(gbPtr), players{p1, p2} {}

Game::~Game() { delete gameBoard; }

void Game::setup() {}

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
    cout << "Player " << player->getId() << " making move." << endl;
    player->makeMove(gameBoard);
    gameBoard->draw();

    if (gameBoard->isWin(player->getColumnIndex() - 1)) {
      cout << "Player " << player->getId() << " is win!" << endl;
      gameRestart();
      continue;
    }

    if (gameBoard->isFull()) {
      cout << "Dead heat." << endl;
      gameRestart();
      continue;
    }

    playerNumber = (playerNumber == NUM_OF_PLAYERS - 1) ? 0 : playerNumber + 1;
  }
}
