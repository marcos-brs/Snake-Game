#include "Game.h"
#include <iostream>

cGame::cGame(const std::size_t screen_width, const std::size_t screen_height,
	const std::size_t grid_width, const std::size_t grid_height) :
	_engine(_dev()),
	random_w(0, static_cast<int>(grid_width - 1)),
	random_h(0, static_cast<int>(grid_height - 1))
	{

	unsigned int x = random_h(_engine);
	unsigned int y = random_h(_engine);

	// init pointers
	_snake = std::make_shared<cSnake>(grid_width, grid_height, x, y);
	_items = std::make_shared<cItems>(grid_width , grid_height);
	_controller = std::make_unique<cController>();

	// start random food
	_items->placeFood(_snake, _engine, random_w, random_h);

	// start random obstacles
	_items->placeObstacle(_snake, _engine, random_w, random_h);
	
	_render = std::make_unique<cRender>(screen_width, screen_height, grid_width, grid_height);
}

void cGame::Run(std::size_t target_frame_duration) {
	Uint32 title_timestamp = SDL_GetTicks();
	Uint32 frame_start;
	Uint32 frame_end;
	Uint32 frame_duration;
	int frame_count = 0;

	while (true) {
		frame_start = SDL_GetTicks();

		this->Update();
		_render->RenderGame(_snake, _items);

		frame_end = SDL_GetTicks();

		frame_count++;
		frame_duration = frame_end - frame_start;

		if (frame_end - title_timestamp >= 1000) {
			_render->UpdateWindowTitle(_score, frame_count);
			frame_count = 0;
			title_timestamp = frame_end;
		}

		if (frame_duration < target_frame_duration) {
			SDL_Delay(target_frame_duration - frame_duration);
		}
	}
}

void cGame::Update() {

	// get input
	_controller->handleInput(_isRunning);

	// stop game
	if (!_isRunning)
		return;
	// snake props
	auto snakeBody = _snake->getSnakeBody();
	auto snakeHead = _snake->getSnakeHead();
	
	// items props
	auto foodPosition = _items->getFoodPosition();
	auto obstaclesPosition = _items->getObstaclesPosition();

	// check if snake colides with one obstacle
	for (auto obstaclePosition : obstaclesPosition) {
		if (obstaclePosition.x == (int)snakeHead.x && obstaclePosition.y == (int)snakeHead.y) {
			_isRunning = false;
			_snake->_isAlive = false;
			return;
		}
	}

	// check if snake colides with herself
	for (auto obstaclePosition : snakeBody) {
		if (obstaclePosition.x == (int)snakeHead.x && obstaclePosition.y == (int)snakeHead.y) {
			_isRunning = false;
			_snake->_isAlive = false;
			return;
		}
	}

	std::cout << foodPosition.x << foodPosition.y << std::endl;

	// check if snake colides with a food
	if ((int)snakeHead.x == foodPosition.x && (int)snakeHead.y == foodPosition.y) {

		// set snake is growing
		_snake->_isGrowing = true;
		// puts a new food
		_items->placeFood(_snake, _engine, random_w, random_h);

		// increase score
		_score++;
	}

	// take directions
	auto direction = _controller->getDirection();

	_snake->update(direction);

	// check if is a time to place new obstacles
}