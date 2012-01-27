#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
public:
    static const int MOVING_LEFT = 0;
    static const int MOVING_UP = 1;
    static const int MOVING_RIGHT = 2;
    static const int MOVING_DOWN = 3;

    static const int FOOD_LEFT = -1;
    static const int FOOD_AHEAD = 0;
    static const int FOOD_RIGHT = 1;
    static const int FOOD_BEHIND = 2;

    static const int GO_LEFT = -1;
    static const int GO_FORWARD = 0;
    static const int GO_RIGHT = 1;

    Snake(int colls, int rows, int xy0, int d0, int food);
    ~Snake();

    bool move(int order);
    bool move2(int dir);
    void restart(int xy0, int d0);
    int findFood();

    inline int abs(int x)const{ return x<0 ? -x : x; }
    inline int sgn(int x)const{ if(x) if(x<0) return -1; else return 1; else return 0; }
    inline int getDirection()const{ return direction; }
    inline int *getSnake()const{ return snake; }
    inline int getLenght()const{ return length; }
    inline int getFirst()const{ return snake[0]; }
    inline int getLast()const{ return last; }    
    inline int getFood()const{ return food; }
    inline void setFood(int x){ food = x; findFood(); }
    inline bool isFoodEaten()const{ return foodEaten; }
protected:
    int colls, rows, length, *snake, direction, last, food, foodDir;
    bool foodEaten;
};

#endif // SNAKE_H
