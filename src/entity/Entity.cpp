#include <glm/detail/type_vec3.hpp>
#include "Entity.h"

Entity::Entity()
{
    this->position = glm::vec3(0, 0, 0);
}

Entity::~Entity() {}

glm::vec3 * Entity::getPosition()
{
    return &this->position;
}
