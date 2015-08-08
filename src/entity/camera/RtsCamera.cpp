#include "RtsCamera.h"

RtsCamera::RtsCamera() : Camera()
{
    bearing = new glm::vec4(1.0f);
    updateBearing();
}

RtsCamera::RtsCamera(float x, float y, float z) : Camera(x, y, z)
{
    bearing = new glm::vec4(1.0f);
    updateBearing();
}

void RtsCamera::moveForward(float n)
{
    glm::vec3 camFocus = *eye - *focus;
    glm::vec3 temp = *eye - (n * camFocus);
    eye->x = temp.x;
    eye->z = temp.z;
    temp = *focus - (n * camFocus);
    focus->x = temp.x;
    focus->z = temp.z;
}

void RtsCamera::moveLeft(float n)
{
    glm::vec4 temp = glm::vec4(*eye, 1.0f) - (n * *bearing);
    eye->x = temp.x;
    eye->z = temp.z;
    temp = glm::vec4(*focus, 1.0f) - (n * *bearing);
    focus->x = temp.x;
    focus->z = temp.z;
}

void RtsCamera::moveRight(float n)
{
    glm::vec4 temp = glm::vec4(*eye, 1.0f) + (n * *bearing);
    eye->x = temp.x;
    eye->z = temp.z;
    temp = glm::vec4(*focus, 1.0f) + (n * *bearing);
    focus->x = temp.x;
    focus->z = temp.z;
}

void RtsCamera::moveBack(float n)
{
    glm::vec3 camFocus = *eye - *focus;
    glm::vec3 temp = *eye + (n * camFocus);
    eye->x = temp.x;
    eye->z = temp.z;
    temp = *focus + (n * camFocus);
    focus->x = temp.x;
    focus->z = temp.z;
}

void RtsCamera::rotateVertical(float deg)
{
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), deg, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec4 temp = rotationMatrix * glm::vec4(*eye, 1.0f);
    eye->x = temp.x;
    if (temp.y > 3) {
        eye->y = temp.y;
    } else {
        eye->y = 3;
    }
    eye->z = temp.z;
}

void RtsCamera::rotateHorizontal(float deg)
{
    glm::vec3 camFocus = *eye - *focus;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), deg, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec4 temp = rotationMatrix * glm::vec4(*eye, 1.0f);
    eye->x = temp.x;
    eye->y = temp.y;
    eye->z = temp.z;

    updateBearing();
}

void RtsCamera::updateBearing()
{
    glm::vec3 camFocus = *eye - *focus;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f));
    *bearing = rotationMatrix * glm::vec4(camFocus, 1.0f);
}
