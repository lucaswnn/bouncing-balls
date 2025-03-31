#pragma once

#include "DrawComponent.h"

class CircleDrawComponent : public DrawComponent
{
public:
    // Constructors
    // Set the draw priority to further front at the constructing moment
    CircleDrawComponent(Actor *owner, float radius);

    // Defines draw priority
    CircleDrawComponent(Actor *owner, float radius, int drawOrder);

    // Send circle drawing to renderer buffer
    void draw(SDL_Renderer *renderer) const override;

private:
    // Circle radius
    float mRadius;
};
