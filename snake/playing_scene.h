#pragma once
#include <iostream>
#include <vector>

#include "scene.h"
#include "types.h"
#include "globals.h"
#include "collision.h"

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
    void drawPanel(SDL_Renderer* renderer);
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

    static const int CELL_SIZE = 10;     // píxeles por celda (constante, existe desde siempre)

    SDL_Rect grid;                       // PÍXELES: solo para dibujar el marco
    static const int COLUMNS = 71;            // CELDAS: ancho del tablero
    static const int ROWS = 76;               // CELDAS: alto del tablero

    SDL_Rect panel;
    static const int WIDTH_PANEL = 40;
    static const int HEIGHT_PANEL = 38;
    
    static const int MARGIN = 20;
};
