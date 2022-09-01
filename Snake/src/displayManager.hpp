#pragma once 

#include <vector>
#include <memory>
#include "SDL.h"
#include "SDL_image.h"
#include "snake.hpp"
#include "food.hpp"

class DisplayManager {

public:
	DisplayManager();
	~DisplayManager();

	bool init();
	bool loadTextures();
	void updateStats(int score, int fps);
	void render(std::unique_ptr<Snake>& snake, std::unique_ptr<Food>& food);

private:
	SDL_Texture* loadTexture(std::string path);

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	SDL_Texture* headTexture;
	SDL_Texture* deadHeadTexture;
	SDL_Texture* bodyTexture;
	SDL_Texture* foodTexture;

};
