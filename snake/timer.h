#pragma once

#include <SDL2/SDL.h>


class Timer
{
private:
    float deltaTime; 
    Uint64 lastTick;
    
public:
    Timer();

    void tick();
    float getDeltaTime();
    void restart();
};