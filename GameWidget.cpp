#include <QKeyEvent>
#include <QPushButton>
#include <QMessageBox>
#include <QString>

#include "GameWidget.hpp"
#include "FieldWidget.hpp"

GameWidget::GameWidget(int size) {
    this->setWindowTitle(QString("2048"));
    game = new Game(size);

    // create the layouts
    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    topLayout = new QHBoxLayout();
    boardLayout = new QGridLayout();

    // set background color
    setStyleSheet("background-color: rgb(230, 230, 230)");

    // fill top layout with new game and undo button
    newGameButton = new QPushButton("NewGame");
    topLayout->addWidget(newGameButton);
    newGameButton->setFocusPolicy(Qt::NoFocus);
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(resetGame()));
    newGameButton->setStyleSheet("border: 1px solid black;"
                                 "padding: 5px;"
                                 "font-size: 14px;"
                                 "background-color: rgb(200, 200, 200);");

    undoButton = new QPushButton("Undo");
    topLayout->addWidget(undoButton);
    undoButton->setFocusPolicy(Qt::NoFocus);
    connect(undoButton, SIGNAL(clicked()), this, SLOT(undo()));
    undoButton->setStyleSheet("border: 1px solid black;"
                              "padding: 5px;"
                              "font-size: 14px;"
                              "background-color: rgb(200, 200, 200);");

    mainLayout->insertLayout(0, topLayout);

    initBoard();
}

void GameWidget::initBoard() {
    int size = game->getBoardDimension();
    // initialize the guiBoard and draw it
    QGridLayout boardLayout;
    guiBoard.resize(size);
    for(int i = 0; i < size; i++) {
        guiBoard[i].resize(size);
    }
    drawBoard();
}

void GameWidget::drawBoard() {
    delete boardLayout;
    boardLayout = new QGridLayout();
    Board board = game->getBoard();

    int boardSize = game->getBoardDimension();
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            delete guiBoard[i][j];
            guiBoard[i][j] = new FieldWidget(board.getField(i, j));
            boardLayout->addWidget(guiBoard[i][j], i, j);
            guiBoard[i][j]->draw();
        }
    }
    mainLayout->insertLayout(1, boardLayout);
    if (game->checkGameOver()) {
        undoButton->setEnabled(false);
        QMessageBox msgBox;
        msgBox.setText("Game Over");
        msgBox.exec();
    }
}

void GameWidget::keyPressed(int key) {
    game->play(key);
    drawBoard();
}

void GameWidget::resetGame() {
    undoButton->setEnabled(true);
    game->restart();
    drawBoard();
}

void GameWidget::undo() {
    game->undoMove();
    drawBoard();
}

void GameWidget::changeBoardSize(int size) {
    // delete the fields in the ui, so they won't just hang around in the background
    int boardSize = game->getBoardDimension();
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            delete guiBoard[i][j];
        }
    }
    guiBoard.clear();
    game = new Game(size);
    initBoard();
}

GameWidget::~GameWidget(){}
