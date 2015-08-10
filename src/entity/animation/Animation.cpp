#include "Animation.h"

Animation::Animation() {}

Animation::~Animation() {}

Animation::Animation(float x, float y, float z, std::vector<Model*> *frames) : Entity(x, y, z)
{
    this->frames = frames;
}

/*** get ***/

Model * Animation::getFrame(int i)
{
    return frames->at(i);
}

bool Animation::getPingPong()
{
    return isPingPong;
}

int Animation::getNumFrames()
{
    return frames->size();
}

Model * Animation::getCurrentFrame()
{
    Model *currentModel;
    int numFrames = frames->size();

    // ping-pong mode
    if (isPingPong) {
        if (pingPongAscending) {
            if (frameCounter < numFrames) {
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

    // standard linear mode
    } else {
        if (frameCounter < numFrames) {
            currentModel = frames->at(frameCounter);
            ++frameCounter;
        } else {
            --frameCounter;
            currentModel = frames->at(frameCounter);
        }
    }

    currentModel->position.x = this->position.x;
    currentModel->position.y = this->position.y;
    currentModel->position.z = this->position.z;

    return currentModel;
}

/*** set ***/

void Animation::setScale(float scale)
{
    for (int i = 0; i < frames->size(); ++i) {
        frames->at(i)->setScale(scale);
    }
}

void Animation::setPingPong(bool pong)
{
    isPingPong = pong;
}
