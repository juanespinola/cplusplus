#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <ctime>

#include "char_letras.h"
#include "scene_manager.h"
#include "menu_scene.h"
#include "globals.h"
#include "timer.h"

// enum class GameState
// {
//     MENU,
//     PLAYING,
//     QUIT
// };





// void keyboardInput(SDL_Keycode key, Delta &direccion)
// {
//     if(key == SDLK_UP && direccion.dy != 1)     { direccion.dx = 0; direccion.dy = -1; } 
//     if(key == SDLK_DOWN && direccion.dy != -1)   { direccion.dx = 0; direccion.dy = 1; }
//     if(key == SDLK_LEFT && direccion.dx != 1)   { direccion.dx = -1; direccion.dy = 0; }
//     if(key == SDLK_RIGHT && direccion.dx != -1)  { direccion.dx = 1; direccion.dy = 0; }
// }

// void menuInput(SDL_Keycode key, int &selectedOption)
// {
//     if(key == SDLK_UP) { selectedOption = (selectedOption - 1 + MENU_OPTIONS ) % MENU_OPTIONS; } 
//     if(key == SDLK_DOWN) { selectedOption = (selectedOption + 1 ) % MENU_OPTIONS; } 
//     std::cout << selectedOption << std::endl;
// }



int main(int argc, char *argv[])
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    srand(time(nullptr));

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    // SDL_SetRenderScale(renderer, 4, 4);

    /*
    * VARIABLES DE MENU
    */

    // GameState currentState = GameState::MENU; // valor inicial


    /*
    *   VARIABLES DE JUEGO
    */
    
    // int selectedOption = 0;
    /*
    *    VARIABLES DEL SISTEMA
    */
    SDL_Event event;
    // Uint64 now = SDL_GetTicks();

    if (!renderer) {
        std::cout << "Error creando renderer: " << SDL_GetError() << std::endl;
    }

    SceneManager sceneManager;
    sceneManager.changeScene(new MenuScene(&sceneManager));
    Timer timer;

    while (!sceneManager.isQuitRequested())
    {
        sceneManager.applyPendingScene();
        while (SDL_PollEvent(&event))
        {
            // esto permite cerrar el juego con la x, gil
            if(event.type == SDL_QUIT)
            {
                sceneManager.requestQuit();
            }

            
            sceneManager.handleInput(event);
            
            // if(currentState == GameState::MENU)
            // {
            //     if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            //     {
            //         currentState = (selectedOption == 0) ? GameState::PLAYING : GameState::QUIT;
            //         std::cout << "selectedOption: " << selectedOption 
            //         << " | currentState: " << static_cast<int>(currentState) 
            //         << std::endl;
            //     } 
            //     else if(event.type == SDL_KEYDOWN)
            //     {
            //         menuInput(event.key.keysym.sym, selectedOption);
            //     }
            // } 
            // else if(currentState == GameState::PLAYING) 
            // {
            //     if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            //     {
            //         currentState = GameState::QUIT;
            //     } 
            //     else if(event.type == SDL_KEYDOWN)
            //     {
            //         keyboardInput(event.key.keysym.sym, direccionInicial);
            //     } 
                 
            // } else if (currentState == GameState::QUIT)
            // {
            //     exit(1);
            // } 
            
            
            // switch (event.type)
            // {
            //     // case SDL_EVENT_QUIT:
            //     case SDL_QUIT:
            //         running = false;
            //         break;

            //     // case SDL_EVENT_KEY_DOWN:
            //     case SDL_KEYDOWN:
                    

            //         // keyboardInput(event.key.key, direccionInicial);
            //         keyboardInput(event.key.keysym.sym, direccionInicial);
            //         break;

            //     default:
            //         break;
            // }
        }
        timer.tick();    
        float deltaTime = timer.getDeltaTime();

        sceneManager.update(deltaTime);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        sceneManager.render(renderer);

        

        // update
        // if(currentState == GameState::MENU)
        // {
        //     SDL_Color normal = {255, 255, 255, 255};   // blanco
        //     SDL_Color resaltado = {255, 255, 0, 255};  // amarillo, por ejemplo


        //     drawText(renderer, "SNAKE", {250, 80}, 8, 4, normal);
        //     drawText(renderer, "JUGAR", {300, 250}, 5, 3, (selectedOption == 0) ? resaltado : normal);
        //     drawText(renderer, "SALIR", {300, 330}, 5, 3, (selectedOption == 1) ? resaltado : normal);
        // }
        // else if(currentState == GameState::PLAYING)
        // {

        
        //     Uint64 now = SDL_GetTicks();
        //     if(now - lastMovement >= intervalMovement)
        //     {
        //         moveSnake(snake, direccionInicial, eat);
        //         // collision detection
        //         collisionDetection(snake, food, eat, grid);
        //         lastMovement = now;
        //     }



        //     // draw snake
        //     drawSnake(renderer, snake, 10);
        //     // draw food
        //     drawFood(renderer, food, 10);
        
        //     // generateFood(food, snake);
        //     // draw grid
        //     drawGrid(renderer, grid);
        // }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
