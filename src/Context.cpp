#include "Context.h"
#include <stdexcept>

#include "Definitions.h"

Context::Context() : windowWidth(WindowParams::width),
                     windowHeight(WindowParams::height),
                     currentColor(Colors::background),
                     backgroundColor(Colors::background),
                     lastUpdateTime(0)
{
    if (const int SDLInit = SDL_Init(SDL_INIT_VIDEO); SDLInit != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        throw std::runtime_error("Failed to initialize SDL");
    }

    window = SDL_CreateWindow(WindowParams::windowName,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              windowWidth,
                              windowHeight,
                              WindowParams::windowFlags);
    if (window == nullptr)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        throw std::runtime_error("Failed to create window");
    }

    renderer = SDL_CreateRenderer(
        window, -1, RendererParams::rendererFlags);
    if (renderer == nullptr)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        throw std::runtime_error("Failed to create renderer");
    }

    clearWindow();
}

Context::~Context()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Context::setCurrentColor(const Color &color)
{
    currentColor = color;
    SDL_SetRenderDrawColor(renderer,
                           currentColor.r,
                           currentColor.g,
                           currentColor.b,
                           currentColor.a);
}

void Context::clearWindow() const
{
    SDL_SetRenderDrawColor(renderer,
                           backgroundColor.r,
                           backgroundColor.g,
                           backgroundColor.b,
                           backgroundColor.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,
                           currentColor.r,
                           currentColor.g,
                           currentColor.b,
                           currentColor.a);
}
