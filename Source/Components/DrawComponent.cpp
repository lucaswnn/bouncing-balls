#include <limits>
#include "DrawComponent.h"
#include "../Actors/Actor.h"
#include "../Context.h"

DrawComponent::DrawComponent(Actor *owner)
    : Component(owner),
      mDrawOrder(std::numeric_limits<int>::max())
{
    mOwner->getContext()->addDrawable(this);
}

DrawComponent::DrawComponent(Actor *owner,
                             const int drawOrder)
    : Component(owner),
      mDrawOrder(drawOrder) { mOwner->getContext()->addDrawable(this); }

DrawComponent::~DrawComponent() { mOwner->getContext()->removeDrawable(this); }
