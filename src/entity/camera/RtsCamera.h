#ifndef OPULENCE_RTSCAMERA_H
#define OPULENCE_RTSCAMERA_H

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

// general
#include <iostream>

#include "Camera.h"

class RtsCamera : public Camera {
private:
    glm::vec4 *lateralAxis;

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
    void updateBearing();
};

#endif
