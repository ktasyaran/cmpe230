#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTime>
#include <algorithm>
/*
 * Main window for game. Resized window for game.
 * */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Card Match Game");
    w.resize(800,800);
    w.show();

    return a.exec();
}
