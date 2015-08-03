#include "Animation.h"

Animation::Animation() {}

Animation::~Animation() {}

Animation::Animation(float x, float y, float z, std::vector<Model*> *frames) : Entity()
{
    this->frames = frames;
}

Model * Animation::getFrame(int i)
{
    return frames->at(i);
}

Model * Animation::getCurrentFrame()
{
    Model *currentModel;
    if (isPingPong) {
        if (pingPongAscending) {
            if (frameCounter < 6) {
                currentModel = frames->at(frameCounter);
                ++frameCounter;
            } else {
                pingPongAscending = false;
                --frameCounter;
                currentModel = frames->at(frameCounter);
            }

        } else {
            if (frameCounter > 0) {
                currentModel = frames->at(frameCounter);
                --frameCounter;
            } else {
                pingPongAscending = true;
                ++frameCounter;
                currentModel = frames->at(frameCounter);
            }
        }
    }
    return currentModel;
}

