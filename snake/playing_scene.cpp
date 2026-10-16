#include "playing_scene.h"

PlayingScene::PlayingScene(SceneManager *manager)
{
    sceneManager = manager;

    std::vector<Position> snake =
    {
        {1, 3},
        {2, 3},
        {3, 3},
    };

    Position food = { 5, 5 };
    bool eat = false;
    Delta direccionInicial = { 0, 0 };

    // disenho
    SDL_Rect grid = { 2, 2, SCREEN_WIDTH - 4, SCREEN_HEIGHT - 4 };
}

void PlayingScene::handleInput(SDL_Event &event)
{
    if (event.type != SDL_KEYDOWN)
    {
        return;
    }

    SDL_Keycode key = event.key.keysym.sym;
}

void PlayingScene::update(float deltaTime)
{
}

void PlayingScene::render(SDL_Renderer *renderer)
{
}
