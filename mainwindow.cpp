#include "mainwindow.hpp"
#include "GameWidget.hpp"

MainWindow::MainWindow() {
    // create gameWidget and set it as the central widget of the main window
    gameWidget = new GameWidget(5);
    setCentralWidget(gameWidget);

    resize(600, 650);

    // create actions
    size4 = new QAction(tr("4 x 4"), this);
    connect(size4, SIGNAL(triggered()), this, SLOT(changeTo4()));
    size5 = new QAction(tr("5 x 5"), this);
    connect(size5, SIGNAL(triggered()), this, SLOT(changeTo5()));
    size6 = new QAction(tr("6 x 6"), this);
    connect(size6, SIGNAL(triggered()), this, SLOT(changeTo6()));
    size7 = new QAction(tr("7 x 7"), this);
    connect(size7, SIGNAL(triggered()), this, SLOT(changeTo7()));
    size8 = new QAction(tr("8 x 8"), this);
    connect(size8, SIGNAL(triggered()), this, SLOT(changeTo8()));

    // create menu
    sizeMenu = menuBar()->addMenu(tr("Board Size"));
    sizeMenu->addAction(size4);
    sizeMenu->addAction(size5);
    sizeMenu->addAction(size6);
    sizeMenu->addAction(size7);
    sizeMenu->addAction(size8);
}

void MainWindow::changeTo4() {
    gameWidget->changeBoardSize(4);
}

void MainWindow::changeTo5() {
    gameWidget->changeBoardSize(5);
}

void MainWindow::changeTo6() {
    gameWidget->changeBoardSize(6);
}

void MainWindow::changeTo7() {
    gameWidget->changeBoardSize(7);
}

void MainWindow::changeTo8() {
    gameWidget->changeBoardSize(8);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch(event->key()){
        case Qt::Key_Right:
            gameWidget->keyPressed(0);
            break;
        case Qt::Key_Up:
            gameWidget->keyPressed(1);
            break;
        case Qt::Key_Left:
            gameWidget->keyPressed(2);
            break;
        case Qt::Key_Down:
            gameWidget->keyPressed(3);
            break;
    }
}
