#include "snakecontrolmanager.h"
#include "snakecontrol.h"

SnakeControlManager::SnakeControlManager() : n(PARENTS*ROWS), current(0),
    best(new int[n]), sortedSc(new int[n]),
    generation(1), attempts(32), att(0)
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
    if(att < attempts || (att=0) || ++current < n){
        if(!sc[current]->moveSnake()){
            if(++att == attempts){
                int res = sc[current]->getMyMax();
                SnakeControl::setMax(res);
                insert(res, best, sortedSc, current);
            }
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
    SnakeControl *temp = new SnakeControl(sc[sortedSc[0]]);
    for(int i=0; i<ROWS; ++i){
        delete sc[i];
    }
    sc[0] = new SnakeControl(temp);
    sc[1] = new SnakeControl(generation);

    for(int i=2; i<ROWS; ++i){
        sc[i] = new SnakeControl(temp);
        sc[i]->cross(0, i/2, i%2, true);
    }

    delete temp;
    resetBest();
}

void SnakeControlManager::resetBest(){
    QString r,z;
    for(int i=0; i<n; ++i){
        r.append(QString::number(sortedSc[i]) + ",");
        z.append(QString::number(best[i]) + ",");
    }
    qDebug("------------------------------");
    qDebug(r.toAscii());
    qDebug(z.toAscii());
    qDebug("------------------------------");
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

QString SnakeControlManager::getTree(){
    return sc[current-1]->getTree(current);
}
