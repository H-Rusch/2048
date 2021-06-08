#include "GameWidget.hpp"
#include "mainwindow.hpp"

#include <QApplication>
#include <ctime>
#include <iostream>

int main(int argc, char *argv[]) {
    srand((unsigned int) time(NULL));
    QApplication a(argc, argv);

    MainWindow window;
    window.show();
    // Set the size of the board here
    //GameWidget w(4);

    return a.exec();
}
