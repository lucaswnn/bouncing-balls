#pragma once

#include "Actor.h"
#include "../Misc/Color.h"

class Circle : public Actor
{
public:
    // Constructor
    Circle(Context *context,
           float radius,
           const Vector2 &position,
           const Color &color);

    // Set circle radius
    void setRadius(const float radius) { mRadius = radius; }

    // Increment circle radius
    void addRadius(const float radius) { mRadius += radius; }

    // Get circle border color
    const Color &getColor() const { return mBorderColor; };

private:
    // Defines what happens on context update calls
    void onUpdate(float deltaTime) override;

    // Defines what happens on context process input calls
    void onProcessInput(const Uint8 *keyState) override;

    // Circle properties
    float mRadius;
    Color mBorderColor;
    Vector2 mVelocity;

    // Circle specific draw component
    class CircleDrawComponent *mDrawComponent;
};
