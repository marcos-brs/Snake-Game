#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]) {
    constexpr std::size_t kFramesPerSecond{ 60 };
    constexpr std::size_t kMsPerFrame{ 1000 / kFramesPerSecond };
    constexpr std::size_t kScreenWidth{ 640 };
    constexpr std::size_t kScreenHeight{ 640 };
    constexpr std::size_t kGridWidth{ 32 };
    constexpr std::size_t kGridHeight{ 32 };

    cGame game(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);

    game.Run(kMsPerFrame);

    return 0;
}