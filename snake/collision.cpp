#include "collision.h"

bool pointVsPoint(Position a, Position b)
{
    return a.x == b.x && a.y == b.y;
}

bool pointInRect(Position point, SDL_Rect rect)
{
    // responde a la pregunta | esta adentro? | si fuera esta afuera? debe ser con ||
    return point.x >= rect.x &&             // pared left
            point.x < rect.x + rect.w &&    // pared right
            point.y >= rect.y &&            // pared up
            point.y < rect.y + rect.h ;     // pared down
}