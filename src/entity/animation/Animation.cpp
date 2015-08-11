#include "Animation.h"

Animation::~Animation() {}

Animation::Animation(float x, float y, float z, std::vector<Model*> *frames) : Entity(x, y, z)
{
    this->frames = frames;
}

/*** get ***/

float Animation::getRate()
{
    return rate;
}

float * Animation::getScale()
{
    return frames->at(0)->getScale();
}

bool Animation::getPingPong()
{
    return isPingPong;
}

Model * Animation::getFrame(int i)
{
    return frames->at(i);
}

Model * Animation::getCurrentFrame()
{
    Model *currentModel;
    int numFrames = frames->size();

    // ping-pong mode
    if (isPingPong) {
        if (pingPongAscending) {
            if (frameCounter < numFrames) {
                currentModel = frames->at(floor(frameCounter));
                frameCounter += rate;
            } else {
                pingPongAscending = false;
                frameCounter -= rate;
                currentModel = frames->at(floor(frameCounter));
            }

        } else {
            if (frameCounter > 0) {
                currentModel = frames->at(floor(frameCounter));
                frameCounter -= rate;
            } else {
                pingPongAscending = true;
                frameCounter += rate;
                currentModel = frames->at(floor(frameCounter));
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

int Animation::getNumFrames()
{
    return frames->size();
}

/*** set ***/

void Animation::setRate(float rate)
{
    this->rate = rate;
}

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
