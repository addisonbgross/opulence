#ifndef OPULENCE_TIMEMANAGER_H
#define OPULENCE_TIMEMANAGER_H

// general
#include <iostream>
#include <SDL_timer.h>

/**
 * TimeManager - acts as a stopwatch
 */
class TimeManager {
private:
    float origin = 0;     // the beginning time of the current time framge
    float paused = 0;     // the saved time when paused
    float lastLap = 0;    // the time since the last getLap() call
    bool running = true;  // the timer start/stop flag

public:
    void start();         // start current timer
    void pause();         // pause current timer
    void reportStats();   // print informational string to std::cout

    // get
    float getTime();      // get current time elapsed
    float getLap();       // get time since the last time this was used
};

#endif
