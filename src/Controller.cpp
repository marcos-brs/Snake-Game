#include "Controller.h"
#include <iostream>

void cController::handleInput(bool &running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                changeDirection(Direction::kUp,
                                Direction::kDown);
                break;

            case SDLK_DOWN:
                changeDirection(Direction::kDown,
                                Direction::kUp);
                break;

            case SDLK_LEFT:
                changeDirection(Direction::kLeft,
                                Direction::kRight);
                break;

            case SDLK_RIGHT:
                changeDirection(Direction::kRight,
                                Direction::kLeft);
                break;
            }
        }
    }
}

Direction cController::getDirection() {
    return _direction;
}


void cController::changeDirection(Direction newDirection, Direction opposite) {
    if (_direction != opposite)
        _direction = newDirection;
}