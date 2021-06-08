#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMenuBar>
#include <QKeyEvent>

#include "GameWidget.hpp"

class MainWindow : public QMainWindow {

    Q_OBJECT

private:
    // elements in the menu bar. clicking those will set the board size to the corresponding size
    QMenu *sizeMenu;
    QAction *size4;
    QAction *size5;
    QAction *size6;
    QAction *size7;
    QAction *size8;

    GameWidget *gameWidget;

public:
    MainWindow();

    // pass down the keyboard input
    void keyPressEvent(QKeyEvent *event);

public slots:
    // those make sure to call the function in the gameWidget which initialize a board of the right size
    void changeTo4();
    void changeTo5();
    void changeTo6();
    void changeTo7();
    void changeTo8();
};

#endif // MAINWINDOW_HPP
