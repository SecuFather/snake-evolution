#ifndef SNAKECONTROLMANAGER_H
#define SNAKECONTROLMANAGER_H

class SnakeControl;

class SnakeControlManager
{
public:
    SnakeControlManager();
    ~SnakeControlManager();

    bool runSnakes();
    void increaseCurrentResult();
    inline int getBest()const{ return best; }
protected:
    int n, current, best;
    SnakeControl **sc;
};

#endif // SNAKECONTROLMANAGER_H
