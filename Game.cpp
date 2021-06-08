#include <algorithm>

#include "Game.hpp"
#include "Board.hpp"

using namespace std;

Game::Game(int size) {
    gameState = new Board(size);
    gameState->updateMovesPossible();
}

Board Game::getBoard() {
    return *gameState;
}

int Game::getBoardDimension() {
    return getBoard().getDimension();
}

bool Game::checkGameOver() {
    bool gameOver = !gameState->anyMovePossible();
    if (gameOver) {
        gameStates.clear();
    }
    return gameOver;
}

void Game::restart() {
    gameState->resetGame();
    gameStates.clear();
}

void Game::play(int input) {
    vector<int> possible = gameState->getMovesPossible();

    if(find(possible.begin(), possible.end(), input) != possible.end()) {
        // input move is in the possible moves
        // save the current board to the list of past board states and then execure the next move
        saveBoardState();
        if (input == 0) {
            gameState->moveRight();
        } else if (input == 1) {
            gameState->moveUp();
        } else if (input == 2) {
            gameState->moveLeft();
        } else if (input == 3) {
            gameState->moveDown();
        }
    }
}

void Game::undoMove() {
    if (gameStates.size() != 0) {
        gameState = new Board(gameStates.back());
        gameStates.pop_back();
    }
}

void Game::saveBoardState() {
    // keep the size of the saved states at a maximum
    if (gameStates.size() > 100) {
        gameStates.erase(gameStates.begin());
    }
    gameStates.push_back(*gameState);
}
