#include "snake.h"

Snake::Snake(int colls, int rows, int xy0, int d0, int food):
    colls(colls), rows(rows), length(xy0+1), snake(new int[colls*rows]),
    direction(d0), last(0), food(food), foodEaten(false)
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

bool Snake::restart(int xy0, int d0){
    length = xy0;
    direction = d0;
    for(int i=0; i<xy0; ++i){
        snake[i] = xy0-1-i;
    }
}
