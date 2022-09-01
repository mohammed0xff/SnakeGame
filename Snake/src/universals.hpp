#pragma once 

#include <iostream>
#include <string>


// DISPLAY VARIABLES
constexpr std::size_t SCREEN_WIDTH{ 640 };
constexpr std::size_t SCREEN_HEIGHT{ 640 };
constexpr std::size_t FPS{ 60 };
constexpr std::size_t MsPerFrame{ 1000 / FPS };

// GAME VARIABLES
constexpr std::size_t GRID_WIDTH{ 32 };
constexpr std::size_t GRID_HEIGHT{ 32 };
constexpr float SNAKE_SPEED = 0.1;

// TEXTURES
const std::string ALIVEHEAD = "assets/head.png";
const std::string DEADHEAD = "assets/deadHead.png";
const std::string BODY = "assets/body.png";
const std::string FOOD = "assets/food.png";	
