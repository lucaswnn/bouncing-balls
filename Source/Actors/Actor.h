#pragma once

#include <SDL_stdinc.h>
#include <vector>
#include "../Tools/Math.h"

// Describes the Actor current state
enum class ActorState
{
    Active,
    Paused,
    Destroy
};

class Actor
{
public:
    // Constructor
    // Receives the context
    explicit Actor(class Context *context);

    // Receives the context and position
    Actor(Context *context, const Vector2 &position);

    // Destructor
    virtual ~Actor();

    // Update function called from Context (not overridable)
    void update(float deltaTime);

    // ProcessInput function called from Context (not overridable)
    void processInput(const Uint8 *keyState);

    // Position getter/setter
    const Vector2 &getPosition() const { return mPosition; }
    void setPosition(const Vector2 &pos) { mPosition = pos; }

    // Scale getter/setter
    float getScale() const { return mScale; }
    void setScale(const float scale) { mScale = scale; }

    // Rotation getter/setter
    float getRotation() const { return mRotation; }
    void setRotation(const float rotation) { mRotation = rotation; }

    // State getter/setter
    ActorState getState() const { return mState; }
    void setState(const ActorState state) { mState = state; }

    // Context getter
    Context *getContext() const { return mContext; }

    // Returns component of type T, or null if it doesn't exist
    template<typename T>
    T *getComponent() const
    {
        for (auto c: mComponents)
        {
            T *t = dynamic_cast<T *>(c);
            if (t != nullptr) { return t; }
        }

        return nullptr;
    }

protected:
    Context *mContext;

    // Any actor-specific update code (overridable)
    virtual void onUpdate(float deltaTime);

    // Any actor-specific update code (overridable)
    virtual void onProcessInput(const Uint8 *keyState);

    // Actor's state
    ActorState mState;

    // Transform
    Vector2 mPosition;
    float mScale;
    float mRotation;

    // Components
    std::vector<class Component *> mComponents;

private:
    friend class Component;

    // Adds component to Actor (this is automatically called
    // in the component constructor)
    void addComponent(Component *c);
};
