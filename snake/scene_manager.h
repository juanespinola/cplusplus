#pragma once
#include "scene.h"

class SceneManager
{
public:
    ~SceneManager();

    void changeScene(Scene *newScene);
    void handleInput(SDL_Event &event);
    void update(float deltaTime);
    void render(SDL_Renderer *renderer);
    void applyPendingScene();
    void requestQuit();
    bool isQuitRequested();
private:
    Scene *currentScene = nullptr;
    Scene *pendingScene = nullptr;
    bool requestedQuit = false;
};
