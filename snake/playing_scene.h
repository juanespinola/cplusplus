#pragma once
#include <iostream>
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
    void drawGrid(SDL_Renderer* renderer);
    void drawSnake(SDL_Renderer* renderer, std::vector<Position>& snake);
    void drawFood(SDL_Renderer* renderer, Position food);
    void keyboardInput(SDL_Keycode key);

private:
    SceneManager *sceneManager;
    
    // variables del juego
    std::vector<Position> snake;
    Position food;
    Delta direction;
    bool eat;
    float elapsedTime;
    float intervalMovement;

    static const int cellSize = 10;

    SDL_Rect grid;

};
