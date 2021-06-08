#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <tuple>
#include <array>

#include "Field.hpp"

using namespace std;

class Board {
    private:
        int dimension;
        vector<vector<Field>> fields;
        vector<tuple<int, int>> emptyFields;
        vector<int> possibleMoves;

        // DEBUGGING initialize any field you want
        void initField(int x, int y);

        // Initialize one of the empty fields
        void spawnNewField();

        // get the amount of empty fields on the board
        int getEmptyFields();

        // checks wether doing a right move is possible
        bool rightPossible();

        // checks wether doing a up move is possible
        bool upPossible();

        // checks wether doing a down move is possible
        bool downPossible();

        // checks wether doing a left move is possible
        bool leftPossible();

        // after a move reset the changed flag on all fields again
        void resetChanged();

    public:
        // constructor. Initialize two random fields on the board
        Board(int size);

        // copy constructor
        Board(const Board &board);

        // copy assignment operator
        Board operator=(const Board &board);

        Field getField(int x, int y);

        // reset the board and initialize the first values
        void resetGame();

        // return the dimension of the board
        int getDimension();

        // save a list of possible moves with the current board. 0 := right, 1 := up, 2 := left, 3 := down
        void updateMovesPossible();

        // get list of possible moves
        vector<int> getMovesPossible();

        // check wether any move is possible on the current board
        bool anyMovePossible();

        // move the fields right
        void moveRight();

        // move the fields up
        void moveUp();

         // move the fields left
        void moveLeft();

        // move the fields down
        void moveDown();
};

#endif // BOARD_H_
