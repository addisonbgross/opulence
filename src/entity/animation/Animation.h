#ifndef OPULENCE_ANIMATION_H
#define OPULENCE_ANIMATION_H

// general
#include <vector>

// opulence
#include "../model/Model.h"
#include "../../container/obj_data.h"

class Animation : Entity {
private:
    std::vector<Model*> *frames;
    int frameCounter = 0;

    bool isPingPong = true, pingPongAscending = true;

public:
    Animation();
    ~Animation();
    Animation(float x, float y, float z, std::vector<Model*> *frames);

    // get
    Model * getFrame(int i);
    Model * getCurrentFrame();
};


#endif

