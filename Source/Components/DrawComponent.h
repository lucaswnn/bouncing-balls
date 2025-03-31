#pragma once

#include "Component.h"
#include <SDL.h>

class DrawComponent : public Component
{
public:
    // Constructors
    // (Lower draw order corresponds with further back)
    // draw order = further front
    explicit DrawComponent(Actor *owner);

    // Custom draw order
    DrawComponent(class Actor *owner,
                  int drawOrder);

    // Destructor
    ~DrawComponent() override;

    // How the drawing must be sent to the renderer buffer (must override)
    virtual void draw(SDL_Renderer *renderer) const = 0;

    // Draw order getter
    int getDrawOrder() const { return mDrawOrder; }

protected:
    // Draw order
    int mDrawOrder;
};
