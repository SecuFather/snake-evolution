#ifndef SNAKECONTROL_H
#define SNAKECONTROL_H

#include "snakefunctions.h"

class SnakeControl
{

public:
    SnakeControl(){
        n=31;
        sf = new SnakeFunction*[n];
        sf[0] = new IsFoodAhead();
        sf[1] = new GoForward();
        sf[2] = new IsDangerAhead();
        sf[5] = new GoRight();
        sf[6] = new IsFoodRight();
        sf[11] = new GoLeft();
        sf[12] = new GoRight();
        sf[13] = new GoRight();
        sf[14] = new IsFoodLeft();
        sf[29] = new GoLeft();
        sf[30] = new GoForward();
    }
    bool moveSnake(){
        int pos = 0;
        int k = 1;
        int ans = sf[pos]->exec();

        while(ans != SnakeFunction::LEAF && ans != SnakeFunction::CRASH && pos < n){
            pos += k + (pos+1)/2 + ans;
            ans = sf[pos]->exec();
            k *= 2;
        }
        return ans != SnakeFunction::CRASH;
    }
    
protected:
    SnakeFunction **sf;
    int n;
};

#endif // SNAKECONTROL_H
