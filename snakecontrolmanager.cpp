#include "snakecontrolmanager.h"
#include "snakecontrol.h"

SnakeControlManager::SnakeControlManager() : n(32), current(0), best(0)
{
    sc = new SnakeControl*[n];
    for(int i=0; i<n; ++i){
        sc[i] = new SnakeControl();
    }
}

SnakeControlManager::~SnakeControlManager(){
    for(int i=0; i<n; ++i){
        delete sc;
    }
    delete[] sc;
}

bool SnakeControlManager::runSnakes(){
    if(current < n && !sc[current]->moveSnake()){
        if(SnakeControl::setMax(sc[current]->getResult())){
            best = current;
        }
        ++current;
        return false;
    }
    return true;
}

void SnakeControlManager::increaseCurrentResult(){
    sc[current]->increaseResult();
}
