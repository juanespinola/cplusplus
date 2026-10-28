
#include "gameover_scene.h"
#include "scene_manager.h"
#include "playing_scene.h"
#include "char_letras.h"

GameOverScene::GameOverScene(SceneManager *manager)
{
    sceneManager = manager;
    selectedOption = 0;
}

GameOverScene::~GameOverScene()
{
    std::cout << "Se destruyo GameOver Scene" << std::endl;
}

void GameOverScene::handleInput(SDL_Event &event)
{
    if (event.type != SDL_KEYDOWN)
    {
        return;
    }

    SDL_Keycode key = event.key.keysym.sym;

    if (key == SDLK_UP)
    {
        selectedOption = (selectedOption - 1 + MENU_OPTIONS) % MENU_OPTIONS;
    }
    if (key == SDLK_DOWN)
    {
        selectedOption = (selectedOption + 1) % MENU_OPTIONS;
    }
    if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
    {
        if (selectedOption == 0)
        {
            sceneManager->changeScene(new PlayingScene(sceneManager));
        } 
        else if(selectedOption == 1)
        {
            sceneManager->requestQuit();
        }
    }
}

void GameOverScene::update(float deltaTime)
{
}

void GameOverScene::render(SDL_Renderer *renderer)
{
    SDL_Color normal = {255, 255, 255, 255};   // blanco
    SDL_Color resaltado = {255, 255, 0, 255};  // amarillo, por ejemplo


    drawText(renderer, "PERDISTE JUEPUTA", {250, 80}, 8, 4, normal);
    drawText(renderer, "JUGAR", {300, 250}, 5, 3, (selectedOption == 0) ? resaltado : normal);
    drawText(renderer, "SALIR", {300, 330}, 5, 3, (selectedOption == 1) ? resaltado : normal);
}
