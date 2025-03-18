#include <iostream>
#include <SDL.h>
#include <vector>
#include "Circle.h"
#include "Context.h"
#include "Definitions.h"

void updateCircles(Context &context, std::vector<Circle> &circles)
{
    if (const Uint32 current = SDL_GetTicks();
        current - context.lastUpdateTime >= 100)
    {
        context.lastUpdateTime = current;
        context.clearWindow();
        for (auto &circle: circles)
        {
            circle.addCoords(1, 1);
            circle.draw(context);
        }
    }
}

int main(int argc, char **argv)
{
    Context context;

    std::vector<Circle> circles;

    // Main loop
    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                {
                    running = false;
                    break;
                };
                case SDL_MOUSEBUTTONDOWN:
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);
                        Circle circle(25, mouseX, mouseY, Colors::blue);
                        circles.push_back(circle);
                        break;
                    }
                };
                default: break;
            }
        }

        updateCircles(context, circles);
        SDL_RenderPresent(context.renderer);
    }

    return 0;
}

