#include "TimeManager.h"

/**
 * start() - start current timer
 */
void TimeManager::start()
{
    if (!running) {
        running = true;
        origin = SDL_GetTicks();
    }
}

/**
 * pause() - pause current timer
 */
void TimeManager::pause()
{
    running = false;
    paused = SDL_GetTicks() - origin;
}

/**
 * reportStats() - print out informational string
 *
 * @modify std::cout
 */
void TimeManager::reportStats()
{
    std::cout << "Time Elapsed: " << getTime() << " ms" << std::endl;
}

/*** get ***/

/**
 * getTime() - get current time elapsed
 *
 * @return current time in milliseconds
 */
float TimeManager::getTime()
{
    if (!running) {
        origin = SDL_GetTicks();
        return paused;
    } else {
        return SDL_GetTicks() - origin;
    }
}
