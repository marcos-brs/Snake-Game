#include <SDL.h>
#include <vector>
#include <memory>
#include <random>

#include "Snake.h"

#pragma once

class cItems {
public:
	cItems(const std::size_t grid_width, const std::size_t grid_height);

	SDL_Point getFoodPosition();
	std::vector<SDL_Point> getOldObstaclesPosition();
	std::vector<SDL_Point> getObstaclesPosition();

	void placeFood(const std::shared_ptr<cSnake> snake, std::mt19937 engine,
		std::uniform_int_distribution<int> random_w, std::uniform_int_distribution<int> random_h);

	void placeObstacle(const std::shared_ptr<cSnake> snake, std::mt19937 engine,
		std::uniform_int_distribution<int> random_w, std::uniform_int_distribution<int> random_h);
private:
	bool isFreeSpace(const std::shared_ptr<cSnake> snake, const unsigned int x, const unsigned int y);

	SDL_Point _food;
	unsigned int _numberOfObstacles;
	std::size_t _gridWidth, _gridHeight;
	std::vector<SDL_Point> _obstacles;
	std::vector<SDL_Point> _oldObstacles;
};