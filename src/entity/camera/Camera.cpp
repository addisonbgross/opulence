#include "Camera.h"
Camera::Camera()
{
    eye   = new glm::vec3(0.0, 0.0, 5.0);
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
    eye->z += zoomInertia;
}

void Camera::decrementZoom()
{
    eye->z -= zoomInertia;
}

void Camera::moveLeft()
{
    eye->x   += 0.1;
}

void Camera::moveRight()
{
    eye->x   -= 0.1;
}

void Camera::moveUp()
{
    eye->y   += 0.1;
}

void Camera::moveDown()
{
    eye->y   -= 0.1;
}

void Camera::rotateVertical(GLfloat deg)
{
    glm::vec3 camFocus = *eye - *focus;
    glm::mat4 rotationMatrix(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, deg, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec4 temp = rotationMatrix * glm::vec4(camFocus, 1.0f);
    eye->x = temp.x;
    eye->y = temp.y;
    eye->z = temp.z;
}

void Camera::rotateHorizontal(GLfloat deg)
{
    glm::vec3 camFocus = *eye - *focus;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), deg, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec4 temp = rotationMatrix * glm::vec4(camFocus, 1.0f);
    eye->x = temp.x;
    eye->y = temp.y;
    eye->z = temp.z;
}