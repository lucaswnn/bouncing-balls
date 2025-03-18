#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "Color.h"

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

namespace RendererParams
{
    constexpr int rendererFlags =
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
}

#endif //DEFINITIONS_H
