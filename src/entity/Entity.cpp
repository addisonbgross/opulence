#include <glm/detail/type_vec3.hpp>
#include "Entity.h"

Entity::Entity()
{
    this->position = glm::vec3(0, 0, 0);
    this->orientation = glm::angleAxis(00.0f, glm::vec3(1, 0, 0));
}

Entity::Entity(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

Entity::~Entity() {}


/*** get ***/
float Entity::getWidth() { return 0; }
float Entity::getHeight() { return 0; }
float Entity::getDepth() { return 0; }

GLfloat * Entity::getOrientation()
{
    orientationReference = glm::toMat4(orientation);
    return &orientationReference[0][0];
}

/*** set ***/

void Entity::setOrientation(glm::quat q)
{
    orientation = q;
}
