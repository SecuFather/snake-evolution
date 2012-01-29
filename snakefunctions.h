#ifndef SNAKEFUNCTIONS_H
#define SNAKEFUNCTIONS_H

#include "snake.h"

class SnakeFunction{
public:
    virtual int exec()=0;
    static Snake *snake;

    static void setSnake(Snake *snake){
        SnakeFunction::snake = snake;
    }

    static const int LEAF = 77;
    static const int CRASH = 777;
    static const int FUNCTION_COUNT = 12;
    static const int ACTION_COUNT = 3;
    static const int SENSOR_COUNT = 9;
};

class IsMovingRight: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->getDirection() == Snake::MOVING_RIGHT); }
};

class IsMovingLeft: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->getDirection() == Snake::MOVING_LEFT); }
};
class IsMovingUp: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->getDirection() == Snake::MOVING_UP); }
};
class IsMovingDown: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->getDirection() == Snake::MOVING_DOWN); }
};
class IsFoodAhead: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->findFood() == Snake::FOOD_AHEAD); }
};
class IsFoodRight: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->findFood() == Snake::FOOD_RIGHT); }
};
class IsFoodLeft: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->findFood() == Snake::FOOD_LEFT); }
};
class IsDangerAhead: public SnakeFunction{
public:
    virtual int exec(){
        return (snake->sgn(snake->findDanger() & Snake::DANGER_AHEAD)+1)%2;
    }
};
class IsDangerLeft: public SnakeFunction{
public:
    virtual int exec(){
        return (snake->sgn(snake->findDanger() & Snake::DANGER_LEFT)+1)%2;
    }
};
class IsDangerRight: public SnakeFunction{
public:
    virtual int exec(){
        return (snake->sgn(snake->findDanger() & Snake::DANGER_RIGHT)+1)%2;
    }
};
class IsDangerTwoAhead: public SnakeFunction{
public:
    virtual int exec(){
        return (snake->sgn(snake->findDanger() & Snake::DANGER__TWO_AHEAD)+1)%2;
    }
};
class Progn: public SnakeFunction{
public:
    Progn() : result(0){}
    virtual int exec(){
        return result = (result + 1)%2;
    }
protected:
    int result;
};
class GoLeft: public SnakeFunction{
public:
    virtual int exec(){
        if(snake->move(Snake::GO_LEFT)){
            return SnakeFunction::LEAF;
        }else{
            return SnakeFunction::CRASH;
        }
    }
};
class GoRight: public SnakeFunction{
public:
    virtual int exec(){
        if(snake->move(Snake::GO_RIGHT)){
            return SnakeFunction::LEAF;
        }else{
            return SnakeFunction::CRASH;
        }
    }
};
class GoForward: public SnakeFunction{
public:
    virtual int exec(){
        if(snake->move(Snake::GO_FORWARD)){
            return SnakeFunction::LEAF;
        }else{
            return SnakeFunction::CRASH;
        }
    }
};

#endif // SNAKEFUNCTIONS_H
