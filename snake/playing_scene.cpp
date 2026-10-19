#include "playing_scene.h"


void moveSnake(std::vector<Position>& snake, Delta direction, bool eat) 
{
    // falta agregar delta
    Position newHead = { 
        snake[0].x + direction.dx, 
        snake[0].y + direction.dy 
    };

    snake.insert(snake.begin(), newHead);

    if(!eat)
    {
        snake.pop_back();
    }
        
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


void PlayingScene::keyboardInput(SDL_Keycode key)
{
    if(key == SDLK_UP && direction.dy != 1)     { direction.dx = 0; direction.dy = -1; } 
    if(key == SDLK_DOWN && direction.dy != -1)   { direction.dx = 0; direction.dy = 1; }
    if(key == SDLK_LEFT && direction.dx != 1)   { direction.dx = -1; direction.dy = 0; }
    if(key == SDLK_RIGHT && direction.dx != -1)  { direction.dx = 1; direction.dy = 0; }
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

    // aqui verificamos si choco contra el grid
    if(snake[0].x < 0 || snake[0].x >= grid.w || snake[0].y < 0 || snake[0].y >= grid.h)
    {
        // std::cout << "Game Over" << std::endl;
        exit(0);
    }

}



void PlayingScene::drawSnake(SDL_Renderer* renderer, std::vector<Position>& snake)
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


void PlayingScene::drawFood(SDL_Renderer* renderer, Position food)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect;
    rect.x = food.x * cellSize;
    rect.y = food.y * cellSize;
    rect.w = cellSize;
    rect.h = cellSize;

    SDL_RenderFillRect(renderer, &rect);
}



void PlayingScene::drawGrid(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    // SDL_RenderFillRect(renderer, &rect); // dibuja un cuadrado blanco en el centro de la ventana
    SDL_RenderDrawRect(renderer, &grid); // dibuja un cuadrado blanco en el centro de la ventana           
}



PlayingScene::PlayingScene(SceneManager *manager)
{
    sceneManager = manager;

    snake = {
        {1, 3},
        {2, 3},
        {3, 3},
    };

    food = { 5, 5 };
    eat = false;
    direction = { 0, 0 };

    // disenho
    grid = { 
        2, 
        2, 
        SCREEN_WIDTH - 4, 
        SCREEN_HEIGHT - 4 
    };

    // lastMovement = SDL_GetTicks();
    elapsedTime = 0;
    intervalMovement = 0.15f;
}

void PlayingScene::handleInput(SDL_Event &event)
{
    if (event.type != SDL_KEYDOWN)
    {
        return;
    }

    SDL_Keycode key = event.key.keysym.sym;

    keyboardInput(key);
}

void PlayingScene::update(float deltaTime)
{
    
    elapsedTime += deltaTime;

    // std::cout << elapsedTime << std::endl;

    if(elapsedTime >= intervalMovement)
    {
        moveSnake(snake, direction, eat);
        collisionDetection(snake, food, eat, grid);
        elapsedTime -= intervalMovement;
    }
   
    
}

void PlayingScene::render(SDL_Renderer *renderer)
{
    drawSnake(renderer, snake);
    drawFood(renderer, food);

    drawGrid(renderer);
}

