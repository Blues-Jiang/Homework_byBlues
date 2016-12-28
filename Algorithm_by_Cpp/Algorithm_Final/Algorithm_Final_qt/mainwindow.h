#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
//#include <QtWidgets>
//#include <qcolor.h>
//#include <qpainter.h>
#include <iostream>

#define INF 99999999

#define WHITE 1
#define BLACK 2
#define NONE 0
#define size 15

#define width 640
#define height 720
#define step 40
//#define step (width-40)/size

struct Point{
  int x;
  int y;
  int chess;
  int value;
  Point(){

  }
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::MainWindow *ui;
    int Num;
    int **chessboard;
    int **scoreBlack,**scoreWhite;

    void initial();
    void AI();
    int isWin(int, int);

    bool player;
};

#endif // MAINWINDOW_H
