#include "snake.h"

Snake::Snake(int colls, int rows, int xy0, int d0, int food, int *fields):
    colls(colls), rows(rows), length(xy0+1), snake(new int[colls*rows]),
    direction(d0), last(0), food(food), foodEaten(false), fields(fields)
{
    for(int i=0; i<length; ++i){
        snake[i] = length-1-i;
    }
}

Snake::~Snake(){    
    delete[] snake;
}

bool Snake::move(int order){
    if(abs(order) > 1){
        order = -(order % 2);
    }
    foodEaten = false;
    direction = (direction + order + 4)%4;
    int temp;
    last = snake[length-1];

    switch(direction){
    case MOVING_LEFT:
        if(snake[0] % colls){
            temp = snake[0]-1;
        }else{
            return false;
        }
        break;
    case MOVING_UP:
        if(snake[0] / colls){
            temp = snake[0]-colls;
        }else{
            return false;
        }
        break;
    case MOVING_RIGHT:
        if((snake[0]+1) % colls){
            temp = snake[0]+1;
        }else{
            return false;
        }
        break;
    case MOVING_DOWN:
        if(snake[0] / colls != rows - 1){
            temp = snake[0]+colls;
        }else{
            return false;
        }
        break;
    }
    if(snake[0] == food){
        foodEaten = true;
        ++length;
    }
    for(int i=0; i<length; ++i){
        if(temp == snake[i]){
            return false;
        }
    }
    for(int i=length-1; i>0; --i){
        snake[i] = snake[i-1];
    }
    snake[0] = temp;        

    return true;
}

bool Snake::move2(int dir){
    return move(dir - direction);
}

void Snake::restart(int xy0, int d0){
    length = xy0;
    direction = d0;
    for(int i=0; i<xy0; ++i){
        snake[i] = xy0-1-i;
    }
}

int Snake::findFood(){
    switch(direction){
    case Snake::MOVING_RIGHT:
    case Snake::MOVING_LEFT:
        if(sgn(((snake[0] % colls) - (food % colls)))*(1-direction/2*2) < 0){
            return Snake::FOOD_BEHIND;
        }else{
            if(sgn(((snake[0] / colls) - (food / colls)))*(1-direction/2*2) < 0){
                return Snake::FOOD_LEFT;
            }else{
                if((snake[0] / colls) == (food / colls)){
                    return Snake::FOOD_AHEAD;
                }else{
                    return Snake::FOOD_RIGHT;
                }
            }
        }
        break;
    case Snake::MOVING_UP:
    case Snake::MOVING_DOWN:
        if(sgn(((snake[0] / colls) - (food / colls)))*(1-direction/2*2) < 0){
            return Snake::FOOD_BEHIND;
        }else{
            if(sgn(((snake[0] % colls) - (food % colls)))*(1-direction/2*2) > 0){
                return Snake::FOOD_LEFT;
            }else{
                if((snake[0] % colls) == (food % colls)){
                    return Snake::FOOD_AHEAD;
                }else{
                    return Snake::FOOD_RIGHT;
                }
            }
        }
        break;
    }
}

int Snake::findDanger(){
    int danger = 0;
    if(snake[0] % colls == 0 || fields[snake[0]-1] > Snake::FOOD_CODE){
        switch(direction){
        case MOVING_LEFT:
            danger += Snake::DANGER_AHEAD;
            break;
        case MOVING_UP:
            danger += Snake::DANGER_LEFT;
            break;
        case MOVING_DOWN:
            danger += Snake::DANGER_RIGHT;
            break;
        }
    }
    if(direction == MOVING_LEFT &&
            (snake[0] % colls == 0 ||
            (snake[0]-1) % colls == 0 ||
            fields[snake[0]-2] > Snake::FOOD_CODE) ){
        danger += Snake::DANGER__TWO_AHEAD;
    }
    if((snake[0]+1) % colls == 0 || fields[snake[0]+1] > Snake::FOOD_CODE){
        switch(direction){
        case MOVING_RIGHT:
            danger += Snake::DANGER_AHEAD;
            break;
        case MOVING_DOWN:
            danger += Snake::DANGER_LEFT;
            break;
        case MOVING_UP:
            danger += Snake::DANGER_RIGHT;
            break;
        }
    }
    if(direction == MOVING_RIGHT &&
            ((snake[0]+1) % colls == 0 ||
            (snake[0]+2) % colls == 0 ||
            fields[snake[0]+2] > Snake::FOOD_CODE) ){
        danger += Snake::DANGER__TWO_AHEAD;
    }
    if(snake[0] / colls == 0|| fields[snake[0]-colls] > Snake::FOOD_CODE){
        switch(direction){
        case MOVING_UP:
            danger += Snake::DANGER_AHEAD;
            break;
        case MOVING_RIGHT:
            danger += Snake::DANGER_LEFT;
            break;
        case MOVING_LEFT:
            danger += Snake::DANGER_RIGHT;
            break;
        }
    }
    if(direction == MOVING_UP &&
            (snake[0] / colls == 0 ||
            (snake[0]-colls) / colls == 0 ||
            fields[snake[0]-colls-colls] > Snake::FOOD_CODE) ){
        danger += Snake::DANGER__TWO_AHEAD;
    }
    if(snake[0] / colls == rows - 1 || fields[snake[0]+colls] > Snake::FOOD_CODE){
        switch(direction){
        case MOVING_DOWN:
            danger += Snake::DANGER_AHEAD;
            break;
        case MOVING_LEFT:
            danger += Snake::DANGER_LEFT;
            break;
        case MOVING_RIGHT:
            danger += Snake::DANGER_RIGHT;
            break;
        }
    }
    if(direction == MOVING_DOWN &&
            (snake[0] / colls == rows-1 ||
            (snake[0]+colls) / colls == rows-1 ||
            fields[snake[0]+colls+colls] > Snake::FOOD_CODE) ){
        danger += Snake::DANGER__TWO_AHEAD;
    }

    return danger;
}


