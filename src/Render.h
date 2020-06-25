#include <vector>
#include <SDL.h>
#include "Items.h"
#include "Snake.h"

#pragma once


class cRender {
public:
    cRender(const std::size_t screen_width, const std::size_t screen_height,
        const std::size_t grid_width, const std::size_t grid_height);
    ~cRender();

    void RenderGame(std::shared_ptr<cSnake> snake, std::shared_ptr<cItems> items);
    void UpdateWindowTitle(int score, int fps);

private:
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};
