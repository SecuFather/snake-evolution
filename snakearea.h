#ifndef SNAKEAREA_H
#define SNAKEAREA_H

#include <QDialog>
#include <QThread>

class Snake;
class QPainter;
class QTimer;
class SnakeControlManager;

namespace Ui {
class SnakeArea;
}

class SnakeArea : public QDialog
{
    Q_OBJECT
    
public:
    static const int START_LENGTH = 10;

    explicit SnakeArea(QWidget *parent = 0);
    ~SnakeArea();

    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *e);

    void resetKey();
    void insertFood();
public slots:
    void moveSnake();
    void pauseSnake();

private:
    Ui::SnakeArea *ui;
protected:
    int colls, rows, *fields;
    Snake *snake;        
    int key;
    QTimer *timer;
    SnakeControlManager *scm;
    bool displayOn;

    void initFields();
    void initPainter(QPainter *painter);
    void drawCells(QPainter *painter);
    QBrush getBrush(int i);        
    void restart();    
    void initList();
    void updateInfo();

    inline int xy(int x, int y)const { return y*colls + x; }    
};

#endif // SNAKEAREA_H
