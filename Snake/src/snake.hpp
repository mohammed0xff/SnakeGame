#pragma once 

#include <vector>
#include "SDL.h"
#include <iostream>
#include <deque>


enum class Direction { Up, Down, Left, Right };

class Snake {
public:

	Snake(int grid_width, int grid_height);
	~Snake();

	void Grow();
	void Update();
	bool isSnakeCell(int x, int y);
	Direction getDirection();
	void setDirection(Direction);
	int GetScore() const;
	void SetScore(int score);
	bool isAlive() const;


	float headX_pos() const;
	float headY_pos() const;
	std::deque<SDL_Point>& body();
private:

	void UpdateHead();
	void UpdateBody(SDL_Point& new_head, SDL_Point& current_head);

private:

	float head_x;
	float head_y;
	float speed;
	int m_score;
	int size;

	Direction m_direction;
	std::deque<SDL_Point> m_body;

	bool isGrowing;
	bool alive;

	int gridWidth;
	int gridHeight;
};