#ifndef OPULENCE_CAMERA_H
#define OPULENCE_CAMERA_H

// general
#include <glm/gtx/vector_angle.hpp>

// opulence
#include "../Entity.h"

class Camera : public Entity {
protected:
    glm::vec3 *eye;    // position of camera's view point
    glm::vec3 *focus;  // target of view
    glm::vec3 *top;    // relative up direction of camera
    glm::vec4 *lateralAxis; // axis orthogonal to the eye

public:
    Camera();
    Camera(float x, float y, float z);
    ~Camera();

    // move
    virtual void move(float x, float y, int screenWidth, int screenHeight) {};
    virtual void moveForward(float n) {};
    virtual void moveLeft(float n) {};
    virtual void moveRight(float n) {};
    virtual void moveBack(float n) {};
    virtual void rotateVertical(float deg) {};
    virtual void rotateHorizontal(float deg) {};
    virtual void zoomIn() {};
    virtual void zoomOut() {};

    // set
    void setEye(glm::vec3 *newEye);
    void setFocus(glm::vec3 *newFocus);
    void setTop(glm::vec3 *newTop);

    // get
    glm::vec3 * getEye();
    glm::vec3 * getFocus();
    glm::vec3 * getTop();
    glm::quat getOrientation();

    void updateBearing();
};

#endif
