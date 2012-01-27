#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
public:
    static const int MOVING_LEFT = 0;
    static const int MOVING_UP = 1;
    static const int MOVING_RIGHT = 2;
    static const int MOVING_DOWN = 3;

    static const int GO_LEFT = -1;
    static const int GO_FORWARD = 0;
    static const int GO_RIGHT = 1;

    Snake(int colls, int rows, int xy0, int d0, int food);
    ~Snake();

    bool move(int order);
    bool move2(int dir);
    bool restart(int xy0, int d0);

    inline int abs(int x)const{ return x<0 ? -x : x; }
    inline int getDirection()const{ return direction; }
    inline int *getSnake()const{ return snake; }
    inline int getLenght()const{ return length; }
    inline int getFirst()const{ return snake[0]; }
    inline int getLast()const{ return last; }    
    inline int getFood()const{ return food; }
    inline void setFood(int x){ food = x; }
    inline bool isFoodEaten()const{ return foodEaten; }
protected:
    int colls, rows, length, *snake, direction, last, food;
    bool foodEaten;
};

#endif // SNAKE_H
