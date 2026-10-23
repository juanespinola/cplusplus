#pragma once

#include <SDL2/SDL.h>
#include "types.h"

// collision punto a punto
bool pointVsPoint(Position a, Position b);
bool pointInRect(Position point, SDL_Rect rect);
// bool rectVsRect(); // aabb
// bool circleVsCircle();
