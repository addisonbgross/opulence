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
    glm::vec3 camFocus = *eye - *focus;
    glm::quat cameraLine(glm::normalize(camFocus));
    glm::quat qRotation = glm::angleAxis(deg, glm::vec3(lateralAxis->x, 0, lateralAxis->z));
    glm::mat4 mat = glm::toMat4( glm::mix(cameraLine, qRotation, 1.0f) );
    glm::vec4 temp = mat * glm::vec4(camFocus, 1.0f);
    temp += glm::vec4(*focus, 1.0f);

    float angle = getAngleToGround( glm::vec3( temp ) - glm::vec3( *focus ) );
    if ( temp.y > heightBottomRestriction && temp.y < heightTopRestriction && angle < verticalRotationRestriction ) {
        eye->x = temp.x;
        eye->y = temp.y;
        eye->z = temp.z;
        updateBearing();
    }
}

void RtsCamera::rotateHorizontal(float deg)
{
    glm::mat4 m = glm::toMat4( glm::angleAxis(-deg, glm::vec3(0, 1, 0)) );
    glm::vec3 camFocus = *eye - *focus;
    glm::vec4 temp = m * glm::vec4(camFocus, 1.0f);
    temp += glm::vec4(*focus, 1.0f);
    eye->x = temp.x;
    eye->z = temp.z;

    updateBearing();
}

void RtsCamera::incrementZoom()
{
    float angle = getAngleToGround( *eye - *focus );
    if ( eye->y < heightTopRestriction && angle < verticalRotationRestriction  ) {
        eye->y += 0.5f;
    }
}

void RtsCamera::decrementZoom()
{
    if ( eye->y > heightBottomRestriction + 0.5f ) {
        eye->y -= 0.5f;
    }
}

float RtsCamera::getAngleToGround( glm::vec3 vec )
{
    return glm::angle( glm::normalize( glm::vec3( vec.x, 0, vec.z ) ), glm::normalize( vec ) );
}
