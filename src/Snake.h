#include <SDL.h>
#include <vector>
#include "Controller.h"

#pragma once
struct fPoint {
	double x;
	double y;
};

class cSnake {
public:
	cSnake(const std::size_t grid_width, const std::size_t grid_height,
		   unsigned int x, unsigned int y);

	void update(Direction direction);

	void setGrowing(bool isGrowing);

	const fPoint getSnakeHead();
	const std::vector<SDL_Point> getSnakeBody();

	bool isSnakeCell(const unsigned int x, const unsigned int y);
	bool _isGrowing{ false };
	bool _isAlive{ true };
private:
	void updateBody(SDL_Point prevHeadCell);
	void updateHead(Direction direction);

	std::size_t _gridWidth, _gridHeight;
	double _speed = { 0.1 };
	fPoint _head;
	
	std::vector<SDL_Point> _body;
};
