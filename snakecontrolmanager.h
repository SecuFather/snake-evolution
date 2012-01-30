#ifndef SNAKECONTROLMANAGER_H
#define SNAKECONTROLMANAGER_H

#include <QApplication>
class SnakeControl;

class SnakeControlManager
{
public:
    SnakeControlManager();
    ~SnakeControlManager();

    bool runSnakes();
    void increaseCurrentResult();    
    void insert(int x, int *tabBest, int *tabBestIndex, int size);
    void cross();
    void resetBest();    

    inline int getBest()const{ return sortedSc[0]; }
    inline int getGeneration()const{ return generation; }

protected:
    int n, current, *best, *sortedSc, generation;
    SnakeControl **sc;
};

#endif // SNAKECONTROLMANAGER_H
