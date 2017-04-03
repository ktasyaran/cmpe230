#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
#include <QTimer>
#include <algorithm>
#include <QStringList>
/*
 * Header of our game file. Widgets, scores and player infos are declared here. They will be used in source file.
 * For this file, there will not be much comment. Variables etc. will be explained in source file.
 * */
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QWidget *window;
    QButtonGroup *buttongroup;
    QPushButton *button[30] ; //Array of buttons.
    QHBoxLayout *layout;
    QHBoxLayout *board;
    QVBoxLayout *gameInfo;
    QVBoxLayout *cards;
    QVBoxLayout *players;
    QVBoxLayout *scores;
    QHBoxLayout *playerNames;
    QVBoxLayout *tim;
    QVBoxLayout *p1i;
    QVBoxLayout *p2i;
    QVBoxLayout *game;
    QHBoxLayout *upi;
    QHBoxLayout *sctim;
    QPushButton *newG;
    QPushButton *prevR;
    QPushButton *nextR;
    QPushButton *Exit;
     QList<int> rands;
    QLabel *sc;
    QLabel *ti;
    QLabel *p1s;
    QLabel *p1t;
    QLabel *p2s;
    QLabel *p2t;
   QLabel *pla1;
    QLabel *pla2;
    QLabel *pla3;
    QLabel *label_1;
    QLabel *label_2;
    int countD;
    int highest;
    int gameCount;
    int P1Score;
    int P2Score;
    int P1Time;
    int P2Time;
    int playerTurn;
    int TracedGame;
    QTime time;
    int isFree[30]; //Checking whether a point is free or not.
    QList<int> isAllUsed;

    QString buttonNames[30]; //Array for button names.



     QList<QString> myWords;

     QList<QList<int> >playerStats;
     QString gam;
     QString hi;
     int count;
    QList<QPair<QPushButton*,int>> controllerArray;

    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
    void handler(int i);
    void Quit();
    void newGame();
    void showPreviousGame();
    void showNextGame();
    void checker();
};
#endif // MAINWINDOW_H
