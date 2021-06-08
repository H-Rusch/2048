#include <random>

#include "Board.hpp"
#include "Field.hpp"

using namespace std;

Board::Board(int size) {
    dimension = size;
    fields.resize(size);
    for (int i = 0; i < size; i++) {
        fields[i].resize(size);
    }
    resetGame();
}

Board::Board(const Board &board) {
    dimension = board.dimension;
    fields = board.fields;
    emptyFields = board.emptyFields;
    possibleMoves = board.possibleMoves;
}

Board Board::operator=(const Board &board) {
    fields = board.fields;
    emptyFields = board.emptyFields;
    possibleMoves = board.possibleMoves;
    return *this;
}

int Board::getDimension() {
    return dimension;
}

void Board::resetGame() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            Field field;
            fields[i][j] = field;
        }
    }
    spawnNewField();
    spawnNewField();
}

Field Board::getField(int x, int y) {
    return fields[x][y];
}

void Board::initField(int x, int y) {
    fields[x][y].initialize();
    updateMovesPossible();
}

void Board::spawnNewField() {
    if (getEmptyFields() > 0) {
        // chose one of the empty coordinates randomly
        int index = rand() % emptyFields.size();
        tuple<int, int> coordinates = emptyFields.at(index);
        emptyFields.erase(emptyFields.begin() + index);
        initField(get<0>(coordinates), get<1>(coordinates));
    }
}

int Board::getEmptyFields() {
    emptyFields.clear();
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (fields[i][j].isEmpty()) {
                emptyFields.push_back(make_tuple(i, j));
            }
        }
    }
    return emptyFields.size();
}

void Board::updateMovesPossible() {
    possibleMoves.clear();
    if (rightPossible()) {
        possibleMoves.push_back(0);
    }
    if (upPossible()) {
        possibleMoves.push_back(1);
    }
    if (leftPossible()) {
        possibleMoves.push_back(2);
    }
    if (downPossible()) {
        possibleMoves.push_back(3);
    }
}

bool Board::anyMovePossible() {
    return possibleMoves.size() > 0;
}

vector<int> Board::getMovesPossible() {
    return possibleMoves;
}

bool Board::rightPossible() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension - 1; j++) {
            if (!fields[i][j].isEmpty()) {
                // empty field can't be moved. Search further for a field which can be moved
                // non empty field could be moved. Check the fields to the right of that field
                int k = j + 1;
                if (fields[i][k].isEmpty()) {
                    // movement is possible if there is an empty field to the right of an initialized field
                    return true;
                } else if (fields[i][k].getValue() == fields[i][j].getValue()) {
                    // movement is possible if two fields with the same value are "next" to each other
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::upPossible() {
    for (int j = 0; j < dimension; j++) {
        for (int i = dimension - 1; i >= 1; i--) {
            if (!fields[i][j].isEmpty()) {
                // empty field can't be moved. Search further for a field which can be moved
                // non empty field could be moved. Check the fields above that field
                int k = i - 1;
                if (fields[k][j].isEmpty()) {
                    // movement is possible if there is an empty field above an initialized field
                    return true;
                } else if (fields[k][j].getValue() == fields[i][j].getValue()) {
                    // movement is possible if two fields with the same value are "next" to each other
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::leftPossible() {
    for (int i = 0; i < dimension; i++) {
        for (int j = dimension - 1; j >= 1; j--) {
            if (!fields[i][j].isEmpty()) {
                // empty field can't be moved. Search further for a field which can be moved
                // non empty field could be moved. Check the fields to the left of that field
                int k = j - 1;
                if (fields[i][k].isEmpty()) {
                    // movement is possible if there is an empty field to the left of an initialized field
                    return true;
                } else if (fields[i][k].getValue() == fields[i][j].getValue()) {
                    // movement is possible if two fields with the same value are "next" to each other
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::downPossible() {
   for (int j = 0; j < dimension; j++) {
        for (int i = 0; i < dimension - 1; i++) {
            if (!fields[i][j].isEmpty()) {
                // empty field can't be moved. Search further for a field which can be moved
                // non empty field could be moved. Check the fields below that field
                int k = i + 1;
                if (fields[k][j].isEmpty()) {
                    // movement is possible if there is an empty field below an initialized field
                    return true;
                } else if (fields[k][j].getValue() == fields[i][j].getValue()) {
                    // movement is possible if two fields with the same value are "next" to each other
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::moveRight() {
    for (int i = 0; i < dimension; i++) {
        for (int j = dimension - 2; j >= 0; j--) {
            if (!fields[i][j].isEmpty()) {
                // empty field can't be moved. Search further for a field which can be moved
                // for a filled field, search until a field of the same value is found for merging, or find the empty field furthest away
                int moveToLocation = j;
                bool reset = true;
                for (int k = j + 1; k < dimension; k++) {
                    if (fields[i][k].isEmpty()) {
                        moveToLocation = k;
                    } else {
                        if (fields[i][k].getValue() == fields[i][j].getValue() && !fields[i][k].getChanged()) {
                            // field with same value found. Merge them and double the value
                            moveToLocation = k;
                            fields[i][k].setChanged(true);
                            fields[i][j].doubleValue();
                            break;
                        } else {
                            // fields with different value found. Move them next to each other
                            moveToLocation = k - 1;
                            if (moveToLocation == j) {
                                reset = false;
                            }
                            break;
                        }
                    }
                }
                // put the fields at the correct location
                fields[i][moveToLocation].setValue(fields[i][j].getValue());
                if (reset) {
                    fields[i][j].resetValue();
                }
            }
        }
    }
    resetChanged();
    spawnNewField();
}

void Board::moveUp() {
    for (int j = 0; j < dimension; j++) {
        for (int i = 1; i < dimension; i++) {
            if (!fields[i][j].isEmpty()) {
                // empty field can't be moved. Search further for a field which can be moved
                // for a filled field, search until a field of the same value is found for merging, or find the empty field furthest away
                int moveToLocation = i;
                bool reset = true;
                for (int k = i - 1; k >= 0; k--) {
                    if (fields[k][j].isEmpty()) {
                        moveToLocation = k;
                    } else {
                        if (fields[k][j].getValue() == fields[i][j].getValue() && !fields[k][j].getChanged()) {
                            // field with same value found. Merge them and double the value
                            moveToLocation = k;
                            fields[k][j].setChanged(true);
                            fields[i][j].doubleValue();
                            break;
                        } else {
                            // fields with different value found. Move them next to each other
                            moveToLocation = k + 1;
                            if (moveToLocation == i) {
                                reset = false;
                            }
                            break;
                        }
                    }
                }
                // put the fields at the correct location
                fields[moveToLocation][j].setValue(fields[i][j].getValue());
                if (reset) {
                    fields[i][j].resetValue();
                }
            }
        }
    }
    resetChanged();
    spawnNewField();
}

void Board::moveLeft() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 1; j < dimension; j++) {
            if (!fields[i][j].isEmpty()) {
                // empty field can't be moved. Search further for a field which can be moved
                // for a filled field, search until a field of the same value is found for merging, or find the empty field furthest away
                int moveToLocation = j;
                bool reset = true;
                for (int k = j - 1; k >= 0; k--) {
                    if (fields[i][k].isEmpty()) {
                        moveToLocation = k;
                    } else {
                        if (fields[i][k].getValue() == fields[i][j].getValue() && !fields[i][k].getChanged()) {
                            // field with same value found. Merge them and double the value
                            moveToLocation = k;
                            fields[i][k].setChanged(true);
                            fields[i][j].doubleValue();
                            break;
                        } else {
                            // fields with different value found. Move them next to each other
                            moveToLocation = k + 1;
                            if (moveToLocation == j) {
                                reset = false;
                            }
                            break;
                        }
                    }
                }
                // put the fields at the correct location
                fields[i][moveToLocation].setValue(fields[i][j].getValue());
                if (reset) {
                    fields[i][j].resetValue();
                }
            }
        }
    }
    resetChanged();
    spawnNewField();
}

void Board::moveDown() {
    for (int j = 0; j < dimension; j++) {
        for (int i = dimension - 2; i >= 0; i--) {
            if (!fields[i][j].isEmpty()) {
                // empty field can't be moved. Search further for a field which can be moved
                // for a filled field, search until a field of the same value is found for merging, or find the empty field furthest away
                int moveToLocation = i;
                bool reset = true;
                for (int k = i + 1; k < dimension; k++) {
                    if (fields[k][j].isEmpty()) {
                        moveToLocation = k;
                    } else {
                        if (fields[k][j].getValue() == fields[i][j].getValue() && !fields[k][j].getChanged()) {
                            // field with same value found. Merge them and double the value
                            moveToLocation = k;
                            fields[k][j].setChanged(true);
                            fields[i][j].doubleValue();
                            break;
                        } else {
                            // fields with different value found. Move them next to each other
                            moveToLocation = k - 1;
                            if (moveToLocation == i) {
                                reset = false;
                            }
                            break;
                        }
                    }
                }
                // put the fields at the correct location
                fields[moveToLocation][j].setValue(fields[i][j].getValue());
                if (reset) {
                    fields[i][j].resetValue();
                }
            }
        }
    }
    resetChanged();
    spawnNewField();
}

void Board::resetChanged() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            fields[i][j].setChanged(false);
        }
    }
}
