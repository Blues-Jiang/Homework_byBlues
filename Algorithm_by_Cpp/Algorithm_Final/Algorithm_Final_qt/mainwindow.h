#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
//#include <QtWidgets>
//#include <qcolor.h>
//#include <qpainter.h>
#include <iostream>

#define WHITE 1
#define BLACK 2
#define NONE 0
#define size 15

#define width 640
#define height 720
#define step 40
//#define step (width-40)/size

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
    int** chessboard;
    void initial();
    int isWin(int, int);
    int f1(int, int);
    int f2(int, int);
    int f3(int, int);
    int f4(int, int);
    bool player;
};

#endif // MAINWINDOW_H
