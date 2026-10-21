#pragma once
#include "scene.h"

class SceneManager; // forward declaration
class PlayingScene;

class MenuScene : public Scene
{
public:
    MenuScene(SceneManager *manager);
    ~MenuScene();

    void handleInput(SDL_Event &event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer *renderer) override;

private:
    static const int MENU_OPTIONS = 2;
    int selectedOption;
    SceneManager *sceneManager;
};