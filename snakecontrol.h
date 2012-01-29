#ifndef SNAKECONTROL_H
#define SNAKECONTROL_H

class SnakeFunction;

class SnakeControl{

public:
    static const int TIMEOUT = 140;
    static int getMax(){ return SnakeControl::max; }
    static bool setMax(int x);

    SnakeControl();
    ~SnakeControl();

    SnakeFunction *randomSensor();
    SnakeFunction *randomAction();
    bool moveSnake();

    inline void increaseResult(){ ++counter; timeout = SnakeControl::TIMEOUT; }
    inline int getResult()const{ return counter; }
    
protected:    
    static int max;

    SnakeFunction **sf;
    int n, counter, timeout;

    SnakeFunction *randomFunction(int x, int y);
};

#endif // SNAKECONTROL_H
