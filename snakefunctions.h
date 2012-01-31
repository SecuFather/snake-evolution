#ifndef SNAKEFUNCTIONS_H
#define SNAKEFUNCTIONS_H

#include "snake.h"
#include <QString>

class SnakeFunction{
public:
    virtual int exec()=0;
    virtual SnakeFunction *copy()=0;
    virtual QString name()=0;
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
    virtual QString name(){ return "IMR"; }
};

class IsMovingLeft: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->getDirection() == Snake::MOVING_LEFT); }
    virtual SnakeFunction *copy(){ return new IsMovingLeft(); }
    virtual QString name(){ return "IML"; }
};
class IsMovingUp: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->getDirection() == Snake::MOVING_UP); }
    virtual SnakeFunction *copy(){ return new IsMovingUp; }
    virtual QString name(){ return "IMU"; }
};
class IsMovingDown: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->getDirection() == Snake::MOVING_DOWN); }
    virtual SnakeFunction *copy(){ return new IsMovingDown; }
    virtual QString name(){ return "IMD"; }
};
class IsFoodAhead: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->findFood() == Snake::FOOD_AHEAD); }
    virtual SnakeFunction *copy(){ return new IsFoodAhead(); }
    virtual QString name(){ return "IFA"; }
};
class IsFoodRight: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->findFood() == Snake::FOOD_RIGHT); }
    virtual SnakeFunction *copy(){ return new IsFoodRight(); }
    virtual QString name(){ return "IFR"; }
};
class IsFoodLeft: public SnakeFunction{
public:
    virtual int exec(){ return (int)!(snake->findFood() == Snake::FOOD_LEFT); }
    virtual SnakeFunction *copy(){ return new IsFoodLeft(); }
    virtual QString name(){ return "IFL"; }
};
class IsDangerAhead: public SnakeFunction{
public:
    virtual int exec(){
        return (snake->sgn(snake->findDanger() & Snake::DANGER_AHEAD)+1)%2;
    }
    virtual SnakeFunction *copy(){ return new IsDangerAhead(); }
    virtual QString name(){ return "IDA"; }
};
class IsDangerLeft: public SnakeFunction{
public:
    virtual int exec(){
        return (snake->sgn(snake->findDanger() & Snake::DANGER_LEFT)+1)%2;
    }
    virtual SnakeFunction *copy(){ return new IsDangerLeft(); }
    virtual QString name(){ return "IDL"; }
};
class IsDangerRight: public SnakeFunction{
public:
    virtual int exec(){
        return (snake->sgn(snake->findDanger() & Snake::DANGER_RIGHT)+1)%2;
    }
    virtual SnakeFunction *copy(){ return new IsDangerRight(); }
    virtual QString name(){ return "IDR"; }
};
class IsDangerTwoAhead: public SnakeFunction{
public:
    virtual int exec(){
        return (snake->sgn(snake->findDanger() & Snake::DANGER__TWO_AHEAD)+1)%2;
    }
    virtual SnakeFunction *copy(){ return new IsDangerTwoAhead(); }
    virtual QString name(){ return "IDTA"; }
};
class Progn: public SnakeFunction{
public:
    Progn() : result(0){}
    virtual int exec(){
        return result = (result + 1)%2;
    }
    virtual SnakeFunction *copy(){ return new Progn(); }
    virtual QString name(){ return "P"; }
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
    virtual QString name(){ return "GL"; }
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
    virtual QString name(){ return "GR"; }
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
    virtual QString name(){ return "GF"; }
};

#endif // SNAKEFUNCTIONS_H
