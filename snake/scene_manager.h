#pragma once
#include "scene.h"

class SceneManager
{
public:
    void changeScene(Scene *newScene);
    void handleInput(SDL_Event &event);
    void update(float deltaTime);
    void render(SDL_Renderer *renderer);
    void applyPendingScene();
    ~SceneManager();

private:
    Scene *currentScene = nullptr;
    Scene *pendingScene = nullptr;
};
