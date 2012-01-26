#ifndef SNAKEAREA_H
#define SNAKEAREA_H

#include <QDialog>
#include <QThread>

class Snake;
class QPainter;

namespace Ui {
class SnakeArea;
}
class SnakeArea;

class SnakeTimer : public QThread{
public:
    SnakeTimer(SnakeArea *sa, int delay=100) : sa(sa), delay(delay){ start(); }

    void run();
protected:    
    SnakeArea *sa;
    int delay;    
};

class SnakeArea : public QDialog
{
    Q_OBJECT
    
public:
    explicit SnakeArea(QWidget *parent = 0);
    ~SnakeArea();

    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *e);

    void resetKey();
    void insertFood();
    
    inline int getKey()const{ return key; }
    inline Snake *getSnake()const{ return snake; }

private:
    Ui::SnakeArea *ui;
protected:
    int colls, rows, *fields;
    Snake *snake;    
    SnakeTimer *st;
    int key;

    void initFields();
    void initPainter(QPainter *painter);
    void drawCells(QPainter *painter);
    QBrush getBrush(int i);        

    inline int xy(int x, int y)const { return y*colls + x; }    
};

#endif // SNAKEAREA_H
