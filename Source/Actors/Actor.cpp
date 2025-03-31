#include "Actor.h"
#include <algorithm>
#include "../Context.h"
#include "../Components/Component.h"

Actor::Actor(Context *context)
    : mContext(context),
      mState(ActorState::Active),
      mPosition(Vector2::Zero),
      mScale(1.0f),
      mRotation(0.0f) { mContext->addActor(this); }

Actor::Actor(Context *context,
             const Vector2 &position)
    : mContext(context),
      mState(ActorState::Active),
      mPosition(position),
      mScale(1.0f),
      mRotation(0.0f) { mContext->addActor(this); }

Actor::~Actor()
{
    mContext->removeActor(this);

    for (const auto component: mComponents) { delete component; }
    mComponents.clear();
}

void Actor::update(const float deltaTime)
{
    if (mState == ActorState::Active)
    {
        for (const auto component: mComponents)
        {
            component->update(deltaTime);
        }
        onUpdate(deltaTime);
    }
}

void Actor::processInput(const Uint8 *keyState)
{
    if (mState == ActorState::Active)
    {
        for (const auto component: mComponents)
        {
            component->processInput(keyState);
        }
        onProcessInput(keyState);
    }
}

void Actor::onUpdate(const float deltaTime) {}

void Actor::onProcessInput(const Uint8 *keyState) {}

void Actor::addComponent(Component *c)
{
    mComponents.emplace_back(c);
    std::sort(mComponents.begin(),
              mComponents.end(),
              [](const Component *a, const Component *b)
              {
                  return a->getUpdateOrder() < b->getUpdateOrder();
              });
}
