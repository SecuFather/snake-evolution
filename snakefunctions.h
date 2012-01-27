#ifndef SNAKEFUNCTIONS_H
#define SNAKEFUNCTIONS_H

#include "snake.h"

class SnakeFunction{
public:
    virtual int exec()=0;
    static Snake *snake;
};
Snake *SnakeFunction::snake = 0;

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

#endif // SNAKEFUNCTIONS_H
