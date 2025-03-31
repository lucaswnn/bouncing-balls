#include "Component.h"
#include "../Actors/Actor.h"

Component::Component(Actor *owner)
    : mOwner(owner),
      mUpdateOrder(std::numeric_limits<int>::max())
{
    // Add to actor's vector of components
    mOwner->addComponent(this);
}

Component::Component(Actor *owner,
                     const int updateOrder)
    : mOwner(owner),
      mUpdateOrder(updateOrder)
{
    // Add to actor's vector of components
    mOwner->addComponent(this);
}

void Component::update(float deltaTime) {}

void Component::processInput(const Uint8 *keyState) {}

Context *Component::getContext() const { return mOwner->getContext(); }


