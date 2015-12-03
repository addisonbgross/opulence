#ifndef OPULENCE_ANIMATION_H
#define OPULENCE_ANIMATION_H

// general
#include <vector>
#include <math.h>

// opulence
#include "../model/Model.h"
#include "../../container/obj_data.h"

class Animation : public Entity {
private:
    std::vector<Model*> *frames;
    Model *currentModel;
    float frameCounter = 0;
    float rate = 1.0;

    // ping pong animation mode
    bool isPingPong = false, pingPongAscending = true;
    bool isRunning = true, isOnce = false;

public:
    int id;

    ~Animation();
    Animation(float x, float y, float z, std::vector<Model*> *frames);
    void runOnce();
    void restart();

    // get
    float getWidth();
    float getHeight();
    float getDepth();
    bool getIsRunning();
    bool getIsOnce();
    float getRate();
    float * getScale();
    bool getPingPong();
    Model * getFrame(int i);
    Model * getCurrentFrame();
    int getNumFrames();

    // set
    void setRate(float rate);
    void setScale(float scale);
    void setPingPong(bool pong);
};


#endif
