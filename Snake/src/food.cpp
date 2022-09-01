#include "food.hpp"


Food::Food(int gridWidth, int gridHeight, std::unique_ptr<Snake> &snake) 
   : random_x(0, static_cast<int>(gridWidth-1)) 
   , random_y(0, static_cast<int>(gridHeight-1))
   , m_position{-1,-1}
   , m_snake(snake)
{
    generateNew();
}


Food::~Food(){
   
}


SDL_Point Food::getPosition() const {
    return m_position;
}


void Food::rewardSnake() {
    m_snake->Grow();
}


void Food::serve() {
    if (isEaten()) {
        rewardSnake();
        generateNew();
    }
}


bool Food::isEaten(){
    int pos_x = static_cast<int>(m_snake->headX_pos());
    int pos_y = static_cast<int>(m_snake->headY_pos());

    if (m_position.x == pos_x && m_position.y == pos_y) {
        m_position.x = m_position.y = -1; // hide food
        return true;
    }
    return false;
}


void Food::generateNew(){
    int x, y;
    do
    {
        x = random_x(generator);
        y = random_y(generator);

    } while (m_snake->isSnakeCell(x, y));

    m_position.x = x;
    m_position.y = y;
}

