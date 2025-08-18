#include "Game.h"

using std::cout;
using std::endl;

Game::Game(IBoard* gbPtr, IPlayer* p1, IPlayer* p2)
    : gameBoard(gbPtr), players{p1, p2} {}

Game::~Game() { delete gameBoard; }

void Game::setup() {}

void Game::play() {
  IPlayer* player;
  int playerNumber = 0;
  gameBoard->display();

  auto gameRestart = [&]() {
    gameBoard->reset();
    gameBoard->display();
    playerNumber = 0;
  };

  Move move;

  while (true) {
    player = players[playerNumber];
    cout << "Player " << player->getId() << " making move." << endl;
    move = player->makeMove();
    switch (move.type) {
      case PLACE_CHIP:
        gameBoard->mvPlaceChip(move.col, player->getPlayerSymbol());
        break;
      case POP_CHIP:
        gameBoard->mvPopChip(move.col);
        break;
      case PLACE_BOMB:
        gameBoard->mvPlaceBomb(move.col);
        break;
      case SWAP_CHIPS:
        gameBoard->mvSwapChips(move.col, move.row, move.targetCol,
                               move.targetRow);
        break;
      case LEFT_SHIFT:
        gameBoard->mvLeftShift(move.row);
        break;
      case RIGHT_SHIFT:
        gameBoard->mvRightShift(move.row);
        break;
      case BOARD_FLIP:
        gameBoard->mvBoardFlip();
        break;
      case EXIT:
        exit(0);
      default:
        cout << "Incorrect command" << endl;
        break;
    }

    gameBoard->display();

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
