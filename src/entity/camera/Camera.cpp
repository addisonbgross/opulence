#include "Camera.h"
Camera::Camera()
{
    eye   = new glm::vec3(10.0, 30.0, 10.0);
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

glm::quat Camera::getOrientation()
{
    glm::vec3 u = glm::vec3(0, 0, 1);
    glm::vec3 v = glm::normalize( *eye - *focus );
    glm::vec3 w = glm::cross(u, v);
    glm::quat q = glm::quat(1.f + glm::dot(u, v), w.x, w.y, w.z);
    return glm::normalize(q);
}

void Camera::incrementZoom()
{
    eye->y += 1;
}

void Camera::decrementZoom()
{
    if (eye->y > 3) {
        eye->y -= 1;
    }
}

void Camera::updateBearing()
{
    glm::vec3 camFocus = *eye - *focus;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f));
    *lateralAxis = glm::normalize(rotationMatrix * glm::vec4(camFocus, 1.0f));
}
