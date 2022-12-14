cmake_minimum_required(VERSION 3.10)

project(snakeGame)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} 
		src/main.cpp
		src/game.cpp 
		src/controller.cpp 
		src/displayManager.cpp
		src/snake.cpp
		src/food.cpp
		)

file(COPY src/assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} 
				${SDL2_IMAGE_LIBRARIES} 
				${SDL2_TTF_LIBRARIES})


add_executable(snake src/main.cpp)
