#ifndef OPULENCE_RTSCAMERA_H
#define OPULENCE_RTSCAMERA_H

#include "Camera.h"

class RtsCamera : public Camera {
private:
    float cameraVelocity = 1.5f;
    float zoomInSpeed = 1.03f;
    float zoomOutSpeed = 0.97f;
    float MAX_ZOOM = 200.0f;
    float MIN_ZOOM = 3.0f;
    float ROTATION_LIMIT = glm::half_pi<float>() * 0.80f;

public:
    RtsCamera();
    RtsCamera(float x, float y, float z);

    // move
    void move(float x, float y, int screenWidth, int screenHeight);
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
