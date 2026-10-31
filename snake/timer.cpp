#include "timer.h"

Timer::Timer()
{
   restart();
}

void Timer::tick()
{
    Uint64 now = SDL_GetTicks64();
    deltaTime = ((float)(now - lastTick)/1000.0f);
    lastTick = now;

    frames++;
    alcanciaFps +=deltaTime;
    if(alcanciaFps >= 1.0)
    {
        fps = frames;
        frames = 0;
        alcanciaFps -= 1.0;
    }


}

float Timer::getDeltaTime()
{
    return deltaTime;
}

void Timer::restart()
{
    deltaTime = 0;   
    lastTick = SDL_GetTicks64();

    alcanciaFps = 0;
    frames = 0;
    fps = 0;
}

int Timer::getFPS()
{
    return fps;
}
