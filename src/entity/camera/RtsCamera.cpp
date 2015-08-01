#include "RtsCamera.h"

RtsCamera::RtsCamera(float x, float y, float z) : Camera(x, y, z) {}

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
    glm::vec3 camFocus = *eye - *focus;
    float rotationAngle = glm::radians(90.f);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec4 temp = glm::vec4(*eye, 1.0f) - (n * (rotationMatrix * glm::vec4(camFocus, 1.0f)));
    eye->x = temp.x;
    eye->z = temp.z;
    temp = glm::vec4(*focus, 1.0f) - (n * (rotationMatrix * glm::vec4(camFocus, 1.0f)));
    focus->x = temp.x;
    focus->z = temp.z;
}

void RtsCamera::moveRight(float n)
{
    glm::vec3 camFocus = *eye - *focus;
    float rotationAngle = glm::radians(90.f);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec4 temp = glm::vec4(*eye, 1.0f) + (n * (rotationMatrix * glm::vec4(camFocus, 1.0f)));
    eye->x = temp.x;
    eye->z = temp.z;
    temp = glm::vec4(*focus, 1.0f) + (n * (rotationMatrix * glm::vec4(camFocus, 1.0f)));
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
    glm::vec3 camFocus = *eye - *focus;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), deg, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec4 temp = rotationMatrix * glm::vec4(*eye, 1.0f);
    eye->x = temp.x;
    eye->y = temp.y;
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
}