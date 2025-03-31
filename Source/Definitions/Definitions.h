#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "../Misc/Color.h"

namespace Colors
{
    inline Color background(0, 0, 0, 0xFF);
    const Color white(0xFF, 0xFF, 0xFF, 0xFF);
    const Color black(0, 0, 0, 0xFF);
    const Color red(0xFF, 0, 0, 0xFF);
    const Color green(0, 0xFF, 0, 0xFF);
    const Color blue(0, 0, 0xFF, 0xFF);
}

namespace WindowParams
{
    inline int width = 800;
    inline int height = 600;
    inline const char *windowName = "Teste";
    constexpr int windowFlags = 0;
}

namespace SDLParams
{
    constexpr int SDLInitFlags = SDL_INIT_VIDEO;
    constexpr int rendererFlags =
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
}

namespace TimeParams
{
    constexpr float MAX_FRAME_RATE_MS = 1000.0f / 60.0f;
    constexpr int MAX_FRAME_RATE_INT_MS = 16;
    constexpr float MAX_DELTA_TIME = 0.05f;
    constexpr float GRAVITY_ACCELERATION = 1000.0f;
}

#endif //DEFINITIONS_H
