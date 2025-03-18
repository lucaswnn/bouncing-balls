#include "Circle.h"

Circle::Circle(const int radius,
               const int x,
               const int y,
               const Color color) : r(radius),
                                    coords(x, y),
                                    color(color) {}

void Circle::setCoords(const int x, const int y)
{
    coords.x = x;
    coords.y = y;
}

void Circle::addCoords(const int x, const int y)
{
    coords.x += x;
    coords.y += y;
}

void Circle::setRadius(const int radius) { r = radius; }

void Circle::addRadius(const int radius) { r += radius; }

void Circle::draw(const Context &context)
{
    SDL_Renderer *renderer = context.renderer;
    const Color currentColor = context.currentColor;

    SDL_SetRenderDrawColor(renderer,
                           color.r,
                           color.g,
                           color.b,
                           color.a);

    const int diameter = (r * 2);

    int x = (r - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, coords.x + x, coords.y - y);
        SDL_RenderDrawPoint(renderer, coords.x + x, coords.y + y);
        SDL_RenderDrawPoint(renderer, coords.x - x, coords.y - y);
        SDL_RenderDrawPoint(renderer, coords.x - x, coords.y + y);
        SDL_RenderDrawPoint(renderer, coords.x + y, coords.y - x);
        SDL_RenderDrawPoint(renderer, coords.x + y, coords.y + x);
        SDL_RenderDrawPoint(renderer, coords.x - y, coords.y - x);
        SDL_RenderDrawPoint(renderer, coords.x - y, coords.y + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
    SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g,
                           currentColor.b, currentColor.a);
}
