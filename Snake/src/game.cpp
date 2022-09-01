#include <iostream>
#include <future>
#include "SDL.h"
#include "game.hpp"


Game::Game() 
    : gridWidth(GRID_WIDTH)
    , gridHeight(GRID_HEIGHT)
    , running(true)
    , pause(false)
{
}

Game::~Game() {

}

bool Game::init() {

    if (displayManager.init() == false) return 0;
    if (displayManager.loadTextures() == false) return 0;

    snake = std::make_unique<Snake>(gridWidth, gridHeight);
    food = std::make_unique<Food>(gridWidth, gridHeight, snake);
}


void Game::run() {

    Uint32 timestamp = SDL_GetTicks();
    Uint32 frameStart;
    Uint32 frameEnd;
    Uint32 elapsedTime;

    int frame_count = 0;

    while (running) {
        // Time start
        frameStart = SDL_GetTicks();

        // Do work
        controller.HandleInput(running, snake);
        update();
        displayManager.render(snake, food);
        
        // Time end
        frameEnd = SDL_GetTicks();
        
        // Calculate duration 
        elapsedTime = frameEnd - frameStart;
        frame_count++;

        // Update the window title when completing one second
        if (frameEnd - timestamp >= 1000) {
            displayManager.updateStats(snake->GetScore(), frame_count);
            frame_count = 0;
            timestamp = frameEnd;
        }

        // If the time for this frame is too small 
        // apply some delay to correct the frame rate.
        if (elapsedTime < MsPerFrame) {
            SDL_Delay(MsPerFrame - elapsedTime);
        }
    }
}


void Game::update() {
    if (!snake->isAlive()) reset();
    food->serve();
    snake->Update();
}


void Game::reset() {
    controller.WaitForAction(running);
    snake = std::make_unique<Snake>(gridWidth, gridHeight);
    food = std::make_unique<Food>(gridWidth, gridHeight, snake);
}


int Game::getScore() const {
    return snake->GetScore();
}

