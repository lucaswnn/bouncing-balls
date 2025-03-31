#pragma once

#include <SDL_stdinc.h>

class Component
{
public:
    // Constructor
    // (the lower the update order, the earlier the component updates)
    // Update order set to the lowest
    explicit Component(class Actor *owner);

    // Custom update order
    explicit Component(class Actor *owner, int updateOrder);

    // Destructor
    virtual ~Component() = default;

    // Update this component by delta time (if needed)
    virtual void update(float deltaTime);

    // Process input for this component (if needed)
    virtual void processInput(const Uint8 *keyState);

    // Update order getter
    int getUpdateOrder() const { return mUpdateOrder; }

    // Owner getter
    Actor *getOwner() const { return mOwner; }

    class Context *getContext() const;

protected:
    // Owning actor
    Actor *mOwner;

    // Update order
    int mUpdateOrder;
};
