#include "snakecontrolmanager.h"
#include "snakecontrol.h"

SnakeControlManager::SnakeControlManager() : n(16), current(0), best(new int[n]), sortedSc(new int[n]),
    generation(1)
{            
    sc = new SnakeControl*[n];
    for(int i=0; i<n; ++i){
        sc[i] = new SnakeControl(generation);
    }
}

SnakeControlManager::~SnakeControlManager(){    
    delete[] sortedSc;
    delete[] best;
    for(int i=0; i<n; ++i){
        delete sc;
    }
    delete[] sc;
}

bool SnakeControlManager::runSnakes(){
    if(current < n){
        if(!sc[current]->moveSnake()){
            int tmp = sc[current]->getResult();
            SnakeControl::setMax(tmp);
            insert(tmp, best, sortedSc, current++);
            return false;
        }
    }else{
        cross();
    }
    return true;
}

void SnakeControlManager::increaseCurrentResult(){
    sc[current]->increaseResult();
}

void SnakeControlManager::insert(int x, int *tabBest, int *tabBestIndex, int size){
    int ip=0, ik=size, i;

    while(ik>ip){
        i = (ip+ik)/2;
        if(tabBest[i] < x){
            ik = i;
        }else{
            ip = i+1;
        }
    }
    for(int j=size; j>ip; --j){
        tabBest[j] = tabBest[j-1];
        tabBestIndex[j] = tabBestIndex[j-1];
    }
    tabBest[ip] = x;
    tabBestIndex[ip] = size;
}

void SnakeControlManager::cross(){
    SnakeControl **temp = new SnakeControl*[4];
    int half=n/2, quarter=n/4, threeQuearters = n-quarter;
    ++generation;

    for(int i=0; i<quarter; ++i){
        if(sc[sortedSc[i]]->getMyMax()){
            temp[i] = new SnakeControl(sc[sortedSc[i]]);
        }else{
            temp[i] = new SnakeControl(generation);
        }
    }
    for(int i=0; i<n; ++i){
        delete sc[i];
    }
    if(SnakeControl::getMax()){
        for(int i=0; i<quarter; ++i){
            sc[i] = temp[i];
        }
        for(int i=0; i<quarter; ++i){
            sc[i+quarter] = new SnakeControl(temp[i]);
            sc[i+half] = new SnakeControl(temp[i]);
            sc[i+threeQuearters] = new SnakeControl(generation);
            for(int j=1; j<quarter; ++j){
                sc[i+quarter]->cross(sc[(i+j)%4], j, 0);
                sc[i+half]->cross(sc[(i+j)%4], j, 1);
            }

        }
    }else{
        for(int i=0; i<n; ++i){
            sc[i] = new SnakeControl(generation);
        }
    }

    delete[] temp;
    resetBest();
}

void SnakeControlManager::resetBest(){
    for(int i=0; i<n; ++i){
        best[i] = 0;
        sortedSc[i] = 0;
    }
    current=0;    
}

int SnakeControlManager::getGeneration(int at){
    return sc[at]->getGeneration();
}
int SnakeControlManager::getMax(int at){
    return sc[at]->getMyMax();
}
