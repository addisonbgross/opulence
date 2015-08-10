#ifndef OPULENCE_TIMEMANAGER_H
#define OPULENCE_TIMEMANAGER_H

// general
#include <iostream>
#include <SDL_timer.h>

class TimeManager {
private:

public:
    //The timer starting time
    float origin = 0;
    float paused = 0;

    //The timer start/stop flag
    bool running = true;

    TimeManager();
    ~TimeManager();
    void start();
    void stop();
    void reportStats();

    // get
    float getTime();
};


#endif
