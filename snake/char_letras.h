#pragma once
#include <SDL2/SDL.h>
#include "types.h"

const int FONT_WIDTH = 5;
const int FONT_HEIGHT = 14;

const char** getLetraMayuscula(char c);
void drawText(SDL_Renderer* renderer, const char* text, Position pos, int pixelSize, int spacing, SDL_Color color);
void drawChar(SDL_Renderer* renderer, char c, Position pos, int pixelSize, SDL_Color color);