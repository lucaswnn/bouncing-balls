#include "CircleDrawComponent.h"

#include "../Actors/Circle.h"
#include "../Context.h"

CircleDrawComponent::CircleDrawComponent(Actor *owner,
                                         const float radius)
    : DrawComponent(owner),
      mRadius(radius) {}

CircleDrawComponent::CircleDrawComponent(Actor *owner,
                                         const float radius,
                                         const int drawOrder)
    : DrawComponent(owner, drawOrder),
      mRadius(radius) {}

void CircleDrawComponent::draw(SDL_Renderer *renderer) const
{
    const auto currentColor = getContext()->getCurrentColor();
    const auto coords = mOwner->getPosition();
    int coords_x = static_cast<int>(coords.x);
    int coords_y = static_cast<int>(coords.y);
    const auto color = dynamic_cast<Circle *>(mOwner)->getColor();

    SDL_SetRenderDrawColor(renderer,
                           color.r,
                           color.g,
                           color.b,
                           color.a);

    const int diameter = static_cast<int>(mRadius) * 2;

    int x = static_cast<int>(mRadius) - 1;
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, coords_x + x, coords_y - y);
        SDL_RenderDrawPoint(renderer, coords_x + x, coords_y + y);
        SDL_RenderDrawPoint(renderer, coords_x - x, coords_y - y);
        SDL_RenderDrawPoint(renderer, coords_x - x, coords_y + y);
        SDL_RenderDrawPoint(renderer, coords_x + y, coords_y - x);
        SDL_RenderDrawPoint(renderer, coords_x + y, coords_y + x);
        SDL_RenderDrawPoint(renderer, coords_x - y, coords_y - x);
        SDL_RenderDrawPoint(renderer, coords_x - y, coords_y + x);

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
