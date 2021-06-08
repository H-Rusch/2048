#ifndef GAME_H_
#define GAME_H_

#include <vector>

#include "Board.hpp"

class Game {
    private:
        Board* gameState;
        vector<Board> gameStates;

    public:
        // construct the game. Initialize the list of possible moves
        Game(int size);

        // getter for the current board
        Board getBoard();

        // get the dimension of the board
        int getBoardDimension();

        // check wether the game is finished and no more moves are possible
        // if the game is over, the list of gameStates is cleared, so undoing won't work
        bool checkGameOver();

        // restart the game by resetting the board. Also reset the past board states
        void restart();

        // execute a move based on the input. The input -1 causes the undo function to be called
        void play(int input);

        /* save current board state to the list of past board states. After 100 moves are saved,
        saving another one will remove the earliest move in the list */
        void saveBoardState();

        // go back to the last board state if there are some moves left
        void undoMove();
};
#endif // GAME_H_
