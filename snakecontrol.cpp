#include "snakecontrol.h"
#include "snakefunctions.h"
#include <QTime>

SnakeControl::SnakeControl() : n(65535){
    sf = new SnakeFunction*[n];
    for(int i=0; i<n/2; ++i){
        sf[i] = randomSensor();
    }
    for(int i=n/2; i<n; ++i){
        sf[i] = randomAction();
    }
}

SnakeControl::~SnakeControl(){
    for(int i=0; i<n; ++i){
        delete sf[i];
    }
    delete[] sf;
}

SnakeFunction *SnakeControl::randomFunction(int x, int y){
    switch(qrand() % x + y){
    case 0:
        return new GoLeft();
        break;
    case 1:
        return new GoRight();
        break;
    case 2:
        return new GoForward();
        break;
    case 3:
        return new IsMovingRight();
        break;
    case 4:
        return new IsDangerAhead();
        break;
    case 5:
        return new IsDangerTwoAhead();
        break;
    case 6:
        return new IsDangerLeft();
        break;
    case 7:
        return new IsDangerRight();
        break;
    case 8:
        return new Progn();
        break;
    case 9:
        return new IsMovingLeft();
        break;
    case 10:
        return new IsMovingUp();
        break;
    case 11:
        return new IsMovingDown();
        break;

    }
    return 0;
}

SnakeFunction *SnakeControl::randomSensor(){
    return randomFunction(SnakeFunction::SENSOR_COUNT, SnakeFunction::ACTION_COUNT);
}

SnakeFunction *SnakeControl::randomAction(){
    return randomFunction(SnakeFunction::ACTION_COUNT, 0);
}

bool SnakeControl::moveSnake(){
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
