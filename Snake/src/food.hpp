#pragma once 

#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include "SDL.h"
#include "snake.hpp"


class Food {

public:
    Food(int grid_width, int grid_height, std::unique_ptr<Snake> &snake);
    ~Food();

    void serve();
    bool isEaten();
    void generateNew();    
    void rewardSnake();
    SDL_Point getPosition() const;

private:
    SDL_Point m_position;
    std::unique_ptr<Snake> &m_snake;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> random_x;
    std::uniform_int_distribution<int> random_y;

};

