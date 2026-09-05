#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <ctime>

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

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


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
        // SDL_FRect rect;
        SDL_Rect rect;

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

void drawFood(SDL_Renderer* renderer, Position food, int cellSize)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect;
    rect.x = food.x * cellSize;
    rect.y = food.y * cellSize;
    rect.w = cellSize;
    rect.h = cellSize;

    SDL_RenderFillRect(renderer, &rect);
}


void generateFood(Position &food, std::vector<Position> &snake, SDL_Rect &grid)
{
    bool validPosition = false;
    while(!validPosition)
    {
        food.x = rand() % 80; // assuming the grid width is 80
        food.y = rand() % 60; // assuming the grid height is 60

        validPosition = true;
	    // compara el cuerpo de snake contra la pos de la comida para evitar colocarse encima
        for(const Position& segment : snake)
        {
            if(segment.x == food.x && segment.y == food.y)
            {
                validPosition = false;
                break;
            }
        }
        // comparamos la comida contra los limites del grid para evitar que se salga de la pantalla
        if(food.x < 0 || food.x >= grid.w || food.y < 0 || food.y >= grid.h)
        {
            validPosition = false;
        }
        
    }
}

void collisionDetection(std::vector<Position>& snake, Position &food, bool &eat, SDL_Rect &grid)
{
	// para entender la colision de 2 objetos, es necesario que la parte de tu obj principal y su posicion, 
	// coinsidan con la del objeto a collisionar
    if(snake[0].x == food.x && snake[0].y == food.y)
    {
        eat = true;
        // std::cout << "Collision" << std::endl;
        generateFood(food, snake, grid);
    }
    else
    {
        eat = false;
    }
}

void drawGrid(SDL_Renderer* renderer, SDL_Rect &grid)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    // SDL_RenderFillRect(renderer, &rect); // dibuja un cuadrado blanco en el centro de la ventana
    SDL_RenderDrawRect(renderer, &grid); // dibuja un cuadrado blanco en el centro de la ventana           
}


int main(int argc, char const *argv[])
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    srand(time(nullptr));

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_HEIGHT, SCREEN_WIDTH, 0, &window, &renderer);
    // SDL_SetRenderScale(renderer, 4, 4);
    std::vector<Position> snake =
    {
        {1, 3},
        {2, 3},
        {3, 3},
    };
    Position food = { 5, 5 };
    bool eat = false;

    bool running = true;
    SDL_Event event;
    
    Delta direccionInicial = { 0, 0 };

    Uint64 lastMovement = SDL_GetTicks();
    const Uint64 intervalMovement = 150;
    SDL_Rect grid = { 2, 2, SCREEN_HEIGHT - 4, SCREEN_WIDTH - 4 };

    if (!renderer) {
        std::cout << "Error creando renderer: " << SDL_GetError() << std::endl;
    }

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                // case SDL_EVENT_QUIT:
                case SDL_QUIT:
                    running = false;
                    break;

                // case SDL_EVENT_KEY_DOWN:
                case SDL_KEYDOWN:
                    // keyboardInput(event.key.key, direccionInicial);
                    keyboardInput(event.key.keysym.sym, direccionInicial);
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
            moveSnake(snake, direccionInicial, eat);
            // collision detection
            collisionDetection(snake, food, eat, grid);
            lastMovement = now;
        }



        // draw snake
        drawSnake(renderer, snake, 10);
        // draw food
        drawFood(renderer, food, 10);
       
        // generateFood(food, snake);
        // draw grid
        drawGrid(renderer, grid);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
