#ifndef CONTEXT_H
#define CONTEXT_H

#include "Color.h"
#include <SDL.h>

class Context
{
public:
    int windowWidth, windowHeight;
    Color currentColor;
    Color backgroundColor;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint32 lastUpdateTime;

    Context();

    ~Context();

    void setCurrentColor(const Color &color);

    void clearWindow() const;
};

#endif //CONTEXT_H
