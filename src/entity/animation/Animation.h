#ifndef OPULENCE_ANIMATION_H
#define OPULENCE_ANIMATION_H

// general
#include <vector>

// opulence
#include "../model/Model.h"
#include "../../container/obj_data.h"

class Animation : public Entity {
private:
    std::vector<Model*> *frames;
    int frameCounter = 0;

    // ping pong animation mode
    bool isPingPong = true, pingPongAscending = true;

public:
    Animation();
    ~Animation();
    Animation(float x, float y, float z, std::vector<Model*> *frames);

    // get
    GLfloat * getScale();
    bool getPingPong();
    Model * getFrame(int i);
    Model * getCurrentFrame();
    int getNumFrames();

    // set
    void setScale(float scale);
    void setPingPong(bool pong);
};


#endif

