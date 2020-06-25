#include <SDL.h>

#pragma once
enum class Direction { kUp, kDown, kLeft, kRight };

class cController {
public:
	void handleInput(bool &running);
	Direction getDirection();
private:
	void changeDirection(Direction newDirection, Direction opposite);

	Direction _direction;
};