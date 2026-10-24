#pragma once
#include "scene.h"

class SceneManager; // forward declaration

class GameOverScene : public Scene
{
public:
    GameOverScene(SceneManager *manager);
    ~GameOverScene();

    void handleInput(SDL_Event &event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer *renderer) override;

private:
    SceneManager *sceneManager;
    static const int MENU_OPTIONS = 2;
    int selectedOption;
};