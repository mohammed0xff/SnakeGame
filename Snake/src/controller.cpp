#include "controller.hpp"




void Controller::HandleInput(bool& running, std::unique_ptr<Snake> &snake) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_w:
                if (snake->getDirection() != Direction::Down) {
                    snake->setDirection(Direction::Up);
                }
                break;

            case SDLK_s:
                if (snake->getDirection() != Direction::Up) {
                    snake->setDirection(Direction::Down);
                }
                break;

            case SDLK_a:
                if (snake->getDirection() != Direction::Right) {
                    snake->setDirection(Direction::Left);
                }
                break;

            case SDLK_d:
                if (snake->getDirection() != Direction::Left) {
                    snake->setDirection(Direction::Right);
                }
                break;
            case SDLK_SPACE:
                WaitForAction(running);
                break;

            }
        }
    }
};

void Controller::WaitForAction(bool& running) {

    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                return;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_SPACE:
                    return;
                }
            }
            SDL_Delay(20);
        }
    }
}
