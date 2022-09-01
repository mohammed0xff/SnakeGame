#include <cmath>
#include <iostream>
#include "snake.hpp"
#include "universals.hpp"


Snake::Snake(int grid_width, int grid_height)
   : gridWidth(grid_width)
   , gridHeight(grid_height)
   , head_x(grid_width / 2)
   , head_y(grid_height / 2)
   , m_direction(Direction::Right)
   , speed(SNAKE_SPEED)
   , isGrowing(false)
   , alive(true)
   , m_score(0)
   , size(5)
{
    m_body.push_back(SDL_Point{ static_cast<int>(head_x - speed), static_cast<int>(head_y) });
}


Snake::~Snake() {

}


void Snake::Grow() {
    m_score++;
    isGrowing = true;
}


void Snake::Update() {

    SDL_Point newHead;

    UpdateHead();

    newHead.x = head_x;
    newHead.y = head_y;
    
    UpdateBody(newHead, m_body.front());

}


void Snake::UpdateHead() {

    switch (m_direction) {

    case Direction::Left:
        head_x -= speed;
        break;

    case Direction::Right:
        head_x += speed;
        break;

    case Direction::Up:
        head_y -= speed;
        break;

    case Direction::Down:
        head_y += speed;
        break;
    }

    // Relocate head to opposite direction if going off of the screen.
    head_x = fmod(head_x + gridWidth,  gridWidth);
    head_y = fmod(head_y + gridHeight, gridHeight);
}


void Snake::UpdateBody(SDL_Point& new_head, SDL_Point& current_head) {

    // snake didn't move.
    if (new_head.x == current_head.x && 
        new_head.y == current_head.y) return;

    if (!isGrowing) {
        // Erase the tail as the snanke moves forward.
        m_body.pop_back();
    }
    else {
        // leave it, letting the snake grow one cell in size.
        isGrowing = false;
        size++;
    }

    // Check for head collision
    for (auto const& block : m_body) {
        if (new_head.x == block.x && new_head.y == block.y) {
            alive = false;
            return;
        }
    }

    m_body.push_front(new_head);
}


bool Snake::isSnakeCell(int x, int y) {

    if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
        return true;
    }
    for (SDL_Point& block : m_body) {
        if (x == block.x && y == block.y) {
            return true;
        }
    }
    return false;
}


float Snake::headX_pos() const { return head_x;}
float Snake::headY_pos() const { return head_y;}

void Snake::setDirection(Direction dir) { m_direction = dir;}
Direction Snake::getDirection() { return m_direction;}

void Snake::SetScore(int score) { m_score = score; }
int Snake::GetScore() const { return m_score; }

bool Snake::isAlive() const { return alive; }
std::deque<SDL_Point>& Snake::body() { return m_body;}

