#include "Camera.h"

Camera::Camera()
{
    eye   = new glm::vec3(0.0, 1.0, 0.0);
    focus = new glm::vec3(0.0, 0.0, -4.0);
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
