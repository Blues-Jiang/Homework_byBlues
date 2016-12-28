#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    resize(width, height);
    initial();
}

MainWindow::~MainWindow(){
    for(int i=0;i<size;i++){
      delete[] chessboard[i];
      delete[] scoreBlack[i];
      delete[] scoreWhite[i];
    }
    delete[] chessboard;
    delete[] scoreBlack;
    delete[] scoreWhite;
    delete ui;
}

void MainWindow::initial(){
  chessboard = new int*[size];
  scoreWhite = new int*[size];
  scoreBlack = new int*[size];
  Num = 0;
  for(int i=0;i<size;i++){
    chessboard[i] = new int[size];
    scoreWhite[i] = new int[size];
    scoreBlack[i] = new int[size];
    for(int j=0;j<size;j++){
      chessboard[i][j] = NONE;
      scoreBlack[i][j] = 0;
      scoreWhite[i][j] = 0;
    }
  }
  //memset(chessboard, NONE, 15 * 15 * sizeof(int));
  player = false;//false ->BLACK round; true -> WHITE round
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    //p.QPainter::setBackgroundColor(QColor::QColor(0,195,255));
    p.setRenderHint(QPainter::Antialiasing, true);
    int i, j;
    for (i = 0; i <= size; i++){
        p.drawLine(20, 20 + i*step, width-20, 20 + i*step);
        p.drawLine(20 + i*step, 20, 20 + i*step, width-20);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            if(chessboard[i][j] == BLACK){
                //std::cout<<"black"<<std::endl;
                brush.setColor(Qt::black);
                p.setBrush(brush);
                p.drawEllipse(QPoint((i+1)*step, (j+1)*step), 15, 15);
                //std::cout<<"done"<<std::endl;
            }
            else if(chessboard[i][j] == WHITE){
                //std::cout<<"white"<<std::endl;
                brush.setColor(Qt::white);
                p.setBrush(brush);
                p.drawEllipse(QPoint((i+1)*step, (j+1)*step), 15, 15);
                //std::cout<<"Done"<<std::endl;
            }
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e){
    int x, y;
    if(e->x() >= 20 && e->x() < width-20 && e->y() >= 20 && e->y() < width-20){
        x = (e->x() - 20) / step;
        y = (e->y() - 20) / step;
        //std::cout<<"x:"<<x<<",y:"<<y<<std::endl;
        //std::cout<<chessboard[x][y]<<std::endl;
        if (chessboard[x][y] == NONE){
            chessboard[x][y] = player?WHITE:BLACK;
            player = !player;
            Num++;
            int temp=isWin(x, y);
            if(temp != NONE){
                update();
                setEnabled(false);
                if(temp == WHITE)     QMessageBox::information(this, "Game over", "White Win", QMessageBox::Ok);
                else if(temp == BLACK)QMessageBox::information(this, "Game over", "Black Win", QMessageBox::Ok);
            }
        }
    }
    update();
}

int MainWindow::isWin(int x, int y){
     //return f1(x, y) || f2(x, y) || f3(x, y) || f4(x ,y);
     if(chessboard[x][y] == NONE) return NONE;
     int temp=chessboard[x][y];
     for (int i = 0; i < 5; i++){
         if(y - i >= 0 && y + 4 - i < size &&
            chessboard[x][y - i] == chessboard[x][y + 1 - i] &&
            chessboard[x][y - i] == chessboard[x][y + 2 - i] &&
            chessboard[x][y - i] == chessboard[x][y + 3 - i] &&
            chessboard[x][y - i] == chessboard[x][y + 4 - i])
            return temp;
     }
     for (int i = 0; i < 5; i++){
         if(x - i >= 0 && x + 4 - i < size &&
            chessboard[x - i][y] == chessboard[x + 1 - i][y] &&
            chessboard[x - i][y] == chessboard[x + 2 - i][y] &&
            chessboard[x - i][y] == chessboard[x + 3 - i][y] &&
            chessboard[x - i][y] == chessboard[x + 4 - i][y])
            return temp;
     }
     for (int i = 0; i < 5; i++){
         if(x - i >= 0 && y - i >= 0 &&
            x + 4 - i < size && y + 4 - i < size &&
            chessboard[x - i][y - i] == chessboard[x + 1 - i][y + 1 - i] &&
            chessboard[x - i][y - i] == chessboard[x + 2 - i][y + 2 - i] &&
            chessboard[x - i][y - i] == chessboard[x + 3 - i][y + 3 - i] &&
            chessboard[x - i][y - i] == chessboard[x + 4 - i][y + 4 - i])
            return temp;
     }
     for (int i = 0; i < 5; i++){
         if(x + i < size && y - i >= 0 &&
            x - 4 + i >= 0 && y + 4 - i < size &&
            chessboard[x + i][y - i] == chessboard[x - 1 + i][y + 1 - i] &&
            chessboard[x + i][y - i] == chessboard[x - 2 + i][y + 2 - i] &&
            chessboard[x + i][y - i] == chessboard[x - 3 + i][y + 3 - i] &&
            chessboard[x + i][y - i] == chessboard[x - 4 + i][y + 4 - i])
            return temp;
     }
     return NONE;

}

void MainWindow::AI(){

}
