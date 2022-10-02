#include "displayManager.hpp"
#include "universals.hpp"
#include <iostream>
#include <string>
#include <math.h>

DisplayManager::DisplayManager()
{
}


DisplayManager::~DisplayManager() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
    IMG_Quit();
}


bool DisplayManager::init() {

    // Initializing SDL 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not be initialized.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not be initialized.\n";
        std::cerr << "SDL_image Error : % s\n", IMG_GetError(), "\n";;
        return false;
    }

    // Creating Window
    m_window = SDL_CreateWindow("Snake",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (m_window == nullptr) {
        std::cerr << "Error creating window..\n";
        std::cerr << SDL_GetError() << "\n";
        return false;

    }

    // Creating renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr) {
        std::cerr << "Error creating renderer..\n";
        std::cerr << SDL_GetError() << "\n";
        return false;

    }

    return true;
}


bool DisplayManager::loadTextures() {

    bool allIsWell = true;

    headTexture = loadTexture(ALIVEHEAD);
    allIsWell &= headTexture != nullptr;
    deadHeadTexture = loadTexture(DEADHEAD);
    allIsWell &= headTexture != nullptr;
    bodyTexture = loadTexture(BODY);
    allIsWell &= headTexture != nullptr;
    foodTexture = loadTexture(FOOD);
    allIsWell &= headTexture != nullptr;

    return allIsWell;
}


void DisplayManager::render(std::unique_ptr<Snake>& snake, std::unique_ptr<Food>& food) {

    SDL_Rect block;
    block.h = SCREEN_HEIGHT / GRID_HEIGHT;
    block.w = SCREEN_WIDTH / GRID_WIDTH;

    int pos_x;
    int pos_y;
    int diameter = (SCREEN_WIDTH / GRID_WIDTH + SCREEN_HEIGHT / GRID_HEIGHT) / 2;

    // Clear screen
    SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255);
    SDL_RenderClear(m_renderer);

    // Render food
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 255);
    block.x = food->getPosition().x * block.w;
    block.y = food->getPosition().y * block.h;
    SDL_RenderCopy(m_renderer, foodTexture, NULL, &block);


    // Render snake's body
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0xCC, 0x7F, 255);
    for (SDL_Point const& point : snake->body()) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderCopy(m_renderer, bodyTexture, NULL, &block);
    }

    // Render snake's head
    block.x = static_cast<int>(snake->headX_pos()) * block.w;
    block.y = static_cast<int>(snake->headY_pos()) * block.h;

    snake->isAlive() ?
        SDL_RenderCopy(m_renderer, headTexture, NULL, &block)
        //SDL_SetRenderDrawColor(m_renderer, 0x00, 0x55, 0x7F, 0xFF)
        :
        SDL_RenderCopy(m_renderer, deadHeadTexture, NULL, &block);

    // Display
    SDL_RenderPresent(m_renderer);
}


void DisplayManager::updateStats(int score, int fps) {
    std::string title = "Snake | Score: " + std::to_string(score) + " | " + std::to_string(fps) + " FPS";
    SDL_SetWindowTitle(m_window, title.c_str());
}


SDL_Texture* DisplayManager::loadTexture(std::string path)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

