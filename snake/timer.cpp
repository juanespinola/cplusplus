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
}

float Timer::getDeltaTime()
{
    return deltaTime;
}

void Timer::restart()
{
    deltaTime = 0;   
    lastTick = SDL_GetTicks64();
}
