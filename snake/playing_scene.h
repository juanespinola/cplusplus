#pragma once
#include <vector>

#include "scene.h"
#include "types.h"
#include "globals.h"

class SceneManager; // forward declaration — misma razón que en menu_scene.h

class PlayingScene : public Scene
{
public:
    PlayingScene(SceneManager *manager);
    void handleInput(SDL_Event &event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer *renderer) override;

private:
    SceneManager *sceneManager;
    
    // variables del juego
    std::vector<Position> snake
};
