#include "snakearea.h"
#include "ui_snakearea.h"
#include "snakecontrolmanager.h"
#include "snakecontrol.h"
#include "snake.h"
#include "snakefunctions.h"

#include <QPainter>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>

SnakeArea::SnakeArea(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SnakeArea), colls(24), rows(12), fields(new int[colls*rows]),
    snake(new Snake(colls, rows, SnakeArea::START_LENGTH, Snake::MOVING_RIGHT, 420, fields)),
    key(snake->getDirection()), timer(new QTimer(this)), scm(new SnakeControlManager())
{
    ui->setupUi(this);    
    initFields();
    qsrand(QTime().currentTime().msecsTo(QTime(0,0)));
    insertFood();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(moveSnake()));
    timer->start(50);
    SnakeFunction::setSnake(snake);
    initList();
}

SnakeArea::~SnakeArea()
{
    delete timer;
    delete snake;
    delete[] fields;
    delete ui;        
}

void SnakeArea::paintEvent(QPaintEvent *){
    QPainter painter(this);
    initPainter(&painter);
    drawCells(&painter);
}

void SnakeArea::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
    case Qt::Key_Left:
        key = Snake::MOVING_LEFT;
        break;
    case Qt::Key_Up:
        key = Snake::MOVING_UP;
        break;
    case Qt::Key_Right:
        key = Snake::MOVING_RIGHT;
        break;
    case Qt::Key_Down:
        key = Snake::MOVING_DOWN;
        break;
    case Qt::Key_Space:
        if(timer->isActive()){
            timer->stop();
        }else{
            timer->start();
        }
        break;
    }

    return QDialog::keyPressEvent(e);
}

void SnakeArea::initFields(){
    for(int i=0; i<colls; ++i){
        for(int j=0; j<rows; ++j){
            fields[xy(i, j)] = Snake::FIELD_CODE; //background color
        }
    }
}

void SnakeArea::initPainter(QPainter *painter){
    painter->setRenderHint(QPainter::Antialiasing, true);    
}

void SnakeArea::drawCells(QPainter *painter){
    int cellWidth=ui->gameWidget->width()/colls;
    int cellHeight=ui->gameWidget->height()/rows;

    fields[snake->getLast()] = Snake::FIELD_CODE; //background color
    fields[snake->getFood()] = Snake::FOOD_CODE; //food's color
    fields[snake->getFirst()] = Snake::SNAKE_HEAD_CODE; //snake's head color

    for(int i=1; i<snake->getLenght(); ++i){
        fields[snake->getSnake()[i]] = Snake::SNAKE_CODE; //snake color
    }

    for(int i=0; i<colls; ++i){
        for(int j=0; j<rows; ++j){            
            painter->fillRect(i*cellWidth, j*cellHeight, cellWidth, cellHeight,
                              getBrush( fields[xy(i,j)] ));
        }
    }
}

QBrush SnakeArea::getBrush(int i){
    switch(i){
    case Snake::FIELD_CODE:
        return QBrush(Qt::white);
    case Snake::SNAKE_CODE:
        return QBrush(Qt::green);
    case Snake::SNAKE_HEAD_CODE:
        return QBrush(Qt::red);
    case Snake::FOOD_CODE:
        return QBrush(Qt::magenta);
    case Snake::DANGER_CODE:
        return QBrush(Qt::black);
    }
    return QBrush(Qt::yellow);
}

void SnakeArea::restart(){
    initFields();
    snake->restart(SnakeArea::START_LENGTH, Snake::MOVING_RIGHT);
}

void SnakeArea::initList(){
    ui->snakeList->setIconSize(QSize(30, 30));
    for(int i=0; i<SnakeControlManager::PARENTS; ++i){
        QListWidgetItem *item = new QListWidgetItem("no data yet", ui->snakeList);
        item->setIcon(QIcon::fromTheme("help-about"));
        item->setData(Qt::UserRole, i);
    }
}

void SnakeArea::updateInfo(){
    setWindowTitle("Snake #" + QString::number(scm->getCurrent()) + " is running | " +
                   "Best result: " + QString::number(SnakeControl::getMax()) + " | " +
                   "Generation: " + QString::number(scm->getGeneration()));
    for(int i=0; i<SnakeControlManager::PARENTS; ++i){
        ui->snakeList->item(i)->setText("Snake #" + QString::number(i+1) + ": " +
                                        "Generation: " + QString::number(scm->getGeneration(i)) + " | "
                                        "Best result: " + QString::number(scm->getMax(i)));
    }
}

void SnakeArea::insertFood(){
    int x = qrand()%(colls*rows);
    int *s = snake->getSnake();
    for(int i=0; i<snake->getLenght(); ++i){
        if(x == s[i] ||
                (x < SnakeArea::START_LENGTH + rows*colls/2 && x >= rows*colls/2)){
            i=-1;
            x = qrand()%(colls*rows);
        }
    }
    snake->setFood(x);
}

void SnakeArea::moveSnake(){        
    if(!scm->runSnakes()){
        updateInfo();
        restart();                        
    }
    if(snake->isFoodEaten()){
        insertFood();
        scm->increaseCurrentResult();
    }
    update();
}

void SnakeArea::resetKey(){
    key = snake->getDirection();
}


