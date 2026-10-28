#include "playing_scene.h"
#include "scene_manager.h"
#include "gameover_scene.h"

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


void generateFood(Position &food, std::vector<Position> &snake, int columns, int rows)
{
    bool validPosition = false;
    while(!validPosition)
    {
        food.x = rand() % columns;  // assuming the grid width is columns
        food.y = rand() % rows;     // assuming the grid height is rows

        validPosition = true;
	    // compara el cuerpo de snake contra la pos de la comida para evitar colocarse encima
        for(const Position& segment : snake)
        {
            if(pointVsPoint(segment, food))
            {
                validPosition = false;
                break;
            }
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

bool collisionDetection(std::vector<Position>& snake, Position &food, bool &eat, int columns, int rows )
{
	// para entender la colision de 2 objetos, es necesario que la parte de tu obj principal y su posicion, 
	// coinsidan con la del objeto a collisionar
    if(pointVsPoint(snake[0], food))
    {
        eat = true;
        // std::cout << "Collision" << std::endl;
        generateFood(food, snake, columns, rows);
    }
    else
    {
        eat = false;
    }

    // aqui verificamos si choco contra el board
    SDL_Rect board;
    board.x = 0;
    board.y = 0;
    board.h = rows;
    board.w = columns;

    // if(!pointInRect(snake[0], board))
    // {
    //     // std::cout << "Game Over" << std::endl;
    //     exit(0);
    // }
    return !pointInRect(snake[0], board);

}

void checkFood(std::vector<Position>& snake, Position &food, bool &eat, int columns, int rows)
{
    if(pointVsPoint(snake[0], food))
    {
        eat = true;
        // std::cout << "Collision" << std::endl;
        generateFood(food, snake, columns, rows);
    }
    else
    {
        eat = false;
    }
}

bool isHittingWall(std::vector<Position>& snake, int columns, int rows)
{
    // aqui verificamos si choco contra el board
    SDL_Rect board;
    board.x = 0;
    board.y = 0;
    board.h = rows;
    board.w = columns;

    // if(!pointInRect(snake[0], board))
    // {
    //     // std::cout << "Game Over" << std::endl;
    //     exit(0);
    // }
    return !pointInRect(snake[0], board);
}

bool isHittingSelf(std::vector<Position>& snake)
{
    for (size_t i = 1; i < snake.size(); i++)
    {
        if(pointVsPoint(snake[0], snake[i]))
        {
            return true;
        }
    }
    return false;
}



void PlayingScene::drawSnake(SDL_Renderer* renderer, std::vector<Position>& snake)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (const Position& segment : snake) 
    {
        // SDL_FRect rect;
        SDL_Rect rect;

        rect.x = grid.x + segment.x * CELL_SIZE;
        rect.y = grid.y + segment.y * CELL_SIZE;
        rect.w = CELL_SIZE;
        rect.h = CELL_SIZE;

        SDL_RenderFillRect(renderer, &rect);
    }
}


void PlayingScene::drawFood(SDL_Renderer* renderer, Position food)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect;
    rect.x = grid.x + food.x * CELL_SIZE;
    rect.y = grid.y + food.y * CELL_SIZE;
    rect.w = CELL_SIZE;
    rect.h = CELL_SIZE;

    SDL_RenderFillRect(renderer, &rect);
}



void PlayingScene::drawGrid(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    // SDL_RenderFillRect(renderer, &rect); // dibuja un cuadrado blanco en el centro de la ventana
    SDL_RenderDrawRect(renderer, &grid); // dibuja un cuadrado blanco en el centro de la ventana           
}

void PlayingScene::drawPanel(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    // SDL_RenderFillRect(renderer, &rect); // dibuja un cuadrado blanco en el centro de la ventana
    SDL_RenderDrawRect(renderer, &panel); // dibuja un cuadrado blanco en el centro de la ventana           
}



PlayingScene::PlayingScene(SceneManager *manager)
{
    sceneManager = manager;

    snake = {
        {3, 3},
        {2, 3},
        {1, 3},
    };

    food = { 5, 5 };
    eat = false;
    direction = { 1, 0 };

    // disenho
    // GRID: pegado a la derecha
    grid.w = COLUMNS * CELL_SIZE;                 // 710
    grid.h = ROWS * CELL_SIZE;                    // 760
    grid.x = SCREEN_WIDTH - MARGIN - grid.w;      // 1024 - 20 - 710 = 294
    grid.y = MARGIN;                              // 20

    // PANEL: lo que sobra a la izquierda
    panel.x = MARGIN;                             // 20
    panel.y = MARGIN;                             // 20
    panel.w = grid.x - MARGIN - MARGIN;           // 294 - 40 = 254
    panel.h = grid.h;                   

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
        // if(collisionDetection(snake, food, eat, columns, rows))
        if(isHittingWall(snake, COLUMNS, ROWS) || isHittingSelf(snake))
        {
            // aqui hace el cambio de escena
            sceneManager->changeScene(new GameOverScene(sceneManager));
            return;
        }
        checkFood(snake, food, eat, COLUMNS, ROWS);
        elapsedTime -= intervalMovement;
    }
   
    
}

void PlayingScene::render(SDL_Renderer *renderer)
{
    drawSnake(renderer, snake);
    drawFood(renderer, food);

    drawGrid(renderer);
    drawPanel(renderer);
}

