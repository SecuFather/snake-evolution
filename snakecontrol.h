#ifndef SNAKECONTROL_H
#define SNAKECONTROL_H

class SnakeFunction;

class SnakeControl{

public:
    SnakeControl();
    ~SnakeControl();

    SnakeFunction *randomSensor();
    SnakeFunction *randomAction();
    bool moveSnake();
    
protected:    
    SnakeFunction **sf;
    int n;

    SnakeFunction *randomFunction(int x, int y);
};

#endif // SNAKECONTROL_H
