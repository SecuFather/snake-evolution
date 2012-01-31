#ifndef SNAKECONTROL_H
#define SNAKECONTROL_H

class QString;
class SnakeFunction;

class SnakeControl{

public:
    static const int TIMEOUT = 240;
    static int getMax(){ return SnakeControl::max; }
    static bool setMax(int x);

    SnakeControl(int generation);
    SnakeControl(SnakeControl *sc);
    ~SnakeControl();

    SnakeFunction *randomSensor();
    SnakeFunction *randomAction();
    bool moveSnake();
    void cross(SnakeControl *src, int part, int inv, bool random=false);
    void increaseResult();
    QString getTree(int at);

    inline int getResult()const{ return counter; }
    inline int getGeneration()const{ return generation; }
    inline void setGeneration(int x){ if(x > generation) generation = x; }
    inline int getMyMax()const{ return myMax; }    
    
protected:    
    static int max;

    SnakeFunction **sf;
    int n, counter, timeout, generation, myMax;

    SnakeFunction *randomFunction(int x, int y);
};

#endif // SNAKECONTROL_H
