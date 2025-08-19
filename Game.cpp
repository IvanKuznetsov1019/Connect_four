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

    if (move.type == INCORRECT) {
      cout << "Invalid command: <" << move.incorrectCommand << ">." << endl;
      continue;
    }

    if (!executeMove(move, player->getPlayerSymbol())) {
      cout << "Invalid command args." << endl;
      continue;
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

bool Game::executeMove(const Move move, char symbol) {
  switch (move.type) {
    case PLACE_CHIP:
      if (gameBoard->mvPlaceChip(move.col, symbol)) {
        return true;
      }
      break;
    case POP_CHIP:
      if (gameBoard->mvPopChip(move.col)) {
        return true;
      }
      break;
    case PLACE_BOMB:
      if (gameBoard->mvPlaceBomb(move.col)) {
        return true;
      }
      break;
    case SWAP_CHIPS:
      if (gameBoard->mvSwapChips(move.col, move.row, move.targetCol,
                                 move.targetRow)) {
        return true;
      }
      break;
    case LEFT_SHIFT:
      if (gameBoard->mvLeftShift(move.row)) {
        return true;
      }
      break;
    case RIGHT_SHIFT:
      if (gameBoard->mvRightShift(move.row)) {
        return true;
      }
      break;
    case BOARD_FLIP:
      gameBoard->mvBoardFlip();
      return true;
    case EXIT:
      exit(0);
  }
  return false;
}