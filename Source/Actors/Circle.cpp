#include "Circle.h"

#include "../Context.h"
#include "../Components/CircleDrawComponent.h"
#include "../Definitions/Definitions.h"

Circle::Circle(Context *context,
               const float radius,
               const Vector2 &position,
               const Color &color)
    : Actor(context, position),
      mRadius(radius),
      mBorderColor(color),
      mVelocity(Vector2(0.0f, 0.0f)),
      mDrawComponent(nullptr) { new CircleDrawComponent(this, radius); }

void Circle::onUpdate(const float deltaTime)
{
    const auto windowSize = getContext()->getWindowSize();
    auto windowHeight = static_cast<float>(windowSize[1]);

    const auto deltaVelocity = Vector2(0.0f,
                                       TimeParams::GRAVITY_ACCELERATION *
                                       deltaTime);

    const auto deltaPosition = mVelocity * deltaTime +
                               Vector2(0.0f,
                                       TimeParams::GRAVITY_ACCELERATION
                                       * deltaTime * deltaTime);
    mVelocity += deltaVelocity;
    mPosition += deltaPosition;


    if (mPosition.y + mRadius > windowHeight)
    {
        mVelocity.y *= -1.0f;
        mPosition.y -= 1.0f;
    }
}

void Circle::onProcessInput(const Uint8 *keyState) {}
