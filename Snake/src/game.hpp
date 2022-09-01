#pragma once 

#include <random>
#include <memory>
#include "SDL.h"
#include "universals.hpp"
#include "controller.hpp"
#include "displayManager.hpp"
#include "snake.hpp"


class Game {
 public:
    Game();
    ~Game();

    bool init();
    void run();
    int getScore() const;

 private:
     void reset();
     void update();

private:
    std::unique_ptr<Snake> snake;
    std::unique_ptr<Food> food;

    DisplayManager displayManager;
    Controller controller;

    int gridWidth;
    int gridHeight;

    bool pause;
    bool running;

};

