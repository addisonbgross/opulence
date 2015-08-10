#include "TimeManager.h"

TimeManager::TimeManager() {}

TimeManager::~TimeManager() {}

void TimeManager::start()
{
    if (!running) {
        running = true;
        origin = SDL_GetTicks();
    }
}

void TimeManager::stop()
{
    running = false;
    paused = SDL_GetTicks() - origin;
}

void TimeManager::reportStats()
{
    std::cout << "Time Elapsed: " << getTime() << " ms" << std::endl;
}

/*** get ***/

float TimeManager::getTime()
{
    if (!running) {
        origin = SDL_GetTicks();
        return paused;
    } else {
        return SDL_GetTicks() - origin;
    }
}
