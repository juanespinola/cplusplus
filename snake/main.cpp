#include <iostream>
#include <vector>
#include <SDL3/SDL.h>


struct Position
{
    int x;
    int y;
};


struct Snake
{
    Position initialPosition;
    int length;
};

struct Delta
{
    int dx;
    int dy;
};


void keyboardInput(SDL_Keycode key, Delta &direccion)
{
    if(key == SDLK_UP && direccion.dy != 1)     { direccion.dx = 0; direccion.dy = -1; } 
    if(key == SDLK_DOWN && direccion.dy != -1)   { direccion.dx = 0; direccion.dy = 1; }
    if(key == SDLK_LEFT && direccion.dx != 1)   { direccion.dx = -1; direccion.dy = 0; }
    if(key == SDLK_RIGHT && direccion.dx != -1)  { direccion.dx = 1; direccion.dy = 0; }
}


void drawSnake(SDL_Renderer* renderer, std::vector<Position>& snake, int cellSize)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (const Position& segment : snake) 
    {
        SDL_FRect rect;

        rect.x = segment.x * cellSize;
        rect.y = segment.y * cellSize;
        rect.w = cellSize;
        rect.h = cellSize;

        SDL_RenderFillRect(renderer, &rect);
    }
}

void moveSnake(std::vector<Position>& snake, Delta direction, bool eat) 
{
    // falta agregar delta
    Position newHead = { snake[0].x + direction.dx, snake[0].y + direction.dy };
    snake.insert(snake.begin(), newHead);

    if(!eat)
    {
        snake.pop_back();
    }
        
}




int main(int argc, char const *argv[])
{    
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("Snake", 800, 600, 0, &window, &renderer);
    // SDL_SetRenderScale(renderer, 4, 4);
    std::vector<Position> snake =
    {
        {1, 3},
        {2, 3},
        {3, 3},
    };
    
    bool running = true;
    SDL_Event event;
    
    Delta direccionInicial = { 0, 0 };

    Uint64 lastMovement = SDL_GetTicks();
    const Uint64 intervalMovement = 150;


    if (!renderer) {
        std::cout << "Error creando renderer: " << SDL_GetError() << std::endl;
    }

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;

                case SDL_EVENT_KEY_DOWN:
                    keyboardInput(event.key.key, direccionInicial);
                    break;

                default:
                    break;
            }
            
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        Uint64 now = SDL_GetTicks();
        if(now - lastMovement >= intervalMovement)
        {
            moveSnake(snake, direccionInicial, false);
            lastMovement = now;
        }



        // draw snake
        drawSnake(renderer, snake, 10);

       
        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // SDL_FRect rect = { 400 - 25, 300 - 25, 50, 50 };   // un cuadrado de 50x50 en el centro
        // SDL_RenderFillRect(renderer, &rect);

        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // SDL_RenderPoint(renderer, 800/2, 600/2);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
