
#include "menu_scene.h"
#include "scene_manager.h"
#include "playing_scene.h"
#include "char_letras.h"

MenuScene::MenuScene(SceneManager *manager)
{
    sceneManager = manager;
    selectedOption = 0;
}

MenuScene::~MenuScene()
{
    std::cout << "Se destruyo Menu Scene" << std::endl;
}

void MenuScene::handleInput(SDL_Event &event)
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
    }
}

void MenuScene::update(float deltaTime)
{
}

void MenuScene::render(SDL_Renderer *renderer)
{
    SDL_Color normal = {255, 255, 255, 255};   // blanco
    SDL_Color resaltado = {255, 255, 0, 255};  // amarillo, por ejemplo


    drawText(renderer, "SNAKE", {250, 80}, 8, 4, normal);
    drawText(renderer, "JUGAR", {300, 250}, 5, 3, (selectedOption == 0) ? resaltado : normal);
    drawText(renderer, "SALIR", {300, 330}, 5, 3, (selectedOption == 1) ? resaltado : normal);
}
