#ifndef OPULENCE_RTSCAMERA_H
#define OPULENCE_RTSCAMERA_H

#include "Camera.h"

class RtsCamera : public Camera {
private:
    float verticalRotationRestriction = glm::half_pi<float>() * 0.85f;
    float heightTopRestriction = 50.0f;
    float heightBottomRestriction = 2.0f;

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
    void incrementZoom();
    void decrementZoom();

    // get
    float getAngleToGround( glm::vec3 vec );
};

#endif
