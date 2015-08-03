#include "Camera.h"
Camera::Camera()
{
    eye   = new glm::vec3(0.0, 5.0, 10.0);
    focus = new glm::vec3(0.0, 0.0, 0.0);
    top   = new glm::vec3(0.0, 1.0, 0.0);
}

Camera::Camera(float x, float y, float z)
{
    eye   = new glm::vec3(x, y, z);
    focus = new glm::vec3(0.0, 0.0, 0.0);
    top   = new glm::vec3(0.0, 1.0, 0.0);
}

Camera::~Camera()
{
    delete eye;
    delete focus;
    delete top;
}

/*** setters ***/

void Camera::setEye(glm::vec3 *newEye)
{
    eye = newEye;
}

void Camera::setFocus(glm::vec3 *newFocus)
{
    focus = newFocus;
}

void Camera::setTop(glm::vec3 *newTop)
{
    top = newTop;
}

/*** getters ***/

glm::vec3 * Camera::getEye()
{
    return eye;
}

glm::vec3 * Camera::getFocus()
{
    return focus;
}

glm::vec3 * Camera::getTop()
{
    return top;
}

void Camera::incrementZoom()
{
    eye->y += 0.5;
}

void Camera::decrementZoom()
{
    if (eye->y > 5) {
        eye->y -= 0.5;
    }
}
