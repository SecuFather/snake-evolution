#ifndef SNAKEFUNCTIONS_H
#define SNAKEFUNCTIONS_H

#include "snake.h"

class SnakeFunction{
public:
    virtual int exec()=0;
    virtual SnakeFunction *copy()=0;
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
    virtual SnakeFunction *copy(){ return new IsMovingRight(); }
};

class IsMovingLeft: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->getDirection() == Snake::MOVING_LEFT); }
    virtual SnakeFunction *copy(){ return new IsMovingLeft(); }
};
class IsMovingUp: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->getDirection() == Snake::MOVING_UP); }
    virtual SnakeFunction *copy(){ return new IsMovingUp; }
};
class IsMovingDown: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->getDirection() == Snake::MOVING_DOWN); }
    virtual SnakeFunction *copy(){ return new IsMovingDown; }
};
class IsFoodAhead: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->findFood() == Snake::FOOD_AHEAD); }
    virtual SnakeFunction *copy(){ return new IsFoodAhead(); }
};
class IsFoodRight: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->findFood() == Snake::FOOD_RIGHT); }
    virtual SnakeFunction *copy(){ return new IsFoodRight(); }
};
class IsFoodLeft: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->findFood() == Snake::FOOD_LEFT); }
    virtual SnakeFunction *copy(){ return new IsFoodLeft(); }
};
class IsDangerAhead: public SnakeFunction{
public:
    virtual int exec(){
        return (snake->sgn(snake->findDanger() & Snake::DANGER_AHEAD)+1)%2;
    }
    virtual SnakeFunction *copy(){ return new IsDangerAhead(); }
};
class IsDangerLeft: public SnakeFunction{
public:
    virtual int exec(){
        return (snake->sgn(snake->findDanger() & Snake::DANGER_LEFT)+1)%2;
    }
    virtual SnakeFunction *copy(){ return new IsDangerLeft(); }
};
class IsDangerRight: public SnakeFunction{
public:
    virtual int exec(){
        return (snake->sgn(snake->findDanger() & Snake::DANGER_RIGHT)+1)%2;
    }
    virtual SnakeFunction *copy(){ return new IsDangerRight(); }
};
class IsDangerTwoAhead: public SnakeFunction{
public:
    virtual int exec(){
        return (snake->sgn(snake->findDanger() & Snake::DANGER__TWO_AHEAD)+1)%2;
    }
    virtual SnakeFunction *copy(){ return new IsDangerTwoAhead(); }
};
class Progn: public SnakeFunction{
public:
    Progn() : result(0){}
    virtual int exec(){
        return result = (result + 1)%2;
    }
    virtual SnakeFunction *copy(){ return new Progn(); }
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
    virtual SnakeFunction *copy(){ return new GoLeft(); }
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
    virtual SnakeFunction *copy(){ return new GoRight(); }
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
    virtual SnakeFunction *copy(){ return new GoForward(); }
};

#endif // SNAKEFUNCTIONS_H
