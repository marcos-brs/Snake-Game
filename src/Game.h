#include <memory>

#include "Items.h"
#include "Snake.h"
#include "Controller.h"
#include "Render.h"

#pragma once

class cGame {
public:
	cGame(const std::size_t screen_width, const std::size_t screen_height,
		const std::size_t grid_width, const std::size_t grid_height);
	void Run(std::size_t target_frame_duration);
	void Update();
private:
	bool _isRunning{ true };
	int _score{ 0 };

	// random generate
	std::random_device _dev;
	std::mt19937 _engine;
	std::uniform_int_distribution<int> random_w;
	std::uniform_int_distribution<int> random_h;

	std::shared_ptr<cSnake> _snake;
	std::shared_ptr<cItems> _items;
	std::unique_ptr<cController> _controller;
	std::unique_ptr<cRender> _render;
};