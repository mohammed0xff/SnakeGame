#pragma once 

#include <memory>
#include <iostream>
#include "SDL.h"
#include "snake.hpp"

class Controller {
public:
	void HandleInput(bool& running, std::unique_ptr<Snake> &snake);
	void WaitForAction(bool& running);
};

