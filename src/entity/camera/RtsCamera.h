#ifndef OPULENCE_RTSCAMERA_H
#define OPULENCE_RTSCAMERA_H

#include "Camera.h"

class RtsCamera : public Camera {
private:

public:
    RtsCamera();
    RtsCamera(float x, float y, float z);

    // move
    void moveForward(float n);
    void moveLeft(float n);
    void moveRight(float n);
    void moveBack(float n);
    void rotateVertical(float deg);
    void rotateHorizontal(float deg);
};

#endif
