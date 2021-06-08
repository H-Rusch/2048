#ifndef GAMEWIDGET_HPP
#define GAMEWIDGET_HPP

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QAction>
#include <QMenu>
#include <QMainWindow>

#include "Game.hpp"
#include "FieldWidget.hpp"

class GameWidget : public QWidget {
    // has to be included so the slot connection works
    Q_OBJECT

private:
    Game* game;
    QGridLayout *boardLayout;
    QHBoxLayout *topLayout;
    QVBoxLayout *mainLayout;
    QVector<QVector<FieldWidget*>> guiBoard;
    QPushButton *newGameButton;
    QPushButton *undoButton;
    QAction *boardSize;
    QMenu *sizeMenu;

    // reserve enough space in the list of FieldWidgets and draw the board for the first time
    void initBoard();

    // fill the grid of fields in the UI
    void drawBoard();

public:
    // constructor which initializes the grid of fields in the UI and sets all the buttons
    GameWidget(int size);

    ~GameWidget();

public slots:
    // reset the game state
    void resetGame();

    // undo the last move
    void undo();

    // open dialogue to change size of the board
    void changeBoardSize(int size);

    // based on the code of a key, call the corresponding function in the game to do that move
    void keyPressed(int key);
};

#endif // GAMEWIDGET_HPP
