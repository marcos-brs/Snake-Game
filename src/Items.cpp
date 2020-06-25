#include "Items.h"

cItems::cItems(const std::size_t grid_width, const std::size_t grid_height) : 
    _gridWidth(grid_width), _gridHeight(grid_height) {
}

SDL_Point cItems::getFoodPosition() {
	return _food;
}

std::vector<SDL_Point> cItems::getOldObstaclesPosition() {
	return _oldObstacles;
}

std::vector<SDL_Point> cItems::getObstaclesPosition() {
	return _obstacles;
}

bool cItems::isFreeSpace(const std::shared_ptr<cSnake> snake, const unsigned int x, const unsigned int y) {
    if (snake->isSnakeCell(x, y))
        return false;

    if (x == _food.x && y == _food.y)
        return false;

    for (auto const& item : _obstacles) {
        if (x == item.x && y == item.y) {
            return false;
        }
    }

    for (auto const& item : _oldObstacles) {
        if (x == item.x && y == item.y) {
            return false;
        }
    }

    return true;
}

void cItems::placeFood(const std::shared_ptr<cSnake> snake, std::mt19937 engine,
    std::uniform_int_distribution<int> random_w, std::uniform_int_distribution<int> random_h) {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item before placing
        // food.
        if (isFreeSpace(snake, x, y) ) {
            _food.x = x;
            _food.y = y;
            return;
        }
    }
}

void cItems::placeObstacle(const std::shared_ptr<cSnake> snake, std::mt19937 engine,
    std::uniform_int_distribution<int> random_w, std::uniform_int_distribution<int> random_h) {
    _oldObstacles = _obstacles;
    _obstacles.clear();
    for (int i = 0; i < 5; i++) {
        int x, y;
        while (true) {
            x = random_w(engine);
            y = random_h(engine);
            if (isFreeSpace(snake, x, y)) {
                _obstacles.push_back({ x, y });
                break;
            }
        }
    }
}