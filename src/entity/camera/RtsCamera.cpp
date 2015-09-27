#include "RtsCamera.h"

RtsCamera::RtsCamera() : Camera()
{
    lateralAxis = new glm::vec4(1.0f);
    updateBearing();
}

RtsCamera::RtsCamera(float x, float y, float z) : Camera(x, y, z)
{
    lateralAxis = new glm::vec4(1.0f);
    updateBearing();
}

void RtsCamera::moveForward(float n)
{
    // height related acceleration
    float diff = glm::abs(eye->y) * 0.025;
    glm::vec3 camFocus = glm::normalize(*eye - *focus);

    eye->x -= (n + diff) * camFocus.x;
    eye->z -= (n + diff) * camFocus.z;
    focus->x -= (n + diff) * camFocus.x;
    focus->z -= (n + diff) * camFocus.z;
    updateBearing();
}

void RtsCamera::moveLeft(float n)
{
    // height related acceleration
    float diff = glm::abs(eye->y) * 0.025;

    eye->x -= (n + diff) * lateralAxis->x;
    eye->z -= (n + diff) * lateralAxis->z;
    focus->x -= (n + diff) * lateralAxis->x;
    focus->z -= (n + diff) * lateralAxis->z;
    updateBearing();
}

void RtsCamera::moveRight(float n)
{
    // height related acceleration
    float diff = glm::abs(eye->y) * 0.025;

    eye->x += (n + diff) * lateralAxis->x;
    eye->z += (n + diff) * lateralAxis->z;
    focus->x += (n + diff) * lateralAxis->x;
    focus->z += (n + diff) * lateralAxis->z;
    updateBearing();
}

void RtsCamera::moveBack(float n)
{
    // height related acceleration
    float diff = glm::abs(eye->y) * 0.025;
    glm::vec3 camFocus = glm::normalize(*eye - *focus);

    eye->x += (n + diff) * camFocus.x;
    eye->z += (n + diff) * camFocus.z;
    focus->x += (n + diff) * camFocus.x;
    focus->z += (n + diff) * camFocus.z;
    updateBearing();
}

void RtsCamera::rotateVertical(float deg)
{
    // >>> Gimbal Locked! <<<
    //  glm::vec3 camFocus = *eye - *focus;
    //  glm::vec3 temp = glm::rotate(camFocus, deg, glm::vec3(1.0, 0.0, 0.0));
    //  temp = glm::rotate(temp, deg, glm::vec3(0.0, 0.0, 1.0));
    //  temp += *focus;
    //  if (eye->y < 3) {
    //     eye->y = 3;
    // } else {
    //     eye->y = temp.y;
    // }
    // eye->x = temp.x;
    // eye->z = temp.z;
    //  updateBearing();
}

void RtsCamera::rotateHorizontal(float deg)
{
    glm::vec3 camFocus = *eye - *focus;
    glm::vec3 temp = glm::rotate(camFocus, deg, glm::vec3(0.0, 1.0, 0.0));
    temp += *focus;
    eye->x = temp.x;
    eye->z = temp.z;
    updateBearing();
}

void RtsCamera::updateBearing()
{
    glm::vec3 camFocus = *eye - *focus;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f));
    *lateralAxis = glm::normalize(rotationMatrix * glm::vec4(camFocus, 1.0f));
}
