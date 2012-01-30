#include "snakecontrol.h"
#include "snakefunctions.h"
#include <QTime>

int SnakeControl::max = -1;

SnakeControl::SnakeControl(int generation) :
    n(65535), counter(0), timeout(SnakeControl::TIMEOUT), generation(generation), myMax(0){
    sf = new SnakeFunction*[n];
    for(int i=0; i<n/2; ++i){
        sf[i] = randomSensor();
    }
    for(int i=n/2; i<n; ++i){
        sf[i] = randomAction();

    }
}

SnakeControl::SnakeControl(SnakeControl *sc) :
    n(sc->n), counter(0), timeout(sc->timeout), generation(sc->generation), myMax(sc->myMax){

    sf = new SnakeFunction*[n];
    for(int i=0; i<n; ++i){
        sf[i] = sc->sf[i]->copy();
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
    int t = 0;
    int ans = sf[pos]->exec();    

    while(ans != SnakeFunction::LEAF && ans != SnakeFunction::CRASH && pos < n/2){
        t = 2*(pos-k+1);
        k *= 2;
        pos = t + k-1 + ans;
        ans = sf[pos]->exec();        
    }
    if(ans == SnakeFunction::CRASH || --timeout == 0){
        return false;
    }else{
        return true;
    }
}

void SnakeControl::cross(SnakeControl *src, int part, int inv){
    int pos=0;
    int k=1;
    int p=1;
    int t=0;

    for(int i=0; i<part; ++i){
        t = 2*(pos-k+1);
        k *= 2;
        pos = t + k-1 + inv;
    }
    delete sf[pos];
    sf[pos] = src->sf[pos]->copy();    

    while(pos < n/2){
        t = 2*(pos-k+1);
        k *= 2;
        pos = t + k-1;
        for(int j=pos; j<pos+p; ++j){
            delete sf[pos];
            sf[pos] = src->sf[pos]->copy();
        }
        p *= 2;
    }
    setGeneration(src->getGeneration());
}

void SnakeControl::increaseResult(){{
    if(++counter > myMax){
        myMax = counter;
    }
    timeout = SnakeControl::TIMEOUT; }
}

bool SnakeControl::setMax(int x){
    if(x > SnakeControl::max){
        SnakeControl::max = x;
        return true;
    }else{
        return false;
    }
}
