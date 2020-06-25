#include "Snake.h"
#include <algorithm>
#include <iostream>

cSnake::cSnake(const std::size_t grid_width, const std::size_t grid_height,
			   unsigned int x, unsigned int y) :
	_gridWidth(grid_width), _gridHeight(grid_height),
	_head({ (double)x, (double)y }) {
	
}

const std::vector<SDL_Point> cSnake::getSnakeBody() { return _body; }
const fPoint cSnake::getSnakeHead() { return _head; };

bool cSnake::isSnakeCell(const unsigned int x, const unsigned int y) {
	if (x == (int)_head.x && y == (int)_head.y)
		return true;

	for (auto const& item : _body) {
		if (x == item.x && y == item.y) {
			return true;
		}
	}

	return false;
}

void cSnake::setGrowing(bool isGrowing) {
	_isGrowing = isGrowing;
	if (isGrowing == true) {

	}
}

void cSnake::updateHead(Direction direction) {
	switch (direction)
	{
	case Direction::kUp:
		_head.y -= 1 * _speed;
		break;
	case Direction::kDown:
		_head.y += 1 * _speed;
		break;
	case Direction::kLeft:
		_head.x -= 1 * _speed;
		break;
	case Direction::kRight:
		_head.x += 1 * _speed;
		break;
	default:
		break;
	}

	_head.x = fmod(_head.x + _gridWidth, _gridWidth);
	_head.y = fmod(_head.y + _gridHeight, _gridHeight);
}

void cSnake::updateBody(SDL_Point prevHeadCell) {

	_body.push_back(prevHeadCell);
	
	if (!_isGrowing) {
		// Remove the tail from the vector.
		_body.erase(_body.begin());
	} else {
		_speed += 0.01;
		this->_isGrowing = false;
	}
}


void cSnake::update(Direction direction) {

	SDL_Point prev_cell{
		static_cast<int>(_head.x),
		static_cast<int>(_head.y)
	};

	updateHead(direction);

	SDL_Point current_cell{
		static_cast<int>(_head.x),
		static_cast<int>(_head.y)
	};


	if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
		updateBody(prev_cell);
	}
}