#include <algorithm>
#include "Context.h"
#include "Actors/Circle.h"
#include "Definitions/Definitions.h"
#include "Components/DrawComponent.h"

Context::Context()
    : mWindowSize({
          WindowParams::width,
          WindowParams::height
          }),
      mWindow(nullptr),
      mRenderer(nullptr),
      mCurrentColor(Colors::background),
      mBackgroundColor(Colors::background),
      mTicksCount(0),
      mIsRunning(true),
      mUpdatingActors(false) {}

bool Context::initialize()
{
    if (const int SDLInit = SDL_Init(SDLParams::SDLInitFlags); SDLInit != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(WindowParams::windowName,
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               mWindowSize[0],
                               mWindowSize[1],
                               WindowParams::windowFlags);
    if (mWindow == nullptr)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow,
                                   -1,
                                   SDLParams::rendererFlags);
    if (mRenderer == nullptr)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    clearWindow();
    mTicksCount = SDL_GetTicks();
    initializeActors();

    return true;
}

void Context::runLoop()
{
    while (mIsRunning)
    {
        processInput();
        updateContext();
        generateOutput();
    }
}


void Context::shutdown() const
{
    while (!mActors.empty()) { delete mActors.back(); }

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

// Implemented as necessary
void Context::initializeActors() {}

void Context::updateActors(const float deltaTime)
{
    mUpdatingActors = true;
    for (const auto actors: mActors) { actors->update(deltaTime); }
    mUpdatingActors = false;

    for (auto pendingActor: mPendingActors) { mActors.push_back(pendingActor); }
    mPendingActors.clear();

    std::vector<Actor *> deadActors;
    for (auto actor: mActors)
    {
        if (actor->getState() == ActorState::Destroy)
        {
            deadActors.push_back(actor);
        }
    }

    for (const auto deadActor: deadActors) { delete deadActor; }
}

void Context::addActor(Actor *actor)
{
    if (mUpdatingActors == true) { mPendingActors.push_back(actor); }
    else { mActors.push_back(actor); }
}

void Context::removeActor(const Actor *actor)
{
    auto removable = std::find(mPendingActors.begin(),
                               mPendingActors.end(),
                               actor);
    if (removable != mPendingActors.end() &&
        !mPendingActors.empty() &&
        removable != mPendingActors.end() - 1)
    {
        std::iter_swap(removable, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    removable = std::find(mActors.begin(),
                          mActors.end(),
                          actor);
    if (removable != mActors.end() &&
        !mActors.empty() &&
        removable != mActors.end() - 1)
    {
        std::iter_swap(removable, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Context::addDrawable(DrawComponent *drawable)
{
    mDrawables.push_back(drawable);

    std::sort(mDrawables.begin(),
              mDrawables.end(),
              [](const DrawComponent *a, const DrawComponent *b)
              {
                  return a->getDrawOrder() < b->getDrawOrder();
              });
}

void Context::removeDrawable(const DrawComponent *drawable)
{
    const auto removable = std::find(mDrawables.begin(),
                                     mDrawables.end(),
                                     drawable);
    mDrawables.erase(removable);
}

void Context::setCurrentColor(const Color &color)
{
    mCurrentColor = color;
    SDL_SetRenderDrawColor(mRenderer,
                           mCurrentColor.r,
                           mCurrentColor.g,
                           mCurrentColor.b,
                           mCurrentColor.a);
}

void Context::clearWindow() const
{
    SDL_SetRenderDrawColor(mRenderer,
                           mBackgroundColor.r,
                           mBackgroundColor.g,
                           mBackgroundColor.b,
                           mBackgroundColor.a);
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer,
                           mCurrentColor.r,
                           mCurrentColor.g,
                           mCurrentColor.b,
                           mCurrentColor.a);
}

void Context::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                quit();
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    addCircle();
                    break;
                }
            };
            default: break;
        }
    }
}

void Context::updateContext()
{
    // Waits 16 ms to update the context
    while (!SDL_TICKS_PASSED(
        SDL_GetTicks(),
        mTicksCount + TimeParams::MAX_FRAME_RATE_INT_MS)) {};

    float deltaTime = static_cast<float>(SDL_GetTicks() - mTicksCount) /
                      1000.0f;

    if (deltaTime > TimeParams::MAX_DELTA_TIME)
    {
        deltaTime = TimeParams::MAX_DELTA_TIME;
    }

    mTicksCount = SDL_GetTicks();

    updateActors(deltaTime);
}

void Context::generateOutput() const
{
    clearWindow();
    for (const auto drawable: mDrawables) { drawable->draw(mRenderer); }
    SDL_RenderPresent(mRenderer);
}

void Context::addCircle()
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    const auto pos_x = static_cast<float>(mouseX);
    const auto pos_y = static_cast<float>(mouseY);
    new Circle(this,
               15.0f,
               Vector2(pos_x, pos_y),
               Colors::blue);
}
