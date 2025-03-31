#pragma once

#include <array>
#include <SDL.h>
#include <vector>
#include "Misc/Color.h"

class Context
{
public:
    // Constructor
    // Create instance based on Definitions.h
    Context();

    // Initialize the SDL window, renderer and set the background color
    bool initialize();

    // Run context main loop
    void runLoop();

    // Disable SDL resources
    void shutdown() const;

    // Stop context main loop
    void quit() { mIsRunning = false; }

    // Actor methods
    // Create actor instances
    void initializeActors();

    // Update actor instances
    void updateActors(float deltaTime);

    // Add actor instance
    void addActor(class Actor *actor);

    // Remove actor instance
    void removeActor(const class Actor *actor);

    // Drawable component methods
    // Add drawable component instance
    void addDrawable(class DrawComponent *drawable);

    // Remove drawable component instance
    void removeDrawable(const class DrawComponent *drawable);

    // Return the window size (Width x Height)
    std::array<int, 2> getWindowSize() const { return mWindowSize; };

    // SDL current color getter/setter
    Color getCurrentColor() const { return mCurrentColor; };

    // Set the current SDL color buffer
    void setCurrentColor(const Color &color);

    // Clear the renderer buffer with the background color
    void clearWindow() const;

private:
    // Main loop methods
    // Process mouse and key inputs
    void processInput();

    // Update game based on current state and input
    void updateContext();

    // Render the objects
    void generateOutput() const;

    // Adds circle by clicking with the left mouse button
    // Creates a circle centered on the click coordinates
    void addCircle();

    // All the actors
    std::vector<class Actor *> mActors;
    std::vector<class Actor *> mPendingActors;

    // All the drawable components
    std::vector<class DrawComponent *> mDrawables;

    // Window properties
    std::array<int, 2> mWindowSize; // Width x Height

    // SDL resources
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    // Color properties
    Color mCurrentColor;
    Color mBackgroundColor;

    // Track elapsed time since game start
    Uint32 mTicksCount;

    // Track if actors are being updated
    bool mIsRunning;
    bool mUpdatingActors;
};
