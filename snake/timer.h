#pragma once

#include <SDL2/SDL.h>


class Timer
{
private:
    float deltaTime; 
    Uint64 lastTick;

    // fps
    int frames;         
    float alcanciaFps;
    int fps;
    
public:
    Timer();

    void tick();
    float getDeltaTime();
    void restart();

    int getFPS();
};