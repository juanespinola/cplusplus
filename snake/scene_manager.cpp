#include "scene_manager.h"

void SceneManager::changeScene(Scene *newScene)
{
    pendingScene = newScene;
    currentScene = nullptr;

}

void SceneManager::handleInput(SDL_Event &event)
{
    currentScene->handleInput(event);
}

void SceneManager::update(float deltaTime)
{
    currentScene->update(deltaTime);
}

void SceneManager::render(SDL_Renderer *renderer)
{
    currentScene->render(renderer);
}
