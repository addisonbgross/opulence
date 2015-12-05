#include "Entity.h"

Entity::Entity()
{
    this->position = glm::vec3(0, 0, 0);
    this->orientation = glm::quat( glm::angleAxis(0.0f, glm::vec3(0, 0, 1)) );
}

Entity::Entity(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
    this->orientation = glm::quat( glm::angleAxis(0.0f, glm::vec3(0, 0, 1)) );
}

Entity::~Entity() {}

/*** get ***/
float Entity::getWidth() { return 0; }
float Entity::getHeight() { return 0; }
float Entity::getDepth() { return 0; }

glm::quat * Entity::getOrientationQuat()
{
    return &orientation;
}

GLfloat * Entity::getOrientation()
{
    orientationReference = glm::toMat4(orientation);
    return &orientationReference[0][0];
}

int Entity::getHighlight()
{
    return isHighlight;
}

int Entity::getInterface()
{
    return isInterface;
}

/*** set ***/

void Entity::setOrientation(glm::quat q)
{
    orientation = q;
}

void Entity::setHighlight(int high)
{
    isHighlight = high;
}

void Entity::setInterface(int inter)
{
    isInterface = inter;
}
